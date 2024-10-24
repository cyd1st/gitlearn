#include <cctype>
#include <iostream>
#include <string>

class LoggerStreamBuf : public std::streambuf {
private:
    std::string buffer;  // 用于存储字符
    int logLevel;        // 日志级别
    bool loggingEnabled; // 日志记录是否开启

public:
    LoggerStreamBuf(int level, bool enabled = true) : logLevel(level), loggingEnabled(enabled) {}

    // 重写 overflow 方法以处理字符
    virtual int_type overflow(int_type c)
    {
        if (!loggingEnabled) {
            return c;
        }

        if (c != EOF) {
            char ch = static_cast<char>(c);
            buffer.push_back(ch); // 添加到缓冲区

            // 如果是换行符，则处理整个日志条目
            if (ch == '\n') {
                handleLogEntry();
                buffer.clear(); // 清空缓冲区
            }
        }

        return c;
    }

    void setLogLevel(int level) { logLevel = level; }

    void enableLogging(bool enabled) { loggingEnabled = enabled; }

private:
    void handleLogEntry()
    {
        std::string entry = buffer;
        if (entry.empty()) {
            return;
        }

        // 检查日志级别
        int currentLevel = extractLogLevel(entry);
        if (currentLevel >= logLevel) {
            // 添加 [LOG] 前缀
            entry = "[LOG] " + entry;
            // std::cout << entry << std::endl;
            std::cout << entry; // 原样输出，额外添加换行
        }
    }

    int extractLogLevel(const std::string &entry)
    {
        // 这里只是一个简单的示例，实际应用中可以根据日志格式解析日志级别
        // 假设日志格式为 "INFO: Message"
        if (entry.find("INFO:") != std::string::npos) {
            return 1; // INFO 级别
        } else if (entry.find("WARNING:") != std::string::npos) {
            return 2; // WARNING 级别
        } else if (entry.find("ERROR:") != std::string::npos) {
            return 3; // ERROR 级别
        }
        return 0; // 默认级别
    }
};

void testcase3()
{
    LoggerStreamBuf logger(2); // 设置日志级别为 WARNING
    std::ostream out(&logger); // 创建一个指向自定义 streambuf 的 std::ostream

    // 使用自定义流来输出不同级别的日志信息
    out << "INFO: This is an informational message" << std::endl;
    out << "WARNING: This is a warning message" << std::endl;
    out << "ERROR: This is an error message" << std::endl;

    // 更改日志级别并重新输出
    logger.setLogLevel(1); // 设置日志级别为 INFO
    out << "INFO: This is an informational message after changing log level" << std::endl;
    out << "WARNING: This is a warning message after changing log level" << std::endl;
    out << "ERROR: This is an error message after changing log level" << std::endl;

    // 禁用日志记录
    logger.enableLogging(false);
    out << "INFO: This will not be logged because logging is disabled" << std::endl;
}

int main()
{
    testcase3();
    return 0;
}