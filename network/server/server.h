//
// Created by Joaquina Daeron on 9/24/23.
//

#ifndef CLIENTSERVERCHAT_SERVER_H
#define CLIENTSERVERCHAT_SERVER_H

#include "../network_interface.h"

namespace csc {
class server : public NetworkInterface {
public:
    explicit server(std::string&& port) : NetworkInterface(std::move(port)), acceptor_{io_context_, ep_}{};
    void connect() override;

private:
    void accept_new_client(socket_ptr& sock);
    asio::ip::tcp::acceptor acceptor_;


};

} // namespace csc

#endif // CLIENTSERVERCHAT_SERVER_H
