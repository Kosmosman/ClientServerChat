//
// Created by Joaquina Daeron on 10/6/23.
//

#ifndef CLIENTSERVERCHAT_PARSER_CLIENT_H
#define CLIENTSERVERCHAT_PARSER_CLIENT_H

#include <json.hpp>
#include <algorithm>

namespace csc {
    template<typename T>
    class ParserClient {
    public:
        static void ParseJson(T &message) {
            nlohmann::json j = nlohmann::json::parse(message);
            std::string s = j["name"].get<std::string>() + ": " + j["message"].get<std::string>();
            message = std::move(s);
        };

        static void GenerateJson(T &message) {
            std::string s{message.begin(), message.end()};
            message = R"({"message":")" + s + "\"}";
        };
    };

} // csc

#endif //CLIENTSERVERCHAT_PARSER_CLIENT_H
