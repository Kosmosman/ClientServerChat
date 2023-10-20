//
// Created by Joaquina Daeron on 10/6/23.
//

#ifndef CLIENTSERVERCHAT_PARSER_SERVER_H
#define CLIENTSERVERCHAT_PARSER_SERVER_H

#include <json.hpp>

namespace csc {
    template<typename T>
    class ParserServer {
    public:
        static void ParseName(T &message) {
            nlohmann::json j = nlohmann::json::parse(message.client.client_name);
            message.client.client_name = j["message"];
        }

        static void GenerateJson(T &message, T& name) {
            nlohmann::json j;
            j["message"] = message;
            j["name"] = name;
            message = std::move(to_string(j));
        };
    };

} // csc

#endif //CLIENTSERVERCHAT_PARSER_SERVER_H