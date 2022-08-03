#include "test.hpp"

int main() {
  int        a = 3;
  const int* cip = &a;
  const int* ip = cip;
  test<int>  A(a);
  int        b = (++a)++;

  A.operator++(a)++;
  A.begin()++;
}