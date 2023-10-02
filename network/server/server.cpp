//
// Created by Joaquina Daeron on 9/24/23.
//

#include "server.h"
#include <iostream>
#include <thread>

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
          readHandler(new_socket);
    } else {
          std::cout << er.message() << '\n';
      }
    accept_new_client();
  });
}

    void server::readHandler(const socket_ptr &socket) {
        std::string mess;
        socket->async_read_some(asio::buffer(mess), [this, socket, &mess](const asio::error_code& e, std::size_t) {
            if (!e)
                messages_.emplace(socket, clients_.size(), std::move(mess));
            else
                std::cout << e.message() << '\n';

            writeHandler(socket);
        });
    }

    void server::writeHandler(const socket_ptr &socket) {
        if (!messages_.front().count_of_last_readers) {
            messages_.pop();
            readHandler(socket);
        } else if (messages_.front().message_owner != socket) {
            socket->async_write_some(asio::buffer(messages_.front().message), [this, socket](const asio::error_code& e, std::size_t) {
                if (!e) --messages_.front().count_of_last_readers;
                readHandler(socket);
            });
        }
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