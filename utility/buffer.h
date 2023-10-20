//
// Created by Joaquina Daeron on 10/11/23.
//

#ifndef CLIENTSERVERCHAT_BUFFER_H
#define CLIENTSERVERCHAT_BUFFER_H

#include <vector>
#include <string>

namespace csc {

    template<typename T = char>
    class Buffer : public std::vector<T> {
    public:
        explicit Buffer(std::size_t size) : std::vector<T>(size) {};

        explicit Buffer(std::string s) { this->insert(this->begin(), s.begin(), s.end()); }

        explicit Buffer(std::string &&s) { std::move(s.begin(), s.end(), this->begin()); }

        explicit Buffer(const std::vector<T> &v) : std::vector<T>(v) {};

        explicit Buffer(std::vector<T> &&v) : std::vector<T>(std::move(v)) {};

        Buffer &operator()(std::string&& s) {
            std::move(s.begin(), s.end(), this->begin());
            return *this;
        }

        Buffer &operator=(const std::string &s) {
            this->resize(s.size());
            std::copy(s.begin(), s.end(), this->begin());
            return *this;
        }

        Buffer &operator=(std::string &&s) {
            this->resize(s.size());
            std::move(s.begin(), s.end(), this->begin());
            return *this;
        }
    };

} // csc

#endif //CLIENTSERVERCHAT_BUFFER_H
