//
// Created by Joaquina Daeron on 9/24/23.
//

#include "client.h"
#include <ios>
#include <iostream>

namespace csc {
void client::connect() {
  socket_ptr sock{new asio::ip::tcp::socket(io_context_)};
  sock->async_connect(ep_, [this, &sock](const asio::error_code &er) {
    if (!er)
      start(sock);
    else
        std::cout << er.message() << '\n';
  });
  io_context_.run();
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