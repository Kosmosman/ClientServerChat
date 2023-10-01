//
// Created by Joaquina Daeron on 9/24/23.
//

#include "server.h"
#include <iostream>

namespace csc {
    void server::connect() {
        acceptor_.accept(socket_);
        start();
        io_context_.run();
    }

    void server::start() {
        input_.async_read_some(asio::buffer(output_buffer_), [this](const asio::error_code& e, std::size_t bytes_transferred){if (e == asio::error::eof) return; writeToSocket();});
        socket_.async_read_some(asio::buffer(input_buffer_), [this](const asio::error_code& e, std::size_t bytes_transferred){if (e == asio::error::eof) return; readFromSocket(bytes_transferred);});
    }

    void server::writeToSocket() {
        socket_.async_write_some(asio::buffer(output_buffer_), [this](const asio::error_code& e, std::size_t bytes_transferred){if (e == asio::error::eof) return; start();});
    }

    void server::readFromSocket(std::size_t bytes_transferred) {
        std::cout << "Client: ";
        for (std::size_t i = 0; i < bytes_transferred && input_buffer_[i] != '\n'; ++i)
            std::cout << input_buffer_[i];
        std::cout << '\n';
        start();
    }
} // csc

int main() {
    csc::server s;
    s.connect();
    return 0;
}