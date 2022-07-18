#include <iostream>
#include <string>

using std::string;

int main() {
    string input;
    while (std::cin >> input);
    std::cout << input << std::endl;
    return 0;
}

/*******
* 输入：
* aaa bbb  ccc
* ddd
* [ctrl+d]
* 输出：
* ddd
* 说明：回车后加 ctrl+d 就可以结束 while 循环。
*******/

/*******
* 输入：
* aaa bbb[ctrl+d][ctrl+d]
* 输出：
* bbb
* 说明：输入两次 ctrl+d 结束 while 循环。为什么要两次？可能第一次表示bbb结束输入，第二次表示EOF,清空缓冲区。
*******/