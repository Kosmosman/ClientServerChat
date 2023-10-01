//
// Created by Joaquina Daeron on 9/24/23.
//

#include "client.h"
#include <iostream>
#include <ios>

namespace csc {
    void client::connect() {
        asio::error_code err;
        socket_.connect(ep_, err);
        if (err) {
            std::cout << err.message() << std::endl;
            return;
        }
        start();
        io_context_.run();
    }

    void client::start() {
        input_.async_read_some(asio::buffer(output_buffer_), [this](const asio::error_code& e, std::size_t bytes_transferred){if (e == asio::error::eof) return; writeToSocket();});
        socket_.async_read_some(asio::buffer(input_buffer_), [this](const asio::error_code& e, std::size_t bytes_transferred){if (e == asio::error::eof) return; readFromSocket(bytes_transferred);});
    }

    void client::writeToSocket() {
        socket_.async_write_some(asio::buffer(output_buffer_), [this](const asio::error_code& e, std::size_t bytes_transferred){if (e == asio::error::eof) return; start();});
    }

    void client::readFromSocket(std::size_t bytes_transferred) {
        std::cout << "Server: ";
        for (std::size_t i = 0; i < bytes_transferred && input_buffer_[i] != '\n'; ++i)
            std::cout << input_buffer_[i];
        std::cout << '\n';
        start();
    }
} // csc


int main(int argc, char** argv) {
    if (argc < 3) {
        std::cout << "Using: client <host> <port>";
        return 1;
    }
    csc::client c(argv[1], argv[2]);
    c.connect();
    return 0;
}