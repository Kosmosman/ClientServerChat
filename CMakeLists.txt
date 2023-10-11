CMAKE_MINIMUM_REQUIRED(VERSION 3.5)
PROJECT(ClientServerChat VERSION 1.0 LANGUAGES CXX)
SET(CMAKE_CXX_STANDARD 20)

add_library(NetworkInterface INTERFACE)
target_include_directories(NetworkInterface INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/network)

add_library(ParserClient INTERFACE utility/parser_client.h)
target_include_directories(ParserClient INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/utility)
target_link_libraries(ParserClient INTERFACE json)

add_library(ParserServer INTERFACE utility/parser_server.h)
target_include_directories(ParserServer INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/utility)
target_link_libraries(ParserServer INTERFACE json)

add_library(CommonValues INTERFACE)
target_include_directories(CommonValues INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/common)

add_library(Buffer INTERFACE utility/buffer.h)
target_include_directories(Buffer INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/utility)

add_executable(Server network/server/server.cpp)
add_executable(Client network/client/client.cpp)
add_subdirectory(include)

target_link_libraries(Server PRIVATE asio ParserServer NetworkInterface CommonValues Buffer)
target_link_libraries(Client PRIVATE asio ParserClient NetworkInterface CommonValues Buffer)

add_executable(Main main.cpp)
target_link_libraries(Main PRIVATE asio)
