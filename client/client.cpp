//
// Created by Joaquina Daeron on 9/24/23.
//

#include "client.h"
#include <iostream>

namespace csc {
    void client::connect() {
        asio::error_code err;
        socket_.connect(ep_, err);
        if (err)
            std::cout << err.message() << std::endl;
        while (true) {
            messageHandler();
        }
    }

    void client::messageHandler() {
        char buff[512];
        std::cin >> buff;
        write(socket_, asio::buffer(buff));
        auto len = socket_.read_some(asio::buffer(buff));
        if (len > 0) std::cout << buff << '\n';
    }
} // csc

int main(int argc, char** argv) {
    if (argc < 3) {
        std::cout << "Using: client <host> <port>";
        return 1;
    }
    csc::client c(argv[1], argv[2]);
    c.connect();
    return 0;
}