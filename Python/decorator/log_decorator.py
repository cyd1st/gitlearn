import datetime
import time

# 装饰器就是将一个函数封装成另一个函数（装饰器返回包装后的函数）
# 原函数（被包装的函数）就在包装后的函数中执行。获取原函数的返回值，
# 作为包装后的函数的返回值（也就是原函数和包装后的函数执行结果是一样的）。
# 
# 下面是一个装饰器函数, 计算函数的运行时间：
def time_duration(fun):
    '''
    装饰器函数，添加函数执行时间。
    @parm: 入参``fun``为要包装的函数。
    @return: 包装后的函数。
    '''
    def fun_wrapper(*args, **kw):
        '''
        fun_wrapper 的入参``*args, **kw``其实就是 func 的入参。也就是：
            fun_wrapper 入参 = fun 入参
            fun_wrapper 返回值 = fun 返回值
        那么，fun_wrapper 就可以看作和 fun 相等。
        '''
        start = time.time()
        result = fun(*args, **kw)
        print("函数", fun.__name__, "执行时间:", time.time() - start)
        return result
    
    return fun_wrapper

# 装饰器只能在函数定义的时候用
@time_duration
def now():
    '''打印当前时间的函数。'''
    cur_time = datetime.datetime.now()
    now_time = cur_time.strftime("%Y-%m-%d %H:%M:%S")
    print(now_time)
    # time.sleep(1) # 使装饰器效果更明显

# now()

print(now.__name__) # fun_wrapper
# 此时发现 now 函数的 __name__ 属性变了，实际很好理解
# now() 事实上就是 fun_wrapper 函数了