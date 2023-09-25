CMAKE_MINIMUM_REQUIRED(VERSION 3.5)
PROJECT(ClientServerChat VERSION 1.0 LANGUAGES CXX)
SET(CMAKE_CXX_STANDARD 17)

add_executable(Server server/server.cpp)
add_executable(Client client/client.cpp)
add_subdirectory(include)
target_link_libraries(Server PRIVATE asio)
target_link_libraries(Client PRIVATE asio)

add_executable(Main main.cpp)
target_link_libraries(Main PRIVATE asio)