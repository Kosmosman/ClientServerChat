//
// Created by Joaquina Daeron on 9/24/23.
//

#ifndef CLIENTSERVERCHAT_CLIENT_H
#define CLIENTSERVERCHAT_CLIENT_H

#include "../network_interface.h"
#include <sys/socket.h>

namespace csc {

class client : public NetworkInterface {
public:
  explicit client(std::string &&ip, std::string &&port) : ep_(asio::ip::address::from_string(ip), stoi(port)) {};
  void connect() override;

private:
    asio::ip::tcp::endpoint ep_;
};

} // namespace csc

#endif // CLIENTSERVERCHAT_CLIENT_H