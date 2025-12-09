# PIE

## 性能对比

编译两个版本并测试
```bash
gcc -O2 -no-pie perf.c -o perf_nopie
gcc -O2 -fPIE -pie perf.c -o perf_pie
```

测试PIE是否有性能差别，理论上是有的，但应该很小。