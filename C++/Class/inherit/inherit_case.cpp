#include <iostream>
class Base {
    int privateVal;
    void privateFunc() { std::cout << "private function." << std::endl; }

public:
    int publicVal;
    void setPrivateVal(int v) { privateVal = v; }

protected:
    int protectedVal;
    void protectedFunc() { std::cout << "protected function." << std::endl; }
};

class PublicDerive : public Base {
public:
    void callPrivateFunc()
    {
        // privateFunc();
        setPrivateVal(2); // 可以间接设置基类的private成员
        protectedFunc();
    }
};

class PrivateDerive : private Base {
public:
    void callPrivateFunc()
    {
        // privateFunc();
        setPrivateVal(2);
        protectedFunc();
    }
};

int main()
{
    PublicDerive pd;
    pd.setPrivateVal(3); // 基类的 pulic 还是 public

    PrivateDerive pd2;
    // pd2.setPrivateVal(2); // // 基类的 pulic 不是 public
}