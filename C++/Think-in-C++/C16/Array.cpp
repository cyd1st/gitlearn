#include "../lib/require.h"
#include <iostream>
using namespace std;

template<class T>
class Array {
  enum { size = 100 };
  T A[size];
public:
  T& operator[](int index);
};

template<class T>
T& Array<T>::operator[](int index) {
    require(index >= 0 && index < size, "Index out of range.");
    return A[index];
}

int main() {
  Array<int> ia;
  Array<float> fa;
  for (int i = 0; i < 20; i++) {
    ia[i] = i * i;
    fa[i] = float(i) * 1.414;
  }
  for (int j = 0; j < 20; j++)
    cout << j << ": " << ia[j] << ", " << fa[j] << endl;

  Array<double> da;
  da[1] = 1.234354356546;
} ///:~