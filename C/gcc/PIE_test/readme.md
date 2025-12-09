# PIE

## 性能对比

编译两个版本并测试
```bash
gcc -O2 -no-pie perf.c -o perf_nopie
gcc -O2 -fPIE -pie perf.c -o perf_pie
```

测试PIE是否有性能差别，理论上是有的，但应该很小。

## 地址对比


```bash
gcc -no-pie showaddr.c -o showaddr_nopie
gcc -fPIE -pie showaddr.c -o showaddr_pie
```

执行以下脚本，对比地址差异：
```bash
# 多次运行查看地址变化
echo "=== 非PIE版本（地址固定）==="
for i in {1..3}; do
    echo "运行 $i:"
    ./showaddr_nopie | head -1
done

echo -e "\n=== PIE版本（地址随机）==="
for i in {1..3}; do
    echo "运行 $i:"
    ./showaddr_pie | head -1
done
```
运行结果如下：
```
=== 非PIE版本（地址固定）===
运行 1:
Main function at: 0x40115f
运行 2:
Main function at: 0x40115f
运行 3:
Main function at: 0x40115f

=== PIE版本（地址随机）===
运行 1:
Main function at: 0x55b121fcc172
运行 2:
Main function at: 0x555f55709172
运行 3:
Main function at: 0x5642ecf73172
```
可以看到，非PIE版本和PIE版本在运行时，地址固定和不固定时，输出结果不同。
