#include <fstream>
#include <iostream>
#include "01_DataLogger.h"

int main()
{
    std::ifstream d("./out/data.bin", std::ios::binary);
    DataPoint data;
    while (d.read((char *)(&data), sizeof(data))) {
        std::cout << data << std::endl;
    }
    return 0;
}
