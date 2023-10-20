//
// Created by Joaquina Daeron on 9/24/23.
//

#include "client.h"
#include <parser_client.h>

#include <ios>
#include <iostream>
#include <utility>

namespace csc {
    void client::Connect() {
        socket_ptr sock{new asio::ip::tcp::socket(io_context_)};
        sock->async_connect(ep_, [this, &sock](const asio::error_code &er) {
            if (!er)
                ReadHandler(sock);
            else
                std::cout << er.message() << '\n';
        });
        io_context_.run();
    }


    void client::ReadHandler(socket_ptr socket) {
        input_.async_read_some(asio::buffer(input_buffer_), [this, socket](const asio::error_code &e, std::size_t bytes) {
            if (!e)
                WriteHandler(socket, bytes);
            else
                std::cout << e.message() << '\n';
        });
        socket->async_read_some(asio::buffer(output_buffer_),
                                [this, socket](const asio::error_code &e, std::size_t bytes) {
                                    if (!e)
                                        PrintMessage(socket, bytes);
                                    else
                                        std::cout << e.message() << '\n';
                                });
    }

    void client::WriteHandler(socket_ptr socket, size_t &bytes) {
        ParserClient<Buffer<>>::GenerateJson(input_buffer_);
        socket->write_some(asio::buffer(input_buffer_, bytes));
        ReadHandler(socket);
    }

    void client::PrintMessage(socket_ptr socket, std::size_t &bytes) {
        ParserClient<Buffer<char>>::ParseJson(output_buffer_);
        for (int i = 0; i < output_buffer_.size() && i < bytes; ++i)
            std::cout << output_buffer_[i];
        std::cout << '\n';
        ReadHandler(std::move(socket));
    }

} // namespace csc

int main(int argc, char **argv) {
    if (argc < 3) {
        std::cout << "Using: client <host> <port>";
        return 1;
    }
    csc::client c(argv[1], std::stoi(argv[2]));
    c.Connect();
    return 0;
}