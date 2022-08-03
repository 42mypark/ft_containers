#include <iomanip>
#include <iostream>
#include <vector>

#include "macro.hpp"
#include "vector.hpp"

template <typename Cont>
void print_cont(const std::string& tag, Cont c) {
  std::cout << tag << ": ";
  for (typename Cont::iterator it = c.begin(); it != c.end(); ++it) {
    std::cout << *it << ' ';
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
    ft::vector<int>  ft_v(3, -3);
    std::vector<int> std_v(3, -3);

    LABEL("std", "ft");
    ROW("empty", std_v.empty(), ft_v.empty());
    ROW("size", std_v.size(), ft_v.size());
    ROW("capacity", std_v.capacity(), ft_v.capacity());
    print_cont("std", std_v);
    print_cont("ft ", ft_v);
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
    print_cont("std", std_v);
    print_cont("ft ", ft_v);
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
    print_cont("std", std_v);
    print_cont("ft ", ft_v);
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
    print_cont("std", std_v);
    print_cont("ft ", ft_v);
    leakcheck();
  }

  {
    SUBTITLE("vector.assign(count, value)");
    ft::vector<int>  ft_v;
    std::vector<int> std_v;

    ft_v.assign(3, -3);
    std_v.assign(3, -3);

    LABEL("std", "ft");
    ROW("empty", std_v.empty(), ft_v.empty());
    ROW("size", std_v.size(), ft_v.size());
    ROW("capacity", std_v.capacity(), ft_v.capacity());
    print_cont("std", std_v);
    print_cont("ft ", ft_v);
  }

  {
    SUBTITLE("vector.at()");

    ft::vector<int>  ft_v;
    std::vector<int> std_v;

    ft_v.assign(3, -3);
    std_v.assign(3, -3);

    LABEL("std", "ft");
    ROW("at(0)", std_v.at(0), ft_v.at(0));
    ROW("at(1)", std_v.at(1), ft_v.at(1));
    ROW("at(2)", std_v.at(2), ft_v.at(2));
    TRYROW("at(3)", std_v.at(3), ft_v.at(3));
    TRYROW("at(-1)", std_v.at(-1), ft_v.at(-1));
    print_cont("std", std_v);
    print_cont("ft ", ft_v);
  }

  {
    SUBTITLE("vector[]");

    ft::vector<int>  ft_v;
    std::vector<int> std_v;

    ft_v.assign(3, -3);
    std_v.assign(3, -3);
    LABEL("std", "ft");
    ROW("[0]", std_v[0], ft_v[0]);
    ROW("[1]", std_v[1], ft_v[1]);
    ROW("[2]", std_v[2], ft_v[2]);
    // ROW("[3]", std_v[3], ft_v[3]);
    // ROW("[-10]", std_v[-10], ft_v[-10]);
    // ROW("[-1]", std_v[-1], ft_v[-1]);
    // ROW("[-2]", std_v[-2], ft_v[-2]);
    print_cont("std", std_v);
    print_cont("ft ", ft_v);
  }
  {
    SUBTITLE("vector.front & back & data");

    ft::vector<int>  ft_v;
    std::vector<int> std_v;

    std_v.push_back(-1);
    std_v.push_back(-2);
    std_v.push_back(-3);
    ft_v.push_back(-1);
    ft_v.push_back(-2);
    ft_v.push_back(-3);

    LABEL("std", "ft");
    ROW("front", std_v.front(), ft_v.front());
    ROW("back", std_v.back(), ft_v.back());
    ROW("*data", *std_v.data(), *ft_v.data());
    print_cont("std", std_v);
    print_cont("ft ", ft_v);
  }

  {
    SUBTITLE("iterator");

    ft::vector<int>  ft_v;
    std::vector<int> std_v;

    std_v.push_back(-1);
    std_v.push_back(-2);
    std_v.push_back(-3);
    std_v.push_back(4);
    std_v.push_back(5);

    ft_v.push_back(-1);
    ft_v.push_back(-2);
    ft_v.push_back(-3);
    ft_v.push_back(4);
    ft_v.push_back(5);

    print_cont("std", std_v);
    print_cont("ft ", ft_v);

    ft_v.begin()++;
    ft_v.rbegin()++;

    SUBTITLE("reverse_iterator");

    *(std_v.rbegin() + 1) = -99;
    *(ft_v.rbegin() + 1) = -99;

    std::cout << "std: ";
    for (std::vector<int>::reverse_iterator ri = std_v.rbegin(); ri != std_v.rend(); ++ri) {
      std::cout << *ri << ' ';
    }
    std::cout << std::endl;

    std::cout << "ft : ";
    for (ft::vector<int>::reverse_iterator ri = ft_v.rbegin(); ri != ft_v.rend(); ++ri) {
      std::cout << *ri << ' ';
    }
    std::cout << std::endl;
  }
  {
    SUBTITLE("vector.reserve()");
    ft::vector<int>  ft_v;
    std::vector<int> std_v;

    ft_v.assign(3, -3);
    std_v.assign(3, -3);

    LABEL("std", "ft");
    ROW("capacity", std_v.capacity(), ft_v.capacity());
    ROW("size", std_v.size(), ft_v.size());

    ft_v.reserve(5);
    std_v.reserve(5);
    ROW("capacity", std_v.capacity(), ft_v.capacity());
    ROW("size", std_v.size(), ft_v.size());

    print_cont("std", std_v);
    print_cont("ft ", ft_v);

    SUBTITLE("vector.max_size()");

    LABEL("std", "ft");
    ROW("max_size", std_v.max_size(), ft_v.max_size());
  }

  {
    SUBTITLE("vector.clear()");
    ft::vector<int>  ft_v;
    std::vector<int> std_v;

    ft_v.assign(3, -3);
    std_v.assign(3, -3);

    LABEL("std", "ft");
    ROW("empty", std_v.empty(), ft_v.empty());
    ROW("capacity", std_v.capacity(), ft_v.capacity());
    ROW("size", std_v.size(), ft_v.size());

    ft_v.clear();
    std_v.clear();

    std::cout << '\n';

    ROW("empty", std_v.empty(), ft_v.empty());
    ROW("capacity", std_v.capacity(), ft_v.capacity());
    ROW("size", std_v.size(), ft_v.size());
  }

  {
    SUBTITLE("vector.insert(pos, value)");
    ft::vector<int>  ft_v;
    std::vector<int> std_v;

    LABEL("std", "ft");

    ft_v.insert(ft_v.end(), 2);
    std_v.insert(std_v.end(), 2);

    ROW("capacity", std_v.capacity(), ft_v.capacity());
    ROW("size", std_v.size(), ft_v.size());

    print_cont("std", std_v);
    print_cont("ft ", ft_v);

    ft_v.insert(ft_v.end(), 3);
    std_v.insert(std_v.end(), 3);

    ROW("capacity", std_v.capacity(), ft_v.capacity());
    ROW("size", std_v.size(), ft_v.size());

    print_cont("std", std_v);
    print_cont("ft ", ft_v);

    ft_v.insert(ft_v.begin(), 1);
    std_v.insert(std_v.begin(), 1);

    ROW("capacity", std_v.capacity(), ft_v.capacity());
    ROW("size", std_v.size(), ft_v.size());

    print_cont("std", std_v);
    print_cont("ft ", ft_v);

    ft_v.insert(ft_v.begin() + 1, -1);
    std_v.insert(std_v.begin() + 1, -1);

    ROW("capacity", std_v.capacity(), ft_v.capacity());
    ROW("size", std_v.size(), ft_v.size());

    print_cont("std", std_v);
    print_cont("ft ", ft_v);
  }
  {
    SUBTITLE("vector.insert(pos, count, value)");
    ft::vector<int>  ft_v;
    std::vector<int> std_v;

    LABEL("std", "ft");
    ft_v.insert(ft_v.end(), 3, 1);
    std_v.insert(std_v.end(), 3, 1);

    ROW("capacity", std_v.capacity(), ft_v.capacity());
    ROW("size", std_v.size(), ft_v.size());

    print_cont("std", std_v);
    print_cont("ft ", ft_v);

    ft_v.insert(ft_v.begin() + 1, 3, 2);
    std_v.insert(std_v.begin() + 1, 3, 2);

    ROW("capacity", std_v.capacity(), ft_v.capacity());
    ROW("size", std_v.size(), ft_v.size());

    print_cont("std", std_v);
    print_cont("ft ", ft_v);

    ft_v.insert(ft_v.begin(), 3, 3);
    std_v.insert(std_v.begin(), 3, 3);

    ROW("capacity", std_v.capacity(), ft_v.capacity());
    ROW("size", std_v.size(), ft_v.size());

    print_cont("std", std_v);
    print_cont("ft ", ft_v);
  }

  {
    SUBTITLE("vector.insert(pos, iter)");
    ft::vector<int>  ft_v;
    std::vector<int> std_v;

    std::vector<int> std_1;
    std::vector<int> std_2;
    std::vector<int> std_3;

    std_1.assign(3, 1);
    std_2.assign(3, 2);
    std_3.assign(3, 3);

    LABEL("std", "ft");

    ft_v.insert(ft_v.end(), std_1.begin(), std_1.end());
    std_v.insert(std_v.end(), std_1.begin(), std_1.end());

    ft_v.insert(ft_v.end(), std_1.begin(), std_1.end());
    std_v.insert(std_v.end(), std_1.begin(), std_1.end());

    ROW("capacity", std_v.capacity(), ft_v.capacity());
    ROW("size", std_v.size(), ft_v.size());

    print_cont("std", std_v);
    print_cont("ft ", ft_v);

    ft_v.insert(ft_v.begin() + 1, std_2.begin(), std_2.end());
    std_v.insert(std_v.begin() + 1, std_2.begin(), std_2.end());

    ROW("capacity", std_v.capacity(), ft_v.capacity());
    ROW("size", std_v.size(), ft_v.size());

    print_cont("std", std_v);
    print_cont("ft ", ft_v);

    ft_v.insert(ft_v.begin(), std_3.begin(), std_3.end());
    std_v.insert(std_v.begin(), std_3.begin(), std_3.end());

    ROW("capacity", std_v.capacity(), ft_v.capacity());
    ROW("size", std_v.size(), ft_v.size());

    print_cont("std", std_v);
    print_cont("ft ", ft_v);

    // std_v.insert(std_v.end(), std_1.end(), std_1.begin());
    // ft_v.insert(ft_v.end(), std_1.end(), std_1.begin());

    // ROW("capacity", std_v.capacity(), ft_v.capacity());
    // ROW("size", std_v.size(), ft_v.size());

    // print_cont("std", std_v);
    // print_cont("ft ", ft_v);
  }

  {
    SUBTITLE("vector.erase(pos)");

    std::vector<int> std_v;
    ft::vector<int>  ft_v;
    std_v.push_back(1);
    std_v.push_back(2);
    std_v.push_back(3);
    ft_v.push_back(1);
    ft_v.push_back(2);
    ft_v.push_back(3);

    LABEL("std", "ft");
    ROW("capacity", std_v.capacity(), ft_v.capacity());
    ROW("size", std_v.size(), ft_v.size());

    print_cont("std", std_v);
    print_cont("ft ", ft_v);

    std_v.erase(std_v.begin() + 1);
    ft_v.erase(ft_v.begin() + 1);
    ROW("capacity", std_v.capacity(), ft_v.capacity());
    ROW("size", std_v.size(), ft_v.size());

    print_cont("std", std_v);
    print_cont("ft ", ft_v);

    std_v.erase(std_v.end() - 1);
    ft_v.erase(ft_v.end() - 1);
    ROW("capacity", std_v.capacity(), ft_v.capacity());
    ROW("size", std_v.size(), ft_v.size());

    print_cont("std", std_v);
    print_cont("ft ", ft_v);

    std_v.erase(std_v.begin());
    ft_v.erase(ft_v.begin());
    ROW("capacity", std_v.capacity(), ft_v.capacity());
    ROW("size", std_v.size(), ft_v.size());

    print_cont("std", std_v);
    print_cont("ft ", ft_v);

    /* Error Both
     * ft_v.erase(ft_v.begin());
     * std_v.erase(std_v.begin());
     * ROW("capacity", std_v.capacity(), ft_v.capacity());
     * ROW("size", std_v.size(), ft_v.size());
     * print_cont("std", std_v);
     * print_cont("ft ", ft_v);
     */
  }

  {
    SUBTITLE("vector.erase(iter)");
    ft::vector<int>  ft_v;
    std::vector<int> std_v;

    std::vector<int> std_1;
    std::vector<int> std_2;
    std::vector<int> std_3;

    std_1.assign(3, 1);
    std_2.assign(3, 2);
    std_3.assign(3, 3);

    LABEL("std", "ft");

    ft_v.insert(ft_v.end(), std_1.begin(), std_1.end());
    std_v.insert(std_v.end(), std_1.begin(), std_1.end());
    ft_v.insert(ft_v.end(), std_1.begin(), std_1.end());
    std_v.insert(std_v.end(), std_1.begin(), std_1.end());
    ft_v.insert(ft_v.begin(), std_2.begin(), std_2.end());
    std_v.insert(std_v.begin(), std_2.begin(), std_2.end());
    ft_v.insert(ft_v.begin(), std_3.begin(), std_3.end());
    std_v.insert(std_v.begin(), std_3.begin(), std_3.end());

    ROW("capacity", std_v.capacity(), ft_v.capacity());
    ROW("size", std_v.size(), ft_v.size());

    print_cont("std", std_v);
    print_cont("ft ", ft_v);

    ft_v.erase(ft_v.begin(), ft_v.begin() + 3);
    std_v.erase(std_v.begin(), std_v.begin() + 3);

    ROW("capacity", std_v.capacity(), ft_v.capacity());
    ROW("size", std_v.size(), ft_v.size());

    print_cont("std", std_v);
    print_cont("ft ", ft_v);

    ft_v.erase(ft_v.begin() + 3, ft_v.begin() + 6);
    std_v.erase(std_v.begin() + 3, std_v.begin() + 6);

    ROW("capacity", std_v.capacity(), ft_v.capacity());
    ROW("size", std_v.size(), ft_v.size());

    print_cont("std", std_v);
    print_cont("ft ", ft_v);

    ft_v.erase(ft_v.end() - 3, ft_v.end());
    std_v.erase(std_v.end() - 3, std_v.end());

    ROW("capacity", std_v.capacity(), ft_v.capacity());
    ROW("size", std_v.size(), ft_v.size());

    print_cont("std", std_v);
    print_cont("ft ", ft_v);

    ft_v.erase(ft_v.end() - 3, ft_v.end());
    std_v.erase(std_v.end() - 3, std_v.end());

    ROW("capacity", std_v.capacity(), ft_v.capacity());
    ROW("size", std_v.size(), ft_v.size());

    print_cont("std", std_v);
    print_cont("ft ", ft_v);
  }

  {
    SUBTITLE("vector.pop_back()");
    std::vector<int> std_v;
    ft::vector<int>  ft_v;

    std_v.assign(2, 2);
    ft_v.assign((size_t)2, 2);

    LABEL("std", "ft");
    ROW("capacity", std_v.capacity(), ft_v.capacity());
    ROW("size", std_v.size(), ft_v.size());

    print_cont("std", std_v);
    print_cont("ft ", ft_v);

    std_v.pop_back();
    ft_v.pop_back();

    ROW("capacity", std_v.capacity(), ft_v.capacity());
    ROW("size", std_v.size(), ft_v.size());

    print_cont("std", std_v);
    print_cont("ft ", ft_v);

    std_v.pop_back();
    ft_v.pop_back();

    ROW("capacity", std_v.capacity(), ft_v.capacity());
    ROW("size", std_v.size(), ft_v.size());

    print_cont("std", std_v);
    print_cont("ft ", ft_v);

    /* Error Both
// std_v.pop_back();
// ft_v.pop_back();

// ROW("capacity", std_v.capacity(), ft_v.capacity());
// ROW("size", std_v.size(), ft_v.size());

// print_cont("std", std_v);
// print_cont("ft ", ft_v);
     */
  }

  {
    SUBTITLE("vector.resize(count)");

    std::vector<int> std_v;
    ft::vector<int>  ft_v;

    std_v.push_back(1);
    std_v.push_back(2);
    std_v.push_back(3);
    ft_v.push_back(1);
    ft_v.push_back(2);
    ft_v.push_back(3);

    LABEL("std", "ft");
    ROW("capacity", std_v.capacity(), ft_v.capacity());
    ROW("size", std_v.size(), ft_v.size());

    print_cont("std", std_v);
    print_cont("ft ", ft_v);

    std_v.resize(5);
    ft_v.resize(5);

    ROW("capacity", std_v.capacity(), ft_v.capacity());
    ROW("size", std_v.size(), ft_v.size());

    print_cont("std", std_v);
    print_cont("ft ", ft_v);

    std_v.resize(2);
    ft_v.resize(2);

    ROW("capacity", std_v.capacity(), ft_v.capacity());
    ROW("size", std_v.size(), ft_v.size());

    print_cont("std", std_v);
    print_cont("ft ", ft_v);

    std_v.resize(6, 4);
    ft_v.resize(6, 4);

    ROW("capacity", std_v.capacity(), ft_v.capacity());
    ROW("size", std_v.size(), ft_v.size());

    print_cont("std", std_v);
    print_cont("ft ", ft_v);
  }

  {
    SUBTITLE("vector.swap(other)");

    std::vector<int> std_v;
    ft::vector<int>  ft_v;

    std::vector<int> std_v2;
    ft::vector<int>  ft_v2;
    std_v.push_back(1);
    std_v.push_back(1);
    std_v.push_back(1);
    ft_v.push_back(1);
    ft_v.push_back(1);
    ft_v.push_back(1);
    std_v2.assign(5, 2);
    ft_v2.assign((size_t)5, 2);

    print_cont("std ", std_v);
    print_cont("std2", std_v2);

    print_cont("ft  ", ft_v);
    print_cont("ft2 ", ft_v2);

    std::cout << '\n';

    ft_v.swap(ft_v2);
    std_v.swap(std_v2);

    print_cont("std ", std_v);
    print_cont("std2", std_v2);

    print_cont("ft  ", ft_v);
    print_cont("ft2 ", ft_v2);

    std::cout << '\n';

    ft_v.swap(ft_v2);
    std_v.swap(std_v2);

    print_cont("std ", std_v);
    print_cont("std2", std_v2);

    print_cont("ft  ", ft_v);
    print_cont("ft2 ", ft_v2);
  }

  {
    SUBTITLE("ft::swap");
    std::vector<int> std_v;
    ft::vector<int>  ft_v;

    std::vector<int> std_v2;
    ft::vector<int>  ft_v2;
    std_v.push_back(1);
    std_v.push_back(1);
    std_v.push_back(1);
    ft_v.push_back(1);
    ft_v.push_back(1);
    ft_v.push_back(1);
    std_v2.assign(5, 2);
    ft_v2.assign(5, 2);

    print_cont("std ", std_v);
    print_cont("std2", std_v2);

    print_cont("ft  ", ft_v);
    print_cont("ft2 ", ft_v2);

    std::cout << '\n';

    ft::swap(ft_v, ft_v2);
    std::swap(std_v, std_v2);

    print_cont("std ", std_v);
    print_cont("std2", std_v2);

    print_cont("ft  ", ft_v);
    print_cont("ft2 ", ft_v2);

    std::cout << '\n';

    ft::swap(ft_v, ft_v2);
    std::swap(std_v, std_v2);

    print_cont("std ", std_v);
    print_cont("std2", std_v2);

    print_cont("ft  ", ft_v);
    print_cont("ft2 ", ft_v2);
  }

  {
    SUBTITLE("operator==(eq)");

    std::vector<int> std_v;
    ft::vector<int>  ft_v;

    std_v.push_back(1);
    std_v.push_back(2);
    std_v.push_back(3);
    ft_v.push_back(1);
    ft_v.push_back(2);
    ft_v.push_back(3);

    std::vector<int> std_v2(std_v);
    ft::vector<int>  ft_v2(ft_v);

    LABEL("std", "ft");
    ROW("equal", (std_v == std_v2), (ft_v == ft_v2));
    std_v.pop_back();
    ft_v.pop_back();
    ROW("equal", (std_v == std_v2), (ft_v == ft_v2));
  }
  {
    SUBTITLE("operator!=(nq)");

    std::vector<int> std_v;
    ft::vector<int>  ft_v;

    std_v.push_back(1);
    std_v.push_back(2);
    std_v.push_back(3);
    ft_v.push_back(1);
    ft_v.push_back(2);
    ft_v.push_back(3);

    std::vector<int> std_v2(std_v);
    ft::vector<int>  ft_v2(ft_v);

    LABEL("std", "ft");
    ROW("not equal", (std_v != std_v2), (ft_v != ft_v2));
    std_v.pop_back();
    ft_v.pop_back();
    ROW("not equal", (std_v != std_v2), (ft_v != ft_v2));
  }
  {
    SUBTITLE("operator<(l)");
    std::vector<int> std_v;
    ft::vector<int>  ft_v;
    std::vector<int> std_v2;
    ft::vector<int>  ft_v2;

    LABEL("std", "ft");
    ROW("less", (std_v < std_v2), (ft_v < ft_v2));

    ft_v2.push_back(1);
    std_v2.push_back(1);

    ROW("less", (std_v < std_v2), (ft_v < ft_v2));

    ft_v.push_back(2);
    std_v.push_back(2);

    ROW("less", (std_v < std_v2), (ft_v < ft_v2));

    ft_v2.push_back(3);
    std_v2.push_back(3);

    ROW("less", (std_v < std_v2), (ft_v < ft_v2));
  }
  {
    SUBTITLE("operator<=(le)");
    std::vector<int> std_v;
    ft::vector<int>  ft_v;
    std::vector<int> std_v2;
    ft::vector<int>  ft_v2;

    LABEL("std", "ft");
    ROW("less equal", (std_v <= std_v2), (ft_v <= ft_v2));

    ft_v2.push_back(1);
    std_v2.push_back(1);

    ROW("less equal", (std_v <= std_v2), (ft_v <= ft_v2));

    ft_v.push_back(2);
    std_v.push_back(2);

    ROW("less equal", (std_v <= std_v2), (ft_v <= ft_v2));

    ft_v2.push_back(3);
    std_v2.push_back(3);

    ROW("less equal", (std_v <= std_v2), (ft_v <= ft_v2));
  }
  {
    SUBTITLE("operator>(g)");
    std::vector<int> std_v;
    ft::vector<int>  ft_v;
    std::vector<int> std_v2;
    ft::vector<int>  ft_v2;

    LABEL("std", "ft");
    ROW("grater", (std_v > std_v2), (ft_v > ft_v2));

    ft_v2.push_back(1);
    std_v2.push_back(1);

    ROW("grater", (std_v > std_v2), (ft_v > ft_v2));

    ft_v.push_back(2);
    std_v.push_back(2);

    ROW("grater", (std_v > std_v2), (ft_v > ft_v2));

    ft_v2.push_back(3);
    std_v2.push_back(3);

    ROW("grater", (std_v > std_v2), (ft_v > ft_v2));
  }
  {
    SUBTITLE("operator>=(ge)");
    std::vector<int> std_v;
    ft::vector<int>  ft_v;
    std::vector<int> std_v2;
    ft::vector<int>  ft_v2;

    LABEL("std", "ft");
    ROW("grater equal", (std_v >= std_v2), (ft_v >= ft_v2));

    ft_v2.push_back(1);
    std_v2.push_back(1);

    ROW("grater equal", (std_v >= std_v2), (ft_v >= ft_v2));

    ft_v.push_back(2);
    std_v.push_back(2);

    ROW("grater equal", (std_v >= std_v2), (ft_v >= ft_v2));

    ft_v2.push_back(3);
    std_v2.push_back(3);

    ROW("grater equal", (std_v >= std_v2), (ft_v >= ft_v2));
  }
}