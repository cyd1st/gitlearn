#include <cstring> // for std::strcpy
#include <iostream>

using namespace std;

class String {
private:
    char *str; // Pointer to a C-style string
public:
    // Default constructor
    String() : str(nullptr) {}

    // Parameterized constructor
    String(const char *s)
    {
        if (s) {
            str = new char[strlen(s) + 1];
            strcpy(str, s);
        } else {
            str = nullptr;
        }
    }

    // Destructor
    ~String() { delete[] str; }

    // Shallow copy constructor
    String(const String &other)
    {
        str = other.str; // Only the pointer is copied, not the data
        cout << "Shallow copy called.\n";
    }

    // Deep copy constructor
    String(String &other, bool deep)
    {
        if (deep && other.str) {
            str = new char[strlen(other.str) + 1];
            strcpy(str, other.str); // Data is copied
            cout << "Deep copy called.\n";
        } else {
            str = other.str;
            cout << "Shallow copy called in deep copy constructor.\n";
        }
    }

    // Overloaded assignment operator for shallow copy
    String &operator=(const String &other)
    {
        if (this == &other)
            return *this; // Self-assignment check
        delete[] str;     // Avoid memory leak
        str = other.str;
        cout << "Shallow assignment called.\n";
        return *this;
    }

    // Overloaded assignment operator for deep copy
    String &deepAssign(const String &other)
    {
        if (this == &other)
            return *this; // Self-assignment check
        delete[] str;     // Avoid memory leak
        if (other.str) {
            str = new char[strlen(other.str) + 1];
            strcpy(str, other.str);
        } else {
            str = nullptr;
        }
        cout << "Deep assignment called.\n";
        return *this;
    }

    void print() const
    {
        if (str)
            cout << "String: " << str << endl;
        else
            cout << "String: (null)" << endl;
    }
};

int main()
{
    String original("Hello World!");
    String shallowCopy(original);             // Calls shallow copy constructor
    String deepCopy = String(original, true); // Calls deep copy constructor

    cout << "Original string: ";
    original.print();

    cout << "Shallow copy string: ";
    shallowCopy.print();

    cout << "Deep copy string: ";
    deepCopy.print();

    // Modify the original string and see the effect on copies
    original.deepAssign(String("Changed Original"));

    cout << "\nAfter changing the original string:\n";

    cout << "Original string: ";
    original.print();

    cout << "Shallow copy string: ";
    shallowCopy.print(); // Will be affected by the change

    cout << "Deep copy string: ";
    deepCopy.print(); // Not affected by the change

    return 0;
}

// 浅拷贝与深拷贝混用容易发生资源回收冲突，导致程序崩溃