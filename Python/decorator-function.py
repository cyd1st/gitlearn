'''
Descripttion: 
Author: cyd
Date: 2021-08-24 11:50:10
LastEditTime: 2021-08-24 15:07:50
'''

import time

def log(func):
    def wrapper(*args, **kw):
        print("call %s():" % func.__name__)
        return func(*args, **kw)
    return wrapper

@log
def now():
    print(time.strftime("%Y-%m-%d %H:%M:%S", time.localtime()))

#
# >>> now()
# call now():
# 2021-08-24 15:06:34
# >>> now.__name__
# 'wrapper'
#