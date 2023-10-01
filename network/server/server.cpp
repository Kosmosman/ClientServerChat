//
// Created by Joaquina Daeron on 9/24/23.
//

#include "server.h"
#include <iostream>
#include <thread>
int counter{};
namespace csc {
void server::connect() {
    socket_ptr sock{new asio::ip::tcp::socket(io_context_)};
    accept_new_client(sock);
    io_context_.run();
}

    void server::accept_new_client(socket_ptr& sock) {
        acceptor_.async_accept(*sock, [this, &sock](asio::error_code er){
            if (!er) {
                std::cout << "NOTIFICATION! NEW CONNECTION\n";
                std::cout << "counter = " << ++counter << '\n';
                start(sock);
                socket_ptr new_socket(new asio::ip::tcp::socket(io_context_));
                accept_new_client(new_socket);
            }
        });
    }
} // namespace csc

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cout << "Using: server <port>";
        return 1;
    }
  csc::server s(argv[1]);
  s.connect();
  return 0;
}