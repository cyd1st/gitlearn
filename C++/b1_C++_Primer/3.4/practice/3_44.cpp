#include <iostream>

using namespace std;
using int_array = int[4];
int main()
{
    int ia[3][4];
    int count = 0;
    for (int (&row)[4] : ia)
        for (int &col : row)
            col = count++;

    // v3
    for (int_array *p = ia; p != ia + 3; p++) {
        for (int *q = *p; q != *p + 4; q++) {
            cout << *q << "\t";
        }
        cout << endl;
    }
        
}