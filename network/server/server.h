//
// Created by Joaquina Daeron on 9/24/23.
//

#ifndef CLIENTSERVERCHAT_SERVER_H
#define CLIENTSERVERCHAT_SERVER_H
#define ASIO_ENABLE_HANDLER_TRACKING


#include <common.h>
#include <network_interface.h>
#include <buffer.h>

#include <queue>
#include <array>
#include <unordered_set>
#include <utility>

namespace csc {

    struct ClientInfo {
        explicit ClientInfo(socket_ptr s, const std::vector<char> &other_name) :
                client_socket{std::move(s)},
                client_name{other_name} {};

        explicit ClientInfo(socket_ptr &&s) : client_socket{std::move(s)}, client_name(NAME_SIZE) {};

        socket_ptr client_socket{};
        Buffer<char> client_name;
    };

    struct MessageInfo {
        explicit MessageInfo(socket_ptr s) : client{std::move(s)}, message(BUFFER_SIZE) {};
        ClientInfo client;
        std::vector<char> message;
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
