#include <iostream>

using namespace std;

int main()
{
    int ia[3][4];
    int count = 0;
    for (int (&row)[4] : ia)
        for (int &col : row)
            col = count++;

    // v1
    for (int (&row)[4] : ia) {
        for (int col : row)
            cout << col << "\t";
        cout << endl;
    }
    cout << "-----------" << endl;
    // v2
    count = 0;
    for (int i = 0; i < 12; i++) {
        cout << ((int *)ia)[i] << "\t";
        count++;
        if (!(count % 4)) {
            cout << endl;
        }
    }
    cout << "-----------" << endl;
    // v3
    for (int (*p)[4] = ia; p != ia + 3; p++) {
        for (int *q = *p; q != *p + 4; q++) {
            cout << *q << "\t";
        }
        cout << endl;
    }
        
}