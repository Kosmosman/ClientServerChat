//
// Created by Joaquina Daeron on 10/6/23.
//

#ifndef CLIENTSERVERCHAT_PARSER_CLIENT_H
#define CLIENTSERVERCHAT_PARSER_CLIENT_H

#include "parser_interface.h"
#include <array>
#include "../common/common.h"

namespace csc {
    template <typename T>
    class ParserClient {
    public:
        T ParseJson(const T &message) override {
            std::string s{to_string(message["name"]) + ": " + to_string(message["message"]) + "\n"};
            T arr{};
            std::move(s.begin(), s.end(), arr.begin());
            return arr;
        };

        nlohmann::json GenerateJson(T message) override {
            return nlohmann::json(message);
        };
    };

} // csc

#endif //CLIENTSERVERCHAT_PARSER_CLIENT_H
