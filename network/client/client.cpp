//
// Created by Joaquina Daeron on 9/24/23.
//

#include "client.h"
#include <ios>
#include <iostream>

namespace csc {
void client::connect() {
  asio::error_code er;
  socket_.connect(ep_, er);
  if (er) {
    std::cout << er.message() << std::endl;
    return;
  }
  start();
}
} // namespace csc

int main(int argc, char **argv) {
  if (argc < 3) {
    std::cout << "Using: client <host> <port>";
    return 1;
  }
  csc::client c(argv[1], argv[2]);
  c.connect();
  return 0;
}