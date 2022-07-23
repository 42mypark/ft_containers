#include <iomanip>
#include <iostream>
#include <memory>
#include <vector>

// #include "vector.hpp"

int main() {
  // {
  //   int              sz = 100;
  //   std::vector<int> v(3);

  //   auto cap = v.capacity();
  //   std::cout << "Initial size: " << v.size() << ", capacity: " << cap << '\n';

  //   std::cout << "\nDemonstrate the capacity's growth policy."
  //                "\nSize:  Capacity:  Ratio:\n"
  //             << std::left;
  //   while (sz-- > 0) {
  //     v.push_back(sz);
  //     if (cap != v.capacity()) {
  //       std::cout << std::setw(7) << v.size() << std::setw(11) << v.capacity() << std::setw(10)
  //                 << v.capacity() / static_cast<float>(cap) << '\n';
  //       cap = v.capacity();
  //     }
  //   }

  //   std::cout << "\nFinal size: " << v.size() << ", capacity: " << v.capacity() << '\n';
  // }

  // {
  // 	std::vector<int> v1;
  // 	std::vector<int> v2;

  // 	v1.push_back(1);
  // 	v1.push_back(2);

  // 	v2.push_back(3);
  // 	v2.push_back(2);
  // 	v2.push_back(1);

  // 	v1 = v2;

  // 	std::cout << 	v1.capacity() << std::endl;
  // 	std::cout <<  v2.capacity() << std::endl;
  // 	// for (std::vector<int>::iterator it = v1.begin(); it != v1.end(); ++it)
  // 	// {
  // 	// 	std::cout << *it << std::endl;
  // 	// }

  // }

  // {
  //   std::vector<int> v;
  //   v.assign(3, 3);
  //   std::cout << v.capacity() << std::endl;
  //   std::cout << v[-1] << std::endl;
  //   std::cout << v[111] << std::endl;
  // }
  // {
  //   std::vector<int> c;
  //   c.push_back(1);
  //   c.push_back(2);
  //   c.push_back(3);
  //   c.push_back(4);
  //   c.push_back(5);
  //   c.push_back(6);
  //   std::cout << *(c.erase(c.end() - 4, c.end() - 2)) << std::endl;
  //   for (auto it = c.begin(); it != c.end(); ++it) {
  //     std::cout << *it << ' ';
  //   }
  // }
  // {
  //   ft::vector<int> c;
  //   c.push_back(1);
  //   c.push_back(2);
  //   c.push_back(3);
  //   c.push_back(4);
  //   c.push_back(5);
  //   c.push_back(6);
  //   // std::cout << *(c.begin() + 1) << std::endl;
  //   // std::cout << *(c.erase(c.end() - 1)) << std::endl;
  // }

  // {
  //   std::vector<int> c;
  //   c.push_back(1);
  //   c.push_back(2);
  //   c.push_back(3);
  //   c.push_back(4);
  //   c.push_back(5);
  //   c.push_back(6);
  //   for (auto it = c.begin(); it != c.end(); ++it) {
  //     std::cout << *it << ' ';
  //   }
  //   std::cout << '\n' <<  *(c.insert(c.begin() + 2, 7)) << std::endl;

  //   for (auto it = c.begin(); it != c.end(); ++it) {
  //     std::cout << *it << ' ';
  //   }
  // }

  // {
  //   std::vector<int> c;
  //   c.push_back(1);
  //   c.push_back(2);
  //   std::cout << c.capacity() << std::endl;
  //   c.insert(c.begin() + 1, 1, -1);
  //   std::cout << c.capacity() << std::endl;
  //   for (auto it = c.begin(); it != c.end(); ++it) {
  //     std::cout << *it << ' ';
  //   }
  // }

  {
    std::vector<int> c;
    c.push_back(1);
    c.push_back(2);
    c.push_back(3);
    std::cout << c.capacity() << std::endl;
    c.resize(5, 0);
    std::cout << c.capacity() << std::endl;
    for (auto it = c.begin(); it != c.end(); ++it) {
      std::cout << *it << ' ';
    }
  }
}
