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
        MessageInfo(socket_ptr s, size_t c, std::string m) : message_owner{s}, count_of_last_readers{c}, message{std::move(m)} {};
        socket_ptr message_owner{};
        size_t count_of_last_readers{};
        std::string message{};
    };

    class server : public NetworkInterface {

    public:
        explicit server(std::string&& port) : ep_(asio::ip::tcp::v4(), stoi(port)), acceptor_(io_context_, ep_){};
  void connect() override;

private:
    void accept_new_client();
        void readHandler(const socket_ptr& socket) override;
        void writeHandler(const socket_ptr& socket) override;

    asio::io_context io_context_;
        asio::ip::tcp::endpoint ep_;
        asio::ip::tcp::acceptor acceptor_;
    std::unordered_map<int, socket_ptr> clients_{};
    std::queue<MessageInfo> messages_{};
    int counter_{};
};

} // namespace csc

#endif // CLIENTSERVERCHAT_SERVER_H
