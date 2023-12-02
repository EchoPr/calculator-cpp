#pragma once

#include "token.h"

class Token_stream
{
    bool full{false};
    Token buffer{'\0'};

public:
    Token_stream() {}

    Token get ();
    void putback (Token);

    void ignore (char);
};