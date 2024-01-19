#include <iostream>
#include "../include/animal.h"



int main() {
    Animal *aDog = new Dog();
    MakeHowl(aDog);

    Cat aCat;
    MakeHowl(&aCat);

    delete aDog;
    return 0;
}