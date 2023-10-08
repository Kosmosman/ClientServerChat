//
// Created by Joaquina Daeron on 10/6/23.
//

#ifndef CLIENTSERVERCHAT_PARSER_SERVER_H
#define CLIENTSERVERCHAT_PARSER_SERVER_H

#include <json.hpp>

namespace csc {
    template<typename T>
    class ParserServer {
        T ParseJson(T &message) {
            nlohmann::json json = nlohmann::json::parse(message);
            return json["message"].get<std::string>();
        };

        void GenerateJson(T message) {

        };
    };

} // csc

#endif //CLIENTSERVERCHAT_PARSER_SERVER_H