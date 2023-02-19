#include <iostream>
#include <vector>
#include <iterator>
#include <string>
#include <fstream>

using namespace std;

void partial_nums(string &infile, string &oddfile, string &evenfile)
{
    ifstream in(infile);
    istream_iterator<int> it_in(in);
    istream_iterator<int> eof;

    ofstream outodd(oddfile);
    ofstream outeven(evenfile);
    ostream_iterator<int> it_out_odd(outodd, " ");
    ostream_iterator<int> it_out_even(outeven, "\n");

    while(it_in != eof) {
        if (*it_in % 2)
            *it_out_odd++ = *it_in;
        else *it_out_even++ = *it_in;
        it_in++;
    }
}
int main(int argc, char **argv)
{
    string in_file(argv[1]);
    string odd_file(argv[2]);
    string even_file(argv[3]);
    partial_nums(in_file, odd_file, even_file);
    return 0;
}