#include "./include/asio-1.28.0/include/asio.hpp"
#include <iostream>

asio::io_service ioService;
asio::posix::stream_descriptor input(ioService, ::dup(STDIN_FILENO));
char buffer[1024];

void handler(const asio::error_code &error, std::size_t bytes_transferred) {
  if (!error) {
    std::string userInput(buffer, bytes_transferred);
    std::cout << "User input: " << userInput << std::endl;

    // Continue reading input
    input.async_read_some(asio::buffer(buffer), handler);
  }
}

int main() {
  std::cout << "Enter input: " << std::endl;

  // Start reading input
  input.async_read_some(asio::buffer(buffer), handler);

  // Run the event loop
  ioService.run();

  return 0;
}
