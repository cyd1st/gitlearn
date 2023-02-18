#include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

void istream_iterator_acc()
{
    istream_iterator<int> input(cin);
    istream_iterator<int> eof;
    int i = accumulate(input, eof, 0);
    cout << i << endl;
}
void istream_iterator_test()
{
    istream_iterator<int> input(cin);
    istream_iterator<int> eof;
    vector<int> vi(input, eof);
    for (int i : vi)
        cout << i << " ";
    cout << endl;
}
int main()
{
    istream_iterator_acc();
    istream_iterator_test();
    return 0;
}