#include <iostream>
#include <string>

using std::string;
using std::cout;
using std::endl;

int main() {
    string s1;
    string s2 = "Hello world!";
    string s3 = s2;
    string s4(s2);
    string s5("Ha");
    string s6(5, 'a');

    cout << "s1: " << s1 << endl;
    cout << "s2: " << s2 << endl;
    cout << "s3: " << s3 << endl;
    cout << "s4: " << s4 << endl;
    cout << "s5: " << s5 << endl;
    cout << "s6: " << s6 << endl;

    return 0;
}

// s1: 
// s2: Hello world!
// s3: Hello world!
// s4: Hello world!
// s5: Ha
// s6: aaaaa