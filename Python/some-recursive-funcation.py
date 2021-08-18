'''
Descripttion: 一些用递归写的函数练习
Author: cyD
Date: 2021-08-19 04:36:25
LastEditTime: 2021-08-19 04:52:10
'''

# 数组和
def SumOfArray(arr):
    if len(arr) == 0:
        return 0
    return arr[0] + SumOfArray(arr[1:])


# 数组长度
def LenOfList(list):
    if list == []:
        return 0
    else:
        return 1 + LenOfList(list[1:])

# 列表最大数
def MaxOfList(list):
    if list == []:
        return None
    if len(list) == 1:
        return list[0]
    return list[0] if list[0]>MaxOfList(list[1:]) else MaxOfList(list[1:])