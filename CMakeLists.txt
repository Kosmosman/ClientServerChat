CMAKE_MINIMUM_REQUIRED(VERSION 3.5)
PROJECT(ClientServerChat VERSION 1.0 LANGUAGES CXX)
SET(CMAKE_CXX_STANDARD 20)

add_executable(Server network/server/server.cpp db/database.cpp)
add_executable(Client network/client/client.cpp)
add_subdirectory(include)
target_link_libraries(Server PRIVATE asio ParserServer)
target_link_libraries(Client PRIVATE asio ParserClient)

add_executable(Main main.cpp)
target_link_libraries(Main INTERFACE asio)

add_library(NetworkInterface INTERFACE network/network_interface.h)

add_library(ParserClient INTERFACE utility/parser_client.h)

add_library(ParserServer INTERFACE utility/parser_server.h)

target_link_libraries(ParserServer INTERFACE json)
target_link_libraries(ParserClient INTERFACE json)
