#include <cstdio>
#include <iostream>
#include "01_MyFILEClass.h"

using namespace std;

int main()
{
    try {
        File fileObject("01_MyFILEClass.h");
        const int BSIZE = 100;
        char buf[BSIZE] = {0};
        while (fgets(buf, BSIZE, fileObject.fp())) {
            fputs(buf, stdout);
        }
        fputc('\n', stdout);
    } catch (File::FileClassError &e) {
        cout << e.what() << endl;
        return EXIT_FAILURE;
    }

    return 0;
}