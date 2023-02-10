#include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>

using namespace std;

void print_vector(vector<int> &vi)
{
    for (auto i : vi)
        cout << i << " ";
    cout << endl;
}
void uni_cp()
{
    vector<int> vi = {1,2,3,4,5,6,7,8};
    vector<int> dest1, dest2;

    unique_copy(vi.cbegin(), vi.cend(), back_inserter(dest1));
    unique_copy(vi.cbegin(), vi.cend(), inserter(dest2, dest2.begin()));
    print_vector(dest1);
    print_vector(dest2);
}
int main()
{
    uni_cp();
    return 0;
}