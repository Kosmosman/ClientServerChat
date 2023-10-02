//
// Created by Joaquina Daeron on 9/24/23.
//

#include "client.h"
#include <ios>
#include <iostream>

namespace csc {
void client::connect() {
  socket_ptr sock{new asio::ip::tcp::socket(io_context_)};
  sock->async_connect(ep_, [this, &sock](const asio::error_code &er) {
    if (!er)
        readHandler(sock);
    else
        std::cout << er.message() << '\n';
  });
  io_context_.run();
}



    void client::readHandler(const socket_ptr &socket) {
        input_.async_read_some(asio::buffer(input_buffer_), [this, socket](const asio::error_code& e, std::size_t) {
            if (!e)
                writeHandler(socket);
            else
                std::cout << e.message() << '\n';
        });
        socket->async_read_some(asio::buffer(output_buffer_), [this, socket](const asio::error_code& e, std::size_t bytes) {
            if (!e)
                printMessage(socket, bytes);
            else
                std::cout << e.message() << '\n';
        });
    }

    void client::writeHandler(const socket_ptr &socket) {
        socket->async_write_some(asio::buffer(input_buffer_), [this, socket](const asio::error_code& e, std::size_t) {
            if (!e)
                readHandler(socket);
            else
                std::cout << e.message() << '\n';
        });
    }

    void client::printMessage(const socket_ptr &socket, std::size_t& bytes) {
        std::cout << "Other: ";
        for (int i = 0; i < bytes && output_buffer_[i] != '\n'; ++i) {
            std::cout <<  output_buffer_[i];
        }
        std::cout << '\n';
        readHandler(socket);
    }

} // namespace csc

int main(int argc, char **argv) {
  if (argc < 3) {
    std::cout << "Using: client <host> <port>";
    return 1;
  }
  csc::client c(argv[1], std::stoi(argv[2]));
  c.connect();
  return 0;
}