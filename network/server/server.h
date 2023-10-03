//
// Created by Joaquina Daeron on 9/24/23.
//

#ifndef CLIENTSERVERCHAT_SERVER_H
#define CLIENTSERVERCHAT_SERVER_H

#include "../network_interface.h"
#include <queue>
#include <unordered_map>

namespace csc {

    struct MessageInfo {
        explicit MessageInfo(socket_ptr s,  std::vector<char> v) : message_owner{s}, message{v} {};
        explicit MessageInfo(socket_ptr s) : message_owner{s}, message(512) {};
        socket_ptr message_owner{};
        std::vector<char> message;
    };

    class server : public NetworkInterface {

    public:
        explicit server(std::string&& port) : ep_(asio::ip::tcp::v4(), stoi(port)), acceptor_(io_context_, ep_){};
  void connect() override;

private:
    void accept_new_client();
    void start(socket_ptr socket);
        void readHandler(socket_ptr socket) override;
        void writeHandler(socket_ptr socket) override;

    asio::io_context io_context_;
        asio::ip::tcp::endpoint ep_;
        asio::ip::tcp::acceptor acceptor_;
    std::unordered_map<int, socket_ptr> clients_{};
    std::queue<MessageInfo> messages_{};
    std::mutex mutex_;
    int counter_{};
};

} // namespace csc

#endif // CLIENTSERVERCHAT_SERVER_H
