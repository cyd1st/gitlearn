//: C04:Datagen.cpp
// Test data generator.
// 用于生成测试数据
//{L} DataLogger
#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <fstream>
#include "../lib/require.h"
#include "01_DataLogger.h"
using namespace std;

int main()
{
    time_t timer;
    srand(time(&timer)); // Seed the random number generator
    ofstream data("./out/data.txt");
    assure(data, "./out/data.txt");
    ofstream bindata("./out/data.bin", ios::binary);
    assure(bindata, "./out/data.bin");

    for (int i = 0; i < 100; i++, timer += 55) {
        // Zero to 199 meters:
        double newdepth = rand() % 200;
        double fraction = rand() % 100 + 1;
        newdepth += 1.0 / fraction;

        double newtemp = 150 + rand() % 200; // Kelvin
        fraction = rand() % 100 + 1;
        newtemp += 1.0 / fraction;
        const DataPoint d(timer, Coord(45, 20, 31), Coord(22, 34, 18), newdepth, newtemp);
        data << d << endl;
        bindata.write(reinterpret_cast<const char *>(&d), sizeof(d));
    }
} ///:~