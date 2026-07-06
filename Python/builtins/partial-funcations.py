'''
Descripttion: 
Author: cyD
Date: 2021-08-25 03:54:48
LastEditTime: 2021-08-25 03:59:11
'''
import functools

# 输入字符串由二进制转为十进制
def int2_1(x, base=2):
    return int(x, base)

int2 = functools.partial(int, base=2)

