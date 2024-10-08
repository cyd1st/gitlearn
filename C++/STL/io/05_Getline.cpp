#include <fstream>
#include <iostream>

using namespace std;
int main()
{
    ofstream file("./out/test.txt", ios::app);
    file << "aaaa" << endl;
    file << "bbb";
    file.close();

    string line;
    ifstream file2("./out/test.txt");

    while (getline(file2, line)) {
        cout << line << endl;
    }

    if (file2.eof()) {
        cout << "eof" << endl;
    }
}