//
// Created by Joaquina Daeron on 9/24/23.
//

#include "server.h"
#include <iostream>
#include <thread>
#include <utility>

namespace csc {
void server::connect() {
  accept_new_client();
  io_context_.run();
}

void server::accept_new_client() {
    socket_ptr new_socket(new asio::ip::tcp::socket(io_context_));
    std::cout << "Socket " << new_socket.get() << '\n';
    acceptor_.async_accept(*new_socket, [this, new_socket](const asio::error_code& er) {
      if (!er) {
        std::cout << "NOTIFICATION! NEW CONNECTION\n";
        std::cout << "counter = " << ++counter_ << '\n';
        clients_[counter_] = new_socket;
          start(new_socket);
    } else {
          std::cout << er.message() << '\n';
      }
    accept_new_client();
  });
}

    void server::readHandler(socket_ptr socket) {
    std::shared_ptr<MessageInfo> message(new MessageInfo(socket));
        socket->async_read_some(asio::buffer(message->message), [this, socket, message](const asio::error_code& e, std::size_t) {
            std::for_each(message->message.begin(), message->message.end(), [](int i){std::cout << i;});
            if (!e)
                messages_.emplace(message->message_owner, message->message);
            else
                std::cout << e.message() << '\n';
            message->message.empty() ? readHandler(socket) : writeHandler(socket);
        });
    }

    void server::writeHandler(socket_ptr socket) {
        mutex_.lock();
        while (!messages_.empty()) {
            for (auto &client: clients_) {
                if (client.second != messages_.front().message_owner) {
                    asio::write(*client.second, asio::buffer(messages_.front().message));
                }
            }
            messages_.pop();
        }
        mutex_.unlock();
        readHandler(socket);
    }

    void server::start(socket_ptr socket) {
        readHandler(std::move(socket));
    }

} // namespace csc

int main(int argc, char **argv) {
  if (argc < 2) {
    std::cout << "Using: server <port>";
    return 1;
  }
  csc::server s(argv[1]);
  s.connect();
  return 0;
}