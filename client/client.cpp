//
// Created by Joaquina Daeron on 9/24/23.
//

#include "client.h"
#include <iostream>

namespace csc {
    void client::connect() {
        asio::error_code err;
        socket_.connect(ep_, err);
        if (err) {
            std::cout << err.message() << std::endl;
            return;
        }
        messageHandler();
    }

    void client::messageHandler() {
        while (true) {
            char response[512]{};
            char request[512]{};
            std::cin.getline(request, 512);
            write(socket_, asio::buffer(request));
            auto len = socket_.read_some(asio::buffer(response));
            if (len > 0) std::cout << "Server: " << response << '\n';
        }
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