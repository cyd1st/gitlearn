#include <iostream>
#include <vector>
#include <string>
#include <iterator>
#include <fstream>

using namespace std;

void read_text(char *filename)
{
    ifstream input(filename);
    istream_iterator<string> it_str(input);
    istream_iterator<string> eof;

    vector<string> vs;
    while (it_str != eof)
        vs.push_back(*it_str++);
    
    for(const auto &s : vs)
        cout << s << " ";
    cout << endl;
}
int main(int argc, char **argv)
{
    read_text(argv[1]);
    return 0;
}