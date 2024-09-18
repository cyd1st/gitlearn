#include "TStack2.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

const string FILE_NAME = "TStack2Test.cpp";
int main() {
    ifstream in = ifstream(FILE_NAME);
    assure(in, "Open file " + FILE_NAME + " failed.");

    string textline;
    Stack<string> st;
    while (getline(in, textline)) {
        st.push(new string(textline));
    }

    Stack<string>::iterator stIterator(st);
    while (stIterator != st.end()) {
        cout << *stIterator << endl;
        stIterator++;
    }
    
    return 0;
} ///:~