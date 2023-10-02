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
    socket_ptr new_socket(new socket_type(io_context_));
    acceptor_.async_accept(*new_socket, [this, new_socket](asio::error_code er) {
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