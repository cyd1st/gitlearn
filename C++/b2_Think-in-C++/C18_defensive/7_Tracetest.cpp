//: C03:Tracetst.cpp {-bor}
#include "../lib/require.h"
#include <fstream>
#include <iostream>
using namespace std;

#define TRACEON
#include "6_Trace.h"

int main()
{
    ifstream f("7_Tracetest.cpp");
    assure(f, "7_Tracetest.cpp");
    cout << f.rdbuf(); // Dumps file contents to file
} ///:~