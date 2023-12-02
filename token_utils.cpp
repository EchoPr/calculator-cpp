#include <string>
#include <iostream>
#include <cmath>
#include <vector>

#include "token_utils.h"
#include "token.h"
#include "token_stream.h"


void error(const std::string& mes)
{
	throw std::runtime_error(mes);
}

void error(const std::string& mes, const std::string& val)
{
	throw std::runtime_error(mes + val);
}


struct Variable
{
  std::string name;
  double value;

  Variable(std::string n, double v) : name{n}, value{v} {}
};

std::vector<Variable> var_table;

double get_value (const std::string& s)
{
    for (const auto& var : var_table)
    {
        if (var.name == s)
            return var.value;
    }

    error("get: undefined name ", s);
    return 0;
}

void set_value (const std::string& s, double d)
{
    for (auto& var : var_table)
    {
        if (var.name == s)
        {
            var.value = d;
            return;
        }
    }

    error("set: undefined name ", s);
}

bool is_declared (const std::string& s)
{
    for (const auto& var : var_table)
    {
        if (var.name == s)
            return true;
    }

    return false;
}

double define_name (const std::string& var, double val)
{
    if (is_declared(var))
        error(var, " declared twice");

    var_table.push_back(Variable{var, val});

    return val;
}

double expression (Token_stream&);

double process_math_function(std::string name, double num){
    if (name == "sin")
        return sin(num);
    else if (name == "tg")
        return tan(num);
    else if (name == "arctg")
        return atan(num); 
}

double primary (Token_stream& ts)
{
    Token t = ts.get();
    switch (t.kind)
    {
    case '(':
    {
        double d = expression(ts);
        t = ts.get();
        if (t.kind != ')')
            error("')' expected");
        return d;
    }

    case calc_consts::func:
    {
        double d = expression(ts);
        
        return process_math_function(t.name, d);
    }

    case '-':
        return -primary(ts);
    case '+':
        return +primary(ts);

    case calc_consts::number:
        return t.value;

    case calc_consts::name:
        return get_value(t.name);

    default:
        error("primary expected");
    }
}

double term (Token_stream& ts)
{
    double left = primary(ts);

    while (true)
    {
        Token t = ts.get();

        switch (t.kind)
        {
        case '*':
            left *= primary(ts);
            break;

        case '/':
        {
            double d = primary(ts);
            if (d == 0)
                error("divide by zero");
            left /= d;
            break;
        }

        case '%':
        {
            double d = primary(ts);
            if (d == 0)
                error("'%': divide by zero");
            left = std::fmod(left, d);
            break;
        }

        default:
            ts.putback(t);
            return left;
        }
    }
}

double expression (Token_stream& ts)
{
    double left = term(ts);

    while (true)
    {
        Token t = ts.get();

        switch (t.kind)
        {
        case '+':
            left += term(ts);
            break;

        case '-':
            left -= term(ts);
            break;

        default:
            ts.putback(t);
            return left;
        }
    }
}

double declaration (Token_stream& ts)
{
    Token t = ts.get();
    if (t.kind != calc_consts::name)
        error("name expected in declaration");

    std::string var = t.name;
    if (is_declared(var))
        error(var, " declared twice");

    t = ts.get();
    if (t.kind != '=')
        error("'=' missing in declaration of ", var);

    return define_name(var, expression(ts));
}

double statement (Token_stream& ts)
{
    Token t = ts.get();
    switch (t.kind)
    {
    case calc_consts::let:
        return declaration(ts);
    default:
        ts.putback(t);
        return expression(ts);
    }
}

void clean_up_mess (Token_stream& ts) { ts.ignore(calc_consts::print); }
