#pragma once

#include <string>

#include "token_stream.h"


namespace calc_consts {
    constexpr char quit = 'q';
    constexpr char print = ';';
    constexpr char number = '8';
    constexpr char name = 'a';
    constexpr char let = 'L';
    constexpr char func = 'F';

    const std::string sin_func = "sin";
    const std::string tg_func = "tg";
    const std::string arctg_func = "arctg";

    const std::string prompt = "> ";
    const std::string result = "= ";
    const std::string declkey = "var";
    const std::string quitkey = "quit";
    
}


void error(const std::string&);

void error(const std::string&, const std::string&);


struct Variable;

double get_value (const std::string&);

void set_value (const std::string&, double);

bool is_declared (const std::string&);

double expression (Token_stream&);

double define_name (const std::string&, double);

double primary (Token_stream&);

double term (Token_stream&);

double declaration (Token_stream&);

double statement (Token_stream&);

void clean_up_mess (Token_stream&);

