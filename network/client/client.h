//
// Created by Joaquina Daeron on 9/24/23.
//

#ifndef CLIENTSERVERCHAT_CLIENT_H
#define CLIENTSERVERCHAT_CLIENT_H

#include <sys/socket.h>
#include "../network_interface.h"

namespace csc {

class client : public NetworkInterface {
public:
  explicit client(std::string &&ip, std::string &&port) : NetworkInterface(std::move(ip), std::move(port)) {};
  void connect() override;
};

} // namespace csc

#endif // CLIENTSERVERCHAT_CLIENT_H
