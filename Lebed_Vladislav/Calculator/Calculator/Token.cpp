#pragma once

#include "Variable.h"
#include "Token.h"
#include "Consts.h"

Token_stream ts;

void Token_stream::ignore(char c)
{
    if (full && c == buffer.kind)
    {
        full = false;
        return;
    }
    full = false;

    char ch;
    while (cin >> ch)
    {
        if (ch == c)
        {
            return;
        }
    }
}

Token Token_stream::get()
{
    if (full)
    {
        full = false;
        return buffer;
    }

    char ch;
    cin >> ch;

    switch (ch)
    {
    case '(':
    case ')':
    case '+':
    case '-':
    case '*':
    case '/':
    case '%':
    case ';':
    case '=':
    case 'q':
    case '^':
    case '!':
    case 'h':
        return Token{ ch };
    case 'L':
        return Token{ let };

    case '.':
    case '0': case '1': case '2': case '3': case '4':
    case '5': case '6': case '7': case '8': case '9':
    {
        cin.putback(ch);
        double val;
        cin >> val;
        return Token{ number, val };
    }

    default:
        if (isalpha(ch))
        {
            string s;
            s += ch;
            while (cin.get(ch) &&
                (isalpha(ch) || isdigit(ch)))
                s += ch;
            cin.putback(ch);

            if (s == declkey)
            {
                return Token{ let };
            }
            return Token{ name, s };
        }
        error("Bad token");
    }
}

void Token_stream::putback(Token t)
{
    if (full == true)
    {
        error("putback() into a full buffer");
    }
    buffer = t;
    full = true;
}