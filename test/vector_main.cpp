#include <iomanip>
#include <iostream>
#include <vector>

#include "macro.hpp"
#include "vector.hpp"

template <typename InputIt>
void print_cont(const std::string& tag, InputIt begin, InputIt end) {
  std::cout << tag << ": ";
  for (; begin != end; ++begin) {
    std::cout << *begin << ' ';
  }
  std::cout << std::endl;
}

void leakcheck() {
#ifdef __APPLE__
  system("leaks vector.test | grep Process");
#endif
}

int main() {
  TITLE("vector");
  {
    SUBTITLE("CONSTRUCTOR-1");
    ft::vector<int>  ft_v;
    std::vector<int> std_v;

    LABEL("std", "ft");
    ROW("empty", std_v.empty(), ft_v.empty());
    ROW("size", std_v.size(), ft_v.size());
    ROW("capacity", std_v.capacity(), ft_v.capacity());
  }

  {
    SUBTITLE("CONSTRUCTOR-3");
    ft::vector<int>  ft_v((std::size_t)3, -3);  // ?
    std::vector<int> std_v(3, -3);

    LABEL("std", "ft");
    ROW("empty", std_v.empty(), ft_v.empty());
    ROW("size", std_v.size(), ft_v.size());
    ROW("capacity", std_v.capacity(), ft_v.capacity());
    print_cont("std", std_v.begin(), std_v.end());
    print_cont("ft ", ft_v.begin(), ft_v.end());
  }

  {
    SUBTITLE("CONSTRUCTOR-5");
    std::vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);
    v.push_back(5);
    ft::vector<int>  ft_v(v.begin(), v.end());
    std::vector<int> std_v(v.begin(), v.end());

    LABEL("std", "ft");
    ROW("empty", std_v.empty(), ft_v.empty());
    ROW("size", std_v.size(), ft_v.size());
    ROW("capacity", std_v.capacity(), ft_v.capacity());
    print_cont("std", std_v.begin(), std_v.end());
    print_cont("ft ", ft_v.begin(), ft_v.end());
  }

  {
    SUBTITLE("CONSTRUCTOR-6");
    std::vector<int> v;
    ft::vector<int>  fv;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    fv.push_back(1);
    fv.push_back(2);
    fv.push_back(3);
    ft::vector<int>  ft_v(fv);
    std::vector<int> std_v(v);

    LABEL("std", "ft");
    ROW("empty", std_v.empty(), ft_v.empty());
    ROW("size", std_v.size(), ft_v.size());
    ROW("capacity", std_v.capacity(), ft_v.capacity());
    print_cont("std", std_v.begin(), std_v.end());
    print_cont("ft ", ft_v.begin(), ft_v.end());
  }

  {
    SUBTITLE("cpa operator & vector.assign(iter)");
    std::vector<int> v;
    ft::vector<int>  fv;
    v.push_back(1);
    v.push_back(-2);
    v.push_back(3);
    fv.push_back(1);
    fv.push_back(-2);
    fv.push_back(3);
    ft::vector<int>  ft_v;
    std::vector<int> std_v;

    ft_v = fv;
    std_v = v;

    LABEL("std", "ft");
    ROW("empty", std_v.empty(), ft_v.empty());
    ROW("size", std_v.size(), ft_v.size());
    ROW("capacity", std_v.capacity(), ft_v.capacity());
    print_cont("std", std_v.begin(), std_v.end());
    print_cont("ft ", ft_v.begin(), ft_v.end());
    leakcheck();
  }

  {
    SUBTITLE("vector.assign(count, value)");
    ft::vector<int>  ft_v;
    std::vector<int> std_v;

    ft_v.assign((std::size_t)3, -3);  // ?
    std_v.assign(3, -3);

    LABEL("std", "ft");
    ROW("empty", std_v.empty(), ft_v.empty());
    ROW("size", std_v.size(), ft_v.size());
    ROW("capacity", std_v.capacity(), ft_v.capacity());
    print_cont("std", std_v.begin(), std_v.end());
    print_cont("ft ", ft_v.begin(), ft_v.end());
  }

  // {
  //   SUBTITLE("vector.at()");
  //   ft::vector<int> v;
  //   v.assign((size_t)3, 1);

  //   try {
  //     std::cout << v.at(0) << std::endl;
  //     std::cout << v.at(1) << std::endl;
  //     std::cout << v.at(2) << std::endl;
  //     std::cout << v.at(3) << std::endl;
  //   } catch (std::exception& e) {
  //     std::cout << e.what() << std::endl;
  //   }
  // }
}