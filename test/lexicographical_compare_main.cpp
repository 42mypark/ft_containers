#include <algorithm>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <memory>
#include <random>
#include <vector>

#include "lexicographical_compare.tcc"
#include "macro.hpp"

template <typename Cont>
void print_cont(const std::string& tag, Cont c) {
  std::cout << tag << ": ";
  for (typename Cont::iterator it = c.begin(); it != c.end(); ++it) {
    std::cout << *it << ' ';
  }
  std::cout << std::endl;
}

struct RNG {
  int operator()(int n) { return std::rand() / (1.0 + RAND_MAX) * n; }
};

int main() {
  TITLE("lexicographical_compare");
  std::srand(time(NULL));
  std::vector<int> v1;
  v1.push_back(1);
  v1.push_back(2);
  v1.push_back(3);
  v1.push_back(4);

  {
    SUBTITLE("Less");
    std::vector<int> v2(v1);
    while (!ft::lexicographical_compare(v1.begin(), v1.end(), v2.begin(), v2.end())) {
      for (std::vector<int>::iterator c = v1.begin(); c != v1.end(); ++c)
        std::cout << *c << ' ';
      std::cout << ">= ";
      for (std::vector<int>::iterator c = v2.begin(); c != v2.end(); ++c)
        std::cout << *c << ' ';
      std::cout << '\n';

      std::random_shuffle(v1.begin(), v1.end());
      std::random_shuffle(v2.begin(), v2.end());
    }
    for (std::vector<int>::iterator c = v1.begin(); c != v1.end(); ++c)
      std::cout << *c << ' ';
    std::cout << " < ";
    for (std::vector<int>::iterator c = v2.begin(); c != v2.end(); ++c)
      std::cout << *c << ' ';
    std::cout << '\n';
  }

  std::cout << '\n';

  {
    SUBTITLE("Grater");
    std::vector<int> v2(v1);
    ft::Grater<int>  g;
    while (!ft::lexicographical_compare(v1.begin(), v1.end(), v2.begin(), v2.end(), g)) {
      for (std::vector<int>::iterator c = v1.begin(); c != v1.end(); ++c)
        std::cout << *c << ' ';
      std::cout << "<= ";
      for (std::vector<int>::iterator c = v2.begin(); c != v2.end(); ++c)
        std::cout << *c << ' ';
      std::cout << '\n';

      std::random_shuffle(v1.begin(), v1.end());
      std::random_shuffle(v2.begin(), v2.end());
    }
    for (std::vector<int>::iterator c = v1.begin(); c != v1.end(); ++c)
      std::cout << *c << ' ';
    std::cout << " > ";
    for (std::vector<int>::iterator c = v2.begin(); c != v2.end(); ++c)
      std::cout << *c << ' ';
    std::cout << '\n';
  }

  {
    SUBTITLE("GraterEqual");
    std::vector<int>     v2(v1);
    ft::GraterEqual<int> ge;

    std::random_shuffle(v1.begin(), v1.end());
    std::random_shuffle(v2.begin(), v2.end());
    while (!ft::lexicographical_compare(v1.begin(), v1.end(), v2.begin(), v2.end(), ge)) {
      for (std::vector<int>::iterator c = v1.begin(); c != v1.end(); ++c)
        std::cout << *c << ' ';
      std::cout << " < ";
      for (std::vector<int>::iterator c = v2.begin(); c != v2.end(); ++c)
        std::cout << *c << ' ';
      std::cout << '\n';

      std::random_shuffle(v1.begin(), v1.end());
      std::random_shuffle(v2.begin(), v2.end());
    }
    for (std::vector<int>::iterator c = v1.begin(); c != v1.end(); ++c)
      std::cout << *c << ' ';
    std::cout << ">= ";
    for (std::vector<int>::iterator c = v2.begin(); c != v2.end(); ++c)
      std::cout << *c << ' ';
    std::cout << '\n';
  }

  {
    SUBTITLE("LessEqual");
    std::vector<int>   v2(v1);
    ft::LessEqual<int> le;

    std::random_shuffle(v1.begin(), v1.end());
    std::random_shuffle(v2.begin(), v2.end());
    while (!ft::lexicographical_compare(v1.begin(), v1.end(), v2.begin(), v2.end(), le)) {
      for (std::vector<int>::iterator c = v1.begin(); c != v1.end(); ++c)
        std::cout << *c << ' ';
      std::cout << " > ";
      for (std::vector<int>::iterator c = v2.begin(); c != v2.end(); ++c)
        std::cout << *c << ' ';
      std::cout << '\n';

      std::random_shuffle(v1.begin(), v1.end());
      std::random_shuffle(v2.begin(), v2.end());
    }
    for (std::vector<int>::iterator c = v1.begin(); c != v1.end(); ++c)
      std::cout << *c << ' ';
    std::cout << "<= ";
    for (std::vector<int>::iterator c = v2.begin(); c != v2.end(); ++c)
      std::cout << *c << ' ';
    std::cout << '\n';
  }
}
