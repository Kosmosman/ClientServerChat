CMAKE_MINIMUM_REQUIRED(VERSION 3.5)
PROJECT(ClientServerChat VERSION 1.0 LANGUAGES CXX)
SET(CMAKE_CXX_STANDARD 20)

add_library(asio INTERFACE)
target_include_directories(asio INTERFACE "asio-1.28.0/include")

add_library(json INTERFACE)
target_include_directories(json INTERFACE "json/single_include/nlohmann")
