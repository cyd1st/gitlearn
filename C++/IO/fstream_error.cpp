/**
 判断文件打开失败（is_open）的原因的示例。
 
 关键步骤：
    - 创建文件 file.txt 并设置为只读 chmod 400 file.txt。
 */

#include <iostream>
#include <fstream>
#include <cerrno>
#include <cstring>
#include <thread>
#include <vector>
#include <sys/stat.h>
#include <mutex>

std::mutex mtx;

/** 打印文件的权限，确保文件确实是只读的 */
void print_file_permissions(const std::string& filename)
{
    struct stat file_stat;
    if (stat(filename.c_str(), &file_stat) == 0) {
        std::cout << "文件权限: " << (file_stat.st_mode & S_IRUSR ? "读" : "-")
                                  << (file_stat.st_mode & S_IWUSR ? "写" : "-")
                                  << (file_stat.st_mode & S_IXUSR ? "执行" : "-") << std::endl;
    } else {
        std::cerr << "无法获取文件权限" << std::endl;
    }
}

void thread_function(const std::string& filename)
{
    std::lock_guard<std::mutex> lock(mtx);
    std::ofstream file(filename);
    if (!file.is_open()) {
        // 使用线程局部存储的 errno
        int errsv = errno;
        std::cerr << "线程 " << std::this_thread::get_id() << " 文件打开失败，错误代码：" << errsv << std::endl;
        std::cerr << "错误详情：" << strerror(errsv) << std::endl;
    } else {
        std::cout << "线程 " << std::this_thread::get_id() << " 文件成功打开" << std::endl;
        file.close();
    }
}

int main()
{
    const std::string filename = "./file.txt";
    // debug使用
    print_file_permissions(filename);

    const int num_threads = 5;

    std::vector<std::thread> threads;
    for (int i = 0; i < num_threads; ++i) {
        threads.emplace_back(thread_function, filename);
    }

    for (auto& t : threads) {
        t.join();
    }

    return 0;
}