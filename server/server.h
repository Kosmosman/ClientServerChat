//
// Created by Joaquina Daeron on 9/24/23.
//

#ifndef CLIENTSERVERCHAT_SERVER_H
#define CLIENTSERVERCHAT_SERVER_H

#include <sys/socket.h>
#include "../include/asio-1.28.0/include/asio.hpp"

namespace csc {
    class server {
    public:
        server() {};
        void connect();

    private:
        void start();
        void writeToSocket();
        void readFromSocket(std::size_t bytes_transferred);

        asio::io_context io_context_;
        asio::posix::stream_descriptor input_{io_context_, ::dup(STDIN_FILENO)};
        asio::ip::tcp::endpoint ep_{asio::ip::tcp::v4(), 8080};
        asio::ip::tcp::socket socket_{io_context_};
        asio::ip::tcp::acceptor acceptor_{io_context_, ep_};

        char input_buffer_[512]{};
        char output_buffer_[512]{};

    };

} // csc

#endif //CLIENTSERVERCHAT_SERVER_H
