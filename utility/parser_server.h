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
        static void GenerateJson(T &message) {
            nlohmann::json j;
            j["message"] = message->message;
            j["name"] = message->client.client_name;
            message->message = std::move(to_string(j));
        };
    };

} // csc

#endif //CLIENTSERVERCHAT_PARSER_SERVER_H