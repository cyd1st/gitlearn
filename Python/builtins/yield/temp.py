import dis

def gen():
    x = yield 1
    return x

async def coro():
    return 1

print("=== 生成器 ===")
dis.dis(gen)
print("=== 协程 ===")
dis.dis(coro)
