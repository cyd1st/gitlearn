//{L} AutoCounter
#include "TPStash.h"
#include <fstream>
#include <iostream>
#include "AutoCounter.h"
using namespace std;

int main()
{
    PStash<AutoCounter> acStash;

    // test1
    for (int i = 0; i < 10; i++)
        acStash.add(AutoCounter::create());
    cout << "Removing 5 manually:" << endl;
    for (int j = 0; j < 5; j++)
        delete acStash.remove(j);
    cout << "Remove two without deleting them:" << endl;
    // ... to generate the cleanup error message.
    cout << acStash.remove(5) << endl;
    cout << acStash.remove(6) << endl;
    cout << "The destructor cleans up the rest:" << endl;
    // Repeat the test from earlier chapters:

    // test2
    ifstream in("TPStashTest.cpp");
    assure(in, "TPStashTest.cpp");
    PStash<string> stringStash;
    string line;
    while (getline(in, line))
        stringStash.add(new string(line));
    // Print out the strings:
    for (int u = 0; stringStash[u]; u++)
        cout << "[" << u << "] " << *stringStash[u] << endl;
} ///:~