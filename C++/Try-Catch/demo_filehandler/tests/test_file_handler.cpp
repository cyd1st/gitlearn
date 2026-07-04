#include <gtest/gtest.h>
#include "file_handler.h"

// 测试不存在的文件读取
TEST(FileHandlerTest, ConstructorThrowsOnNonexistentFile) {
    EXPECT_THROW({
        FileHandler badFile("nonexistent.txt");
    }, FileException);
}

// 验证关闭后文件操作异常
TEST(FileHandlerTest, ReadAfterCloseThrowsException) {
    FileHandler writer("readonly.txt", "w");
    const char* data = "Test data\n";
    writer.write(data, 1, std::strlen(data));

    // 显式关闭文件
    writer.close();

    // 验证关闭后尝试读取文件会抛出异常
    EXPECT_THROW({
        writer.readLine();
    }, FileException);
}

// 验证空文件读取异常
TEST(FileHandlerTest, ReadEmptyFileThrowsException) {
    {
        FILE* f = std::fopen("empty.txt", "w");
        std::fclose(f);
    }

    FileHandler reader("empty.txt");
    EXPECT_THROW(reader.readLine(), std::runtime_error);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    int result = RUN_ALL_TESTS();
    
    // 测试完成后清理生成的临时文件
    std::remove("readonly.txt");
    std::remove("empty.txt");
    std::remove("nonexistent.txt");  // 这个文件可能不存在，但无害
    
    return result;
}