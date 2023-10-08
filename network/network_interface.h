//
// Created by Joaquina Daeron on 10/1/23.
//

#ifndef CLIENTSERVERCHAT_NETWORK_INTERFACE_H
#define CLIENTSERVERCHAT_NETWORK_INTERFACE_H

#include <asio.hpp>
#include <iostream>
#include <memory>
#include <sys/socket.h>
#include <utility>

namespace csc {
    using size_t = unsigned long;
    using socket_ptr = std::shared_ptr<asio::ip::tcp::socket>;
    using socket_type = asio::ip::tcp::socket;

    class NetworkInterface {
    public:

        virtual void Connect() = 0;

        virtual ~NetworkInterface() = default;

    private:

        virtual void ReadHandler(socket_ptr socket) = 0;

        virtual void WriteHandler(socket_ptr socket) = 0;


    };
} // namespace csc

#endif // CLIENTSERVERCHAT_NETWORK_INTERFACE_H