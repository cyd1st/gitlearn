//: TestSuite:Test.h
#ifndef TEST_H
#define TEST_H
#include <cassert>
#include <iostream>
#include <string>
using std::cout;
using std::ostream;
using std::string;

// fail_() has an underscore to prevent collision with
// ios::fail(). For consistency, test_() and succeed_()
// also have underscores.

#define test_(cond) do_test(cond, #cond, __FILE__, __LINE__)
#define fail_(str) do_fail(str, __FILE__, __LINE__)

namespace TestSuite {

class Test {
    ostream *osptr;
    long nPass;
    long nFail;
    // Disallowed:
    Test(const Test &);
    Test &operator=(const Test &);

protected:
    void do_test(bool cond, const string &lbl, const char *fname, long lineno);
    void do_fail(const string &lbl, const char *fname, long lineno);

public:
    Test(ostream *osptr = &cout)
    {
        this->osptr = osptr;
        nPass = nFail = 0;
    }
    virtual ~Test() {}
    virtual void run() = 0;
    long getNumPassed() const { return nPass; }
    long getNumFailed() const { return nFail; }
    const ostream *getStream() const { return osptr; }
    void setStream(ostream *osptr) { this->osptr = osptr; }
    void succeed_() { ++nPass; }
    long report() const;
    virtual void reset() { nPass = nFail = 0; }
};

} // namespace TestSuite
#endif // TEST_H ///:~