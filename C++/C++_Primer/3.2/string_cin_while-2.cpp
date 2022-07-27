#include <iostream>
#include <string>

using std::string;

int main(void) {
    string input;
    while (std::cin >> input);
    std::cout << input << std::endl;

    string a(input), b(input);
    std::cin >> a >> b;
    std::cout << a << " " << b << std::endl;
    return 0;
}

/*******
* 输入：
* aaa bbb
* [ctrl+d]
* 输出：
* bbb
* 说明：输出bbb后直接结束，为什么？
*******/

/*******
* 输入：
* aaa bbb[ctrl+d][ctrl+d]
* 输出：
* bbb
* 说明：输入两次 ctrl+d 结束 while 循环。为什么要两次？可能第一次表示bbb结束输入，第二次表示EOF,清空缓冲区。
*******/