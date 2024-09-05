#include <iostream>
using namespace std;

class Animal {
public:
    Animal() {
        cout << "Animal constructor" << endl;
    }

    virtual ~Animal() {
        cout << "Animal destructor" << endl;
    }

    virtual void sound() {
        cout << "Animal sound" << endl;
    }

protected:
    int legs = 0;
};

class Dog : public Animal {
public:
    Dog() {
        legs = 4;
        cout << "Dog constructor" << endl;
    }

    ~Dog() {
        cout << "Dog destructor" << endl;
    }

    void sound() {
        cout << "Dog sound" << endl;
    }

    int getLegs() {
        return legs;
    }
};

class Cat : public Animal {
public:
    Cat() {
        legs = 4;
        cout << "Cat constructor" << endl;
    }

    ~Cat() {
        cout << "Cat destructor" << endl;
    }

    void sound() {
        cout << "Cat sound" << endl;
    }

    int getLegs() {
        return legs;
    }
};


void MakeHowl(Animal &animal) {
    animal.sound();
}

void MakeHowl(Animal *animal) {
    animal->sound();
}