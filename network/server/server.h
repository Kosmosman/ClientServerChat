//
// Created by Joaquina Daeron on 9/24/23.
//

#ifndef CLIENTSERVERCHAT_SERVER_H
#define CLIENTSERVERCHAT_SERVER_H

#include "../network_interface.h"
#include <unordered_map>

namespace csc {
class server : public NetworkInterface {
    using socket_type = asio::ip::tcp::socket;
public:
  explicit server(std::string &&port) : acceptor_{io_context_, asio::ip::tcp::endpoint(asio::ip::tcp::v4(),std::stoi(port))} {};
  void connect() override;

private:
  void accept_new_client();
  asio::ip::tcp::acceptor acceptor_;
  std::unordered_map<int, socket_ptr> clients_{};
  int counter_{};
};

} // namespace csc

#endif // CLIENTSERVERCHAT_SERVER_H
