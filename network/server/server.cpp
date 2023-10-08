//
// Created by Joaquina Daeron on 9/24/23.
//

#include "server.h"
#include <iostream>
#include <thread>
#include <utility>

namespace csc {
    void server::Connect() {
        AcceptNewClient();
        io_context_.run();
    }

    void server::AcceptNewClient() {
        socket_ptr new_socket(new asio::ip::tcp::socket(io_context_));
        std::cout << "Socket " << new_socket.get() << '\n';
        acceptor_.async_accept(*new_socket, [this, new_socket](const asio::error_code &er) {
            if (!er) {
                std::cout << "NOTIFICATION! NEW CONNECTION\n";
                clients_.insert(new_socket);
                Start(new_socket);
            } else {
                std::cout << er.message() << '\n';
                new_socket->close();
            }
            AcceptNewClient();
        });
    }

    void server::ReadHandler(socket_ptr socket) {
        std::shared_ptr<MessageInfo> message(new MessageInfo(socket));
        socket->async_read_some(asio::buffer(message->message),
                                [this, socket, message](const asio::error_code &e, std::size_t bytes) {
                                    std::cout << "Read " << bytes << " bytes\n";
                                    if (!e) {
                                        messages_.emplace(*message);
                                    } else {
                                        std::cout << e.message() << '\n';
                                        clients_.erase(socket);
                                        socket->close();
                                        return;
                                    }
                                    message->message.empty() ? ReadHandler(socket) : WriteHandler(socket);
                                });
    }

    void server::WriteHandler(socket_ptr socket) {
        mutex_.lock();
        while (!messages_.empty()) {
            for (auto &client: clients_) {
                if (client != messages_.front().client.client_socket) {
                    asio::write(*client, asio::buffer(messages_.front().message));
                }
            }
            messages_.pop();
        }
        mutex_.unlock();
        ReadHandler(socket);
    }

    void server::Start(socket_ptr socket) {
        ReadHandler(std::move(socket));
    }

} // namespace csc

int main(int argc, char **argv) {
    if (argc < 2) {
        std::cout << "Using: server <port>";
        return 1;
    }
    csc::server s(argv[1]);
    s.Connect();
    return 0;
}