#include <algorithm>
#include <iomanip>
#include <iostream>
#include <memory>
#include <vector>

template <typename Cont>
void print_cont(const std::string& tag, Cont c) {
  std::cout << tag << ": ";
  for (typename Cont::iterator it = c.begin(); it != c.end(); ++it) {
    std::cout << *it << ' ';
  }
  std::cout << std::endl;
}

#include <algorithm>
#include <iostream>
#include <random>
#include <vector>

// int main() {
//   std::vector<int> v1{1, 2, 3, 4};
//   std::vector<int> v2{1, 2, 3, 4};

//   std::mt19937 g{std::random_device{}()};
//   while (!std::lexicographical_compare(v1.begin(), v1.end(), v2.begin(), v2.end())) {
//     for (auto c : v1)
//       std::cout << c << ' ';
//     std::cout << ">= ";
//     for (auto c : v2)
//       std::cout << c << ' ';
//     std::cout << '\n';

//     std::shuffle(v1.begin(), v1.end(), g);
//     std::shuffle(v2.begin(), v2.end(), g);
//   }

//   for (auto c : v1)
//     std::cout << c << ' ';
//   std::cout << "< ";
//   for (auto c : v2)
//     std::cout << c << ' ';
//   std::cout << '\n';
// }

template <typename T>
class Comp {
 public:
  bool operator()(const T& o1, const T& o2) {
    std::cout << "o1 : " << o1 << std::endl;
    std::cout << "o2 : " << o2 << std::endl;
    return o1 > o2;
  }
};

// bool cmp(int& a, int& b) {
//   std::cout << "o1 : " << a << std::endl;
//   std::cout << "o2 : " << b << std::endl;
//   return (a >= b);
// }

int main() {
  {
    std::vector<int> v1;
    std::vector<int> v2;
    Comp<int>        c;

    v1.assign(3, 2);
    v2.assign(3, 2);
    v1.push_back(2);
    v2.push_back(3);

    print_cont("v1", v1);
    print_cont("v2", v2);

    bool res1 = std::lexicographical_compare(v1.begin(), v1.end(), v2.begin(), v2.end());

    std::cout << res1 << std::endl;

    bool res2 = std::lexicographical_compare(v1.begin(), v1.end(), v2.begin(), v2.end(), c);

    std::cout << res2 << std::endl;
  }
  {
    std::vector<int> v1;
    std::vector<int> v2;

    v1.assign(3, 3);
    v2.assign(3, 2);

    print_cont("v1", v1);
    print_cont("v2", v2);

    bool res = std::lexicographical_compare(v1.begin(), v1.end(), v2.begin(), v2.end());

    std::cout << res << std::endl;
  }
  {
    std::vector<int> v1;
    std::vector<int> v2;

    v1.assign(3, 2);
    v2.assign(3, 3);

    print_cont("v1", v1);
    print_cont("v2", v2);

    bool res = std::lexicographical_compare(v1.begin(), v1.end(), v2.begin(), v2.end());

    std::cout << res << std::endl;
  }
}
