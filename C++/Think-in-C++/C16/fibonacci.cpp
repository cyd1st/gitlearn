#include "../lib/require.h"

int fibonacci(int n) {
  const int sz = 100;
  require(n < sz, "fibonacci n can't greater than 100.");
  static int f[sz]; // Initialized to zero

  if (f[n] != 0) {
    return f[n];
  }

  f[0] = f[1] = 1;
  // Scan for unfilled array elements:
  int i;
  for(i = 0; i < sz; i++)
    if(f[i] == 0) break;
  while(i <= n) {
    f[i] = f[i-1] + f[i-2];
    i++;
  }
  return f[n];
} ///:~