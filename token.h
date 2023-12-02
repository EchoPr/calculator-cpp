#pragma once

#include <string>
#include <vector>

class Token{
public:
    char kind;
    double value;
    std::string name;

    Token(char ch) : kind{ch}, value{0} {}

    Token(char ch, double val) : kind{ch}, value{val} {}

    Token(char ch, std::string id) : kind{ch}, name{id} {}
};
