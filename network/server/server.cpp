//
// Created by Joaquina Daeron on 9/24/23.
//

#include "server.h"
#include <parser_server.h>

#include <iostream>
#include <thread>

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
                // Добавить обработчик события для подключившихся клиентов
                std::cout << "NOTIFICATION! NEW CONNECTION\n";
                Authenticator::Authentication(*this, new_socket);
            } else {
                std::cout << er.message() << '\n';
                new_socket->close();
            }
            AcceptNewClient();
        });
    }


//    void server::AcceptNewClient() {
//        socket_ptr new_socket(new asio::ip::tcp::socket(io_context_));
//        std::cout << "Socket " << new_socket.get() << '\n';
//        acceptor_.async_accept(*new_socket, [this, new_socket](const asio::error_code &er) {
//            if (!er) {
//                std::cout << "NOTIFICATION! NEW CONNECTION\n";
//                clients_.insert(new_socket);
//                Start(new_socket);
//            } else {
//                std::cout << er.message() << '\n';
//                new_socket->close();
//            }
//            AcceptNewClient();
//        });
//    }

    void server::ReadHandler(socket_ptr socket) {
        std::shared_ptr<MessageInfo> message(new MessageInfo(socket));
        socket->async_read_some(asio::buffer(message->message),
                                [this, socket, message](const asio::error_code &e, std::size_t bytes) {
                                    std::cout << "Read " << bytes << " bytes\n";
                                    if (!e) {
                                        message->message.resize(bytes);
                                        ParserServer<Buffer<char>>::GenerateJson(message->message, message->client.client_name);
                                        messages_.emplace(*message);
                                    } else {
                                        std::cout << e.message() << '\n';
                                        clients_.erase(socket);
                                        socket->close();
                                        return;
                                    }
                                    message->message.empty() ? ReadHandler(socket) : WriteHandler(socket, bytes);
                                });
    }

    void server::WriteHandler(socket_ptr socket, size_t &bytes) {
        mutex_.lock();
        while (!messages_.empty()) {
            for (auto &client: clients_) {
                if (client.first != messages_.front().client.client_socket) {
                    asio::write(*client.first, asio::buffer(messages_.front().message));
                    std::cout << "Output message: ";
                    for (auto &i: messages_.front().message) std::cout << i;
                    std::cout << '\n';
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

    void Authenticator::Authentication(server &s, socket_ptr socket) {
        nlohmann::json j{};
        j["name"] = "Server";
        j["message"] = "Welcome to the chat! Enter your name: ";
        std::string str{to_string(j)};
        std::shared_ptr<MessageInfo> buff(new MessageInfo(socket, std::move(str)));
        socket->write_some(asio::buffer(buff->message));
        // Нужно разделить буфферы на входящий и исходящий
        socket->async_read_some(asio::buffer(buff->client.client_name, 512), [&s, socket, buff](const asio::error_code &er, size_t bytes) {
            if (!er) {
                ParserServer<MessageInfo>::ParseName(*buff);
                s.clients_.emplace(socket, buff->client.client_name);
            }
            s.Start(socket);
        });
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