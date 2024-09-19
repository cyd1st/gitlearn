//: TestSuite:Suite.h
#ifndef SUITE_H
#define SUITE_H
#include "2_TestSuite_Test.h"
#include <stdexcept>
#include <vector>

using std::logic_error;
using std::vector;

namespace TestSuite {

class TestSuiteError : public logic_error {
public:
    TestSuiteError(const string &s = "") : logic_error(s) {}
};

class Suite {
    string name;
    ostream *osptr;
    vector<Test *> tests;
    void reset();
    // Disallowed ops:
    Suite(const Suite &);
    Suite &operator=(const Suite &);

public:
    Suite(const string &name, ostream *osptr = &cout) : name(name) { this->osptr = osptr; }
    string getName() const { return name; }
    long getNumPassed() const;
    long getNumFailed() const;
    const ostream *getStream() const { return osptr; }
    void setStream(ostream *osptr) { this->osptr = osptr; }
    void addTest(Test *t) noexcept(false);
    void addSuite(const Suite &);
    void run(); // Calls Test::run() repeatedly
    long report() const;
    void free(); // Deletes tests
};

} // namespace TestSuite
#endif // SUITE_H ///:~