//
// Created by Joaquina Daeron on 9/24/23.
//

#ifndef CLIENTSERVERCHAT_SERVER_H
#define CLIENTSERVERCHAT_SERVER_H

#include <sys/socket.h>
#include <thread>
#include <memory>
#include "../include/asio-1.28.0/include/asio.hpp"

namespace csc {
    using socket_ptr = std::shared_ptr<asio::ip::tcp::socket>;
    class server {
    public:
        server() = default;
        void connect();
        void message_handler();
    private:
        asio::io_context io_context_;
        asio::ip::tcp::endpoint ep_{asio::ip::tcp::v4(), 8080};
        asio::ip::tcp::socket socket_{io_context_};
        asio::ip::tcp::acceptor acceptor_{io_context_, ep_};
    };

} // csc

#endif //CLIENTSERVERCHAT_SERVER_H
