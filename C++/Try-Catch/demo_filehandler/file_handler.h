#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#include <iostream>
#include <fstream>
#include <memory>
#include <utility>
#include <string>
#include <cstring>
#include <system_error>
#include <stdexcept>

class FileException : public std::runtime_error {
public:
    explicit FileException(const std::string& filename, const std::string& msg)
        : std::runtime_error(msg), filePath(filename) {}

    const char* what() const noexcept override;
    const std::string& path() const noexcept { return filePath; }

private:
    std::string filePath;
};

class FileHandler {
public:
    explicit FileHandler(const std::string& filename, const std::string& mode = "r");
    ~FileHandler() noexcept;

    // 移动语义支持
    FileHandler(FileHandler&& other) noexcept;
    FileHandler& operator=(FileHandler&& other) noexcept;

    // 禁止拷贝操作（单次声明）
    FileHandler(const FileHandler&) = delete;
    FileHandler& operator=(const FileHandler&) = delete;

    std::string readLine();
    size_t read(void* ptr, size_t size, size_t count);
    size_t write(const void* ptr, size_t size, size_t count);
    void seek(long offset, int whence = SEEK_SET);
    long tell() const;
    void flush();
    void close();

    FILE* get() const noexcept { return fileHandle; }
    bool isClosed() const noexcept { return !fileHandle; }

private:
    std::string filePath;
    FILE* fileHandle;

    FILE* openFile(const std::string& filename, const std::string& mode);
};

#endif // FILE_HANDLER_H