
// #include <vector>

// struct A {
//   int a;
//   int b;
// };

// int main() {
//   std::vector<struct A>            v;
//   std::reverse_iterator<struct A*> ri = v.rbegin();
//   ri->a;
//   ft::reverse_iterator<struct A*> rr;
//   rr = ri;
//   rr->a;
// }
#include <iostream>
#include <vector>

#include "reverse_iterator.tcc"
int main() {
  std::vector<int>                                 v{0, 1, 2, 3};
  ft::reverse_iterator<std::vector<int>::iterator> iter = v.rbegin();
  std::cout << iter[0] << std::endl;
  std::cout << iter[1] << std::endl;
  std::cout << iter[2] << std::endl;
  std::cout << iter[3] << std::endl;
}
