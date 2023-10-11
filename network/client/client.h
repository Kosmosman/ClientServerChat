//
// Created by Joaquina Daeron on 9/24/23.
//

#ifndef CLIENTSERVERCHAT_CLIENT_H
#define CLIENTSERVERCHAT_CLIENT_H

//#define ASIO_ENABLE_HANDLER_TRACKING

#include <network_interface.h>
#include <common.h>
#include <parser_client.h>
#include <buffer.h>

#include <sys/socket.h>
#include <array>

namespace csc {

    class client : public NetworkInterface {
    public:
        explicit client(std::string &&ip, int &&port) : ep_(asio::ip::address::from_string(ip), port),
                                                        input_buffer_(BUFFER_SIZE), output_buffer_(BUFFER_SIZE) {};

        void Connect() override;

    private:
        void ReadHandler(socket_ptr socket) override;

        void WriteHandler(socket_ptr socket) override;

        void PrintMessage(socket_ptr socket, std::size_t &bytes);

        asio::io_context io_context_{};
        asio::posix::stream_descriptor input_{io_context_, ::dup(STDIN_FILENO)};
        asio::ip::tcp::endpoint ep_;

        Buffer<char> input_buffer_;
        Buffer<char> output_buffer_;

    };

} // namespace csc

#endif // CLIENTSERVERCHAT_CLIENT_H