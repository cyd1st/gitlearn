#include "file_handler.h"

const char* FileException::what() const noexcept {
    static thread_local std::string message;
    message = "File Error [" + filePath + "]: " + std::runtime_error::what();
    return message.c_str();
}

FileHandler::FileHandler(const std::string& filename, const std::string& mode)
    : filePath(filename), fileHandle(nullptr) {
    fileHandle = openFile(filename, mode);
}

FileHandler::~FileHandler() noexcept {
    try {
        close();
    } catch (...) {
        std::cerr << "Error closing file in destructor: " << filePath << std::endl;
    }
}

FileHandler::FileHandler(FileHandler&& other) noexcept
    : filePath(std::move(other.filePath)),
      fileHandle(std::exchange(other.fileHandle, nullptr)) {}

FileHandler& FileHandler::operator=(FileHandler&& other) noexcept {
    if (this != &other) {
        close();
        filePath = std::move(other.filePath);
        fileHandle = std::exchange(other.fileHandle, nullptr);
    }
    return *this;
}

std::string FileHandler::readLine() {
    if (isClosed()) {
        throw FileException(filePath, "File is closed");
    }
    char buffer[4096];
    if (std::fgets(buffer, sizeof(buffer), fileHandle)) {
        return buffer;
    }
    if (std::feof(fileHandle)) {
        throw std::runtime_error("End of file reached");
    }
    throw FileException(filePath, "Read error");
}

size_t FileHandler::read(void* ptr, size_t size, size_t count) {
    if (isClosed()) {
        throw FileException(filePath, "File is closed");
    }
    size_t result = std::fread(ptr, size, count, fileHandle);
    if (result != count && std::ferror(fileHandle)) {
        throw FileException(filePath, "Read operation failed");
    }
    return result;
}

size_t FileHandler::write(const void* ptr, size_t size, size_t count) {
    if (isClosed()) {
        std::cerr << "Attempt to write to closed file: " << filePath << std::endl;
        throw FileException(filePath, "File is closed");
    }
    size_t result = std::fwrite(ptr, size, count, fileHandle);
    if (result != count) {
        std::cerr << "Write error on file: " << filePath 
                  << ", fwrite returned: " << result << std::endl;
        throw FileException(filePath, "Write operation failed");
    }
    return result;
}

void FileHandler::seek(long offset, int whence) {
    if (isClosed()) {
        throw FileException(filePath, "File is closed");
    }
    if (std::fseek(fileHandle, offset, whence) != 0) {
        throw FileException(filePath, "Seek operation failed");
    }
}

long FileHandler::tell() const {
    if (isClosed()) {
        throw FileException(filePath, "File is closed");
    }
    long pos = std::ftell(fileHandle);
    if (pos == -1L) {
        throw FileException(filePath, "Tell operation failed");
    }
    return pos;
}

void FileHandler::flush() {
    if (isClosed()) {
        throw FileException(filePath, "File is closed");
    }
    if (std::fflush(fileHandle) != 0) {
        throw FileException(filePath, "Flush operation failed");
    }
}

FILE* FileHandler::openFile(const std::string& filename, const std::string& mode) {
    FILE* f = std::fopen(filename.c_str(), mode.c_str());
    if (!f) {
        throw FileException(filename, "Failed to open file with mode: " + mode);
    }
    return f;
}

void FileHandler::close() {
    if (fileHandle) {
        FILE* tmp = fileHandle;
        fileHandle = nullptr;
        if (std::fclose(tmp) != 0) {
            std::cerr << "Error closing file: " << filePath << std::endl;
        }
    }
}