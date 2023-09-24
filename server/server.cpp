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
            char data[512];
            asio::error_code er;
            auto len = socket_.read_some(asio::buffer(data), er);
            if (er == asio::error::eof) {
                std::cout << "Client leave a chat.\n" << er.message() << '\n';
                return;
            }
                if (len > 0) asio::write(socket_, asio::buffer("ok", 2));
        }
    }
} // csc

int main() {
    csc::server s;
    s.connect();
    return 0;
}