CMAKE_MINIMUM_REQUIRED(VERSION 3.5)
PROJECT(ClientServerChat VERSION 1.0 LANGUAGES CXX)
SET(CMAKE_CXX_STANDARD 17)

add_executable(Server network/server/server.cpp db/database.cpp)
add_executable(Client network/client/client.cpp)
add_subdirectory(include)
target_link_libraries(Server PRIVATE asio json)
target_link_libraries(Client PRIVATE asio json)

add_executable(Main main.cpp)
target_link_libraries(Main PRIVATE asio)

add_library(NetworkInterface INTERFACE network/network_interface.h)
