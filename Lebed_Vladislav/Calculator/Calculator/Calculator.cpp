/*
  calculator08buggy.cpp

  Helpful comments removed.

  We have inserted 3 bugs that the compiler will catch and 3 that it won't.
*/

#include "Consts.h"
#include "std_lib_facilities.h"
#include "Token.h"
#include "Variable.h"
#include "Structure.h"

using namespace std;

void calculate()
{
    while (true)
        try
    {
        cout << prompt;
        Token t = ts.get();
        while (t.kind == print)
            t = ts.get();
        if (t.kind == quit)
            return;
        ts.putback(t);
        cout << result << statement() << endl;
    }
    catch (runtime_error& e)
    {
        cerr << e.what() << endl;
        clean_up_mess();
    }
}


int main()
try
{
    define_name("pi", 3.141592653589793);
    define_name("e", 2.718281828459045);

    calculate();

    return 0;
}
catch (exception& e)
{
    cerr << "exception: " << e.what() << endl;
    return 1;
}
catch (...)
{
    cerr << "Oops, unknown exception" << endl;
    return 2;
}