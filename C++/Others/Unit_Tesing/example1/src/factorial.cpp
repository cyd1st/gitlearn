// 计算阶乘
unsigned long factorial(unsigned int n) {
    if (n == 0) return 1;
    return n * factorial(n - 1);
}