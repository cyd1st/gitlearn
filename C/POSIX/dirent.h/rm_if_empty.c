// create by ai
// 删除目录示例
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

int rmdir_if_empty(const char *dirname)
{
    DIR *dir;
    struct dirent *entry;

    // 打开目录以检查是否为空
    if ((dir = opendir(dirname)) == NULL) {
        perror("opendir");
        return -1;
    }

    // 尝试读取目录中的条目
    if ((entry = readdir(dir)) != NULL) {
        // 如果有除了 . 和 .. 之外的条目，则目录不为空
        if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
            closedir(dir);
            printf("Directory '%s' is not empty.\n", dirname);
            return -1; // 目录不为空，无法删除
        }
    }
    closedir(dir);

    // 删除目录
    if (rmdir(dirname) == -1) {
        perror("rmdir");
        return -1;
    }
    printf("Directory '%s' removed successfully.\n", dirname);
    return 0;
}

int main()
{
    const char *dirname = "./out/test";
    rmdir_if_empty(dirname);
    return 0;
}