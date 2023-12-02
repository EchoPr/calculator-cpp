#include <iostream>
#include <cmath>
#include <vector>

#include "token_stream.h"
#include "token_utils.h"


void Token_stream::putback(Token t)
{
    if (full)
        error("putback() into a full buffer");

    buffer = t;
    full = true;
}

std::vector<std::string> nesting_functions;  

Token Token_stream::get()
{
    if (full)
    {
        full = false;
        return buffer;
    }

    char ch;
    std::cin >> ch;

    switch (ch)
    {
    case '(':
    case ')':
    case '+':
    case '-':
    case '*':
    case '/':
    case '%':
    case calc_consts::print:
    case '=':
        return Token{ch};

    case '.':
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
    {
        std::cin.putback(ch);
        double val;
        std::cin >> val;
        return Token{calc_consts::number, val};
    }

    default:
        if (isalpha(ch))
        {
            std::string s;
            s += ch;
            while (std::cin.get(ch) && (isalpha(ch) || isdigit(ch)))
                s += ch;
            std::cin.putback(ch);

            if (s == calc_consts::declkey)
                return Token{calc_consts::let};

            if (s == calc_consts::quitkey)
                return Token{calc_consts::quit};

            if (
                s == calc_consts::sin_func ||
                s == calc_consts::tg_func ||
                s == calc_consts::arctg_func 
                ){
                return Token{
                    calc_consts::func,
                    s
                };
            }

            return Token{calc_consts::name, s};
        }
        error("bad token");
    }
}

void Token_stream::ignore(char c)
{
    if (full && c == buffer.kind)
    {
        full = false;
        return;
    }
    full = false;

    for (char ch; std::cin >> ch;)
    {
        if (ch == c)
            return;
    }
}

