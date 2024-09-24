#include "01_MyFILEClass.h"
#include <cstddef>
#include <cstdlib>

using namespace std;

File::File(const char *fname, const char *mode)
{
    if ((f = fopen(fname, mode)) == NULL) {
        throw FileClassError("Error opening file");
    }
}

File::~File() { fclose(f); }

FILE *File::fp() { return f; }