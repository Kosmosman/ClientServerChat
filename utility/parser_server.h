//
// Created by Joaquina Daeron on 10/6/23.
//

#ifndef CLIENTSERVERCHAT_PARSER_SERVER_H
#define CLIENTSERVERCHAT_PARSER_SERVER_H

#include "parser_interface.h"

namespace csc {
    template <typename T>
    class ParserServer  {
        T ParseJson(const nlohmann::json &message) override {

        };

        nlohmann::json GenerateJson(T message) override {

        };
    }

} // csc

#endif //CLIENTSERVERCHAT_PARSER_SERVER_H
