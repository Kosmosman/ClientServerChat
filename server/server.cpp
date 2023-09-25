//
// Created by Joaquina Daeron on 9/24/23.
//

#include "server.h"
#include <iostream>

namespace csc {
    void server::connect() {
        acceptor_.accept(socket_);
        message_handler();
    }

    void server::message_handler() {
        std::cout << "Connected!\n";
        while (true) {
            char response[512]{};
            char request[512];
            asio::error_code er;
            auto len = socket_.read_some(asio::buffer(response), er);
            if (er == asio::error::eof) {
                std::cout << "Client leave a chat.\n" << er.message() << '\n';
                return;
            } else {
                std::cout << "Client: " << response << '\n';
            }
                if (len > 0) {
                    std::cin.getline(request, 512);
                    asio::write(socket_, asio::buffer(request, 512));
                }
        }
    }
} // csc

int main() {
    csc::server s;
    s.connect();
    return 0;
}