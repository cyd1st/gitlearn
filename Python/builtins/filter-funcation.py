'''
Descripttion: 
Author: cyd
Date: 2021-08-23 16:33:02
LastEditTime: 2021-08-23 16:33:43
'''

# 过滤f开头的单词
def filter_fword(word):
    if word[0] == 'F' or word[0] == 'f':
        return 0
    else:
        return 1