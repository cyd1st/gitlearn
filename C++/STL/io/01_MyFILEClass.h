//: C04:File.h
// stdio files wrapped.
#ifndef FILECLASS_H
#define FILECLASS_H
#include <cstdio>
#include <stdexcept>

class File {
    std::FILE *f;

public:
    struct FileClassError : std::runtime_error {
        FileClassError(const char *msg) : std::runtime_error(msg) {}
    };
    File(const char *fname, const char *mode = "r");
    ~File();
    std::FILE *fp(); // 废弃
};
#endif // FILECLASS_H ///:~