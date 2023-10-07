//
// Created by Joaquina Daeron on 9/24/23.
//

#ifndef CLIENTSERVERCHAT_SERVER_H
#define CLIENTSERVERCHAT_SERVER_H
#define ASIO_ENABLE_HANDLER_TRACKING


#include "../network_interface.h"
#include "../../common/common.h"

#include <queue>
#include <array>
#include <unordered_set>

namespace csc {

    struct MessageInfo {
        explicit MessageInfo(socket_ptr s) : message_owner{s} {};
        socket_ptr message_owner{};
        std::array<char, 512> message{};
    };

    struct ClientInfo {
        explicit ClientInfo(socket_ptr s, std::array<char, NAME_SIZE> other_name) : client_socket{s},
                                                                                    client_name{other_name} {};
        socket_ptr client_socket{};
        std::array<char, NAME_SIZE> client_name{};
    };

    class server : public NetworkInterface {

    public:
        explicit server(std::string &&port) : ep_(asio::ip::tcp::v4(), stoi(port)), acceptor_(io_context_, ep_) {};

        void Connect() override;

    private:
        void AcceptNewClient();

        void Start(socket_ptr socket);

        void ReadHandler(socket_ptr socket) override;

        void WriteHandler(socket_ptr socket) override;

        asio::io_context io_context_;
        asio::ip::tcp::endpoint ep_;
        asio::ip::tcp::acceptor acceptor_;
        std::unordered_set<socket_ptr> clients_{};
        std::queue<MessageInfo> messages_{};
        std::mutex mutex_;
    };

} // namespace csc

#endif // CLIENTSERVERCHAT_SERVER_H
