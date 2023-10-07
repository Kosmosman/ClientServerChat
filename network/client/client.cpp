//
// Created by Joaquina Daeron on 9/24/23.
//

#include "client.h"
#include <ios>
#include <iostream>

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
        input_.async_read_some(asio::buffer(input_buffer_), [this, socket](const asio::error_code &e, std::size_t) {
            if (!e)
                WriteHandler(socket);
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

    void client::WriteHandler(socket_ptr socket) {
        asio::error_code e;
        asio::write(*socket, asio::buffer(input_buffer_), e);
        if (!e)
            ReadHandler(socket);
        else
            std::cout << e.message() << '\n';

    }

    void client::PrintMessage(socket_ptr socket, std::size_t &bytes) {
        std::cout << "Other: ";
        for (int i = 0; output_buffer_[i] != '\n'; ++i)
            std::cout << output_buffer_[i];
        std::cout << '\n';
        ReadHandler(socket);
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