#include <iostream>
#include <string>
#include <vector>
#include <cmath>

#include "token.h"
#include "token_stream.h"
#include "token_utils.h"


Token_stream ts;

void calculate ()
{
    while (true)
        try
        {
            std::cout << calc_consts::prompt;
            Token t = ts.get();
            while (t.kind == calc_consts::print)
                t = ts.get();
            if (t.kind == calc_consts::quit)
                return;

            ts.putback(t);
            std::cout << calc_consts::result << statement(ts) << std::endl;
        }
        catch (std::runtime_error& e)
        {
            std::cerr << e.what() << std::endl;
            clean_up_mess(ts);
        }
}

int main ()
try
{
    define_name("pi", 3.1415926);
    define_name("e", 2.718281828);

    calculate();
}
catch (std::exception& e)
{
    std::cerr << "exception: " << e.what() << std::endl;
    return 1;
}
catch (...)
{
    std::cerr << "Oops, unknown exception" << std::endl;
    return 2;
}