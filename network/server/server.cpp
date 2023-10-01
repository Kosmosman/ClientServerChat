//
// Created by Joaquina Daeron on 9/24/23.
//

#include "server.h"
#include <iostream>

namespace csc {
void server::connect() {
    asio::error_code er;
    acceptor_.accept(socket_, er);
    if (er) {
        std::cout << er.message() << std::endl;
        return;
    }
    start();
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