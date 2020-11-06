#pragma once
#include "std_lib_facilities.h"

bool is_declared(string s);
double get_value(string s);
double define_name(string var, double val);

struct Variable
{
    string name;
    double value;

    Variable(string n, double v)
        : name{ n }, value{ v }
    { }
};
