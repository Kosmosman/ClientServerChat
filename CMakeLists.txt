CMAKE_MINIMUM_REQUIRED(VERSION 3.5)
PROJECT(ClientServerChat VERSION 1.0 LANGUAGES CXX)
SET(CMAKE_CXX_STANDARD 20)

add_library(NetworkInterface INTERFACE)
target_include_directories(NetworkInterface INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/network)

add_library(ParserClient INTERFACE)
target_include_directories(ParserClient INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/utility)
target_link_libraries(ParserClient INTERFACE json)

add_library(ParserServer INTERFACE)
target_include_directories(ParserServer INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/utility)
target_link_libraries(ParserClient INTERFACE json)

add_library(CommonValues INTERFACE)
target_include_directories(CommonValues INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/common)

add_executable(Server network/server/server.cpp db/database.cpp)
add_executable(Client network/client/client.cpp)
add_subdirectory(include)

target_link_libraries(Server PRIVATE asio ParserServer NetworkInterface CommonValues)
target_link_libraries(Client PRIVATE asio ParserClient NetworkInterface CommonValues)

add_executable(Main main.cpp)
target_link_libraries(Main PRIVATE asio)



