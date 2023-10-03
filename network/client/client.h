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
  explicit client(std::string &&ip, int &&port) : ep_(asio::ip::address::from_string(ip),port) {};
  void connect() override;

private:
    void readHandler(socket_ptr socket) override;
    void writeHandler(socket_ptr socket) override;
    void printMessage(socket_ptr socket, std::size_t& bytes);

    asio::io_context io_context_{};
    asio::posix::stream_descriptor input_{io_context_, ::dup(STDIN_FILENO)};
    asio::ip::tcp::endpoint ep_;

    char input_buffer_[512]{};
    char output_buffer_[512]{};
};

} // namespace csc

#endif // CLIENTSERVERCHAT_CLIENT_H