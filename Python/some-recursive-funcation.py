# recursive function

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
