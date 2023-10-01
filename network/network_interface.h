//
// Created by Joaquina Daeron on 10/1/23.
//

#ifndef CLIENTSERVERCHAT_NETWORK_INTERFACE_H
#define CLIENTSERVERCHAT_NETWORK_INTERFACE_H

#include "../include/asio-1.28.0/include/asio.hpp"
#include <sys/socket.h>
#include <iostream>
#include <memory>
#include <utility>

namespace csc {
    class NetworkInterface {
    public:
        using size_t = unsigned long;
        using socket_ptr = std::shared_ptr<asio::ip::tcp::socket>;
    public:
        explicit NetworkInterface(std::string &&ip, std::string &&port) : ep_(asio::ip::address::from_string(ip), stoi(port)){};
        explicit NetworkInterface(std::string &&port) : ep_(asio::ip::tcp::v4(), stoi(port)) {};
        virtual void connect() = 0;
        virtual ~NetworkInterface() = default;

        void start(socket_ptr& socket) {
            readHandler(socket);
        }

    private:
        void readHandler(socket_ptr& socket){
            input_.async_read_some(
                    asio::buffer(output_buffer_, 512),
                    [this, &socket](const asio::error_code &e, size_t bytes_transferred) {
                        if (e == asio::error::eof)
                            return;
                        writeHandler(socket);
                    });
            socket->async_read_some(
                    asio::buffer(input_buffer_, 512),
                    [this, &socket](const asio::error_code &e, size_t bytes_transferred) {
                        if (e == asio::error::eof)
                            return;
                        printMessage(bytes_transferred, socket);
                    });
        };
        void writeHandler(socket_ptr& socket){
            socket->async_write_some(
                    asio::buffer(output_buffer_, 512),
                    [this, &socket](const asio::error_code &e, size_t bytes_transferred) {
                        if (e == asio::error::eof)
                            return;
                        readHandler(socket);
                    });
        };
        void printMessage(size_t bytes_transferred, socket_ptr& socket){
            if (bytes_transferred) {
                std::cout << "Other: ";
                for (size_t i = 0; i < bytes_transferred && input_buffer_[i] != '\n';
                     ++i)
                    std::cout << input_buffer_[i];
                std::cout << '\n';
                readHandler(socket);
            }
        };

    protected:
        asio::io_context io_context_;
        asio::ip::tcp::endpoint ep_;
    private:
        asio::posix::stream_descriptor input_{io_context_, ::dup(STDIN_FILENO)};
        char input_buffer_[512]{};
        char output_buffer_[512]{};

    };
} // namespace csc

#endif //CLIENTSERVERCHAT_NETWORK_INTERFACE_H
