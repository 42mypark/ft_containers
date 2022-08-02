#include <deque>
#include <iostream>
#include <string>
#include <type_traits>
#if 1  // CREATE A REAL STL EXAMPLE
#include <map>
#include <stack>
#include <vector>
namespace ft = std;
#else
#include <map.hpp>
#include <stack.hpp>
#include <vector.hpp>
#endif

#include <stdlib.h>

#include "macro.hpp"
template <class _Tp, class _Up>
struct is_same : public ft::false_type {};
template <class _Tp>
struct is_same<_Tp, _Tp> : public ft::true_type {};

#define MAX_RAM 4294967296
#define BUFFER_SIZE 4096
struct Buffer {
  int  idx;
  char buff[BUFFER_SIZE];
};

#define COUNT (MAX_RAM / (int)sizeof(Buffer))

template <typename Cont>
void print_vec(const std::string& tag, Cont c) {
  std::cout << tag << ": ";
  for (typename Cont::iterator it = c.begin(); it != c.end(); ++it) {
    std::cout << *it << " ";
  }
  std::cout << std::endl;
}

template <typename Cont>
void print_map(const std::string& tag, Cont c) {
  std::cout << tag << ": ";
  for (typename Cont::iterator it = c.begin(); it != c.end(); ++it) {
    std::cout << "(" << it->first << ", " << it->second << ") ";
  }
  std::cout << std::endl;
}

void leakcheck() {
#ifdef __APPLE__
  system("leaks vector.test | grep Process");
#endif
}

template <typename T>
class MutantStack : public ft::stack<T> {
 public:
  MutantStack() {}
  MutantStack(const MutantStack<T>& src) { *this = src; }
  MutantStack<T>& operator=(const MutantStack<T>& rhs) {
    this->c = rhs.c;
    return *this;
  }
  ~MutantStack() {}

  typedef typename ft::stack<T>::container_type::iterator iterator;

  iterator begin() { return this->c.begin(); }
  iterator end() { return this->c.end(); }
};

void subject_test() {
  ft::vector<std::string>                vector_str;
  ft::vector<int>                        vector_int;
  ft::stack<int>                         stack_int;
  ft::vector<Buffer>                     vector_buffer;
  ft::stack<Buffer, std::deque<Buffer> > stack_deq_buffer;
  ft::map<int, int>                      map_int;

  for (int i = 0; i < COUNT; i++) {
    vector_buffer.push_back(Buffer());
  }

  for (int i = 0; i < COUNT; i++) {
    const int idx = rand() % COUNT;
    vector_buffer[idx].idx = 5;
  }
  ft::vector<Buffer>().swap(vector_buffer);

  try {
    for (int i = 0; i < COUNT; i++) {
      const int idx = rand() % COUNT;
      vector_buffer.at(idx);
      std::cerr << "Error: THIS VECTOR SHOULD BE EMPTY!!" << std::endl;
    }
  } catch (const std::exception& e) {
    // NORMAL ! :P
  }

  for (int i = 0; i < COUNT; ++i) {
    map_int.insert(ft::make_pair(rand(), rand()));
  }

  int sum = 0;
  for (int i = 0; i < 10000; i++) {
    int access = rand();
    sum += map_int[access];
  }
  std::cout << "should be constant with the same seed: " << sum << std::endl;

  { ft::map<int, int> copy = map_int; }
  MutantStack<char> iterable_stack;
  for (char letter = 'a'; letter <= 'z'; letter++)
    iterable_stack.push(letter);
  for (MutantStack<char>::iterator it = iterable_stack.begin(); it != iterable_stack.end(); it++) {
    std::cout << *it;
  }
  std::cout << std::endl;
}

void vector_functional_test() {
  TITLE("vector");
  {
    SUBTITLE("CONSTRUCTOR-1");
    ft::vector<int> ft_v;
    ft::vector<int> std_v;

    LABEL("std", "ft");
    ROW("empty", std_v.empty(), ft_v.empty());
    ROW("size", std_v.size(), ft_v.size());
    ROW("capacity", std_v.capacity(), ft_v.capacity());
  }

  {
    SUBTITLE("CONSTRUCTOR-3");
    ft::vector<int> ft_v(3, -3);
    ft::vector<int> std_v(3, -3);

    LABEL("std", "ft");
    ROW("empty", std_v.empty(), ft_v.empty());
    ROW("size", std_v.size(), ft_v.size());
    ROW("capacity", std_v.capacity(), ft_v.capacity());
    print_vec("std", std_v);
    print_vec("ft ", ft_v);
  }

  {
    SUBTITLE("CONSTRUCTOR-5");
    ft::vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);
    v.push_back(5);
    ft::vector<int> ft_v(v.begin(), v.end());
    ft::vector<int> std_v(v.begin(), v.end());

    LABEL("std", "ft");
    ROW("empty", std_v.empty(), ft_v.empty());
    ROW("size", std_v.size(), ft_v.size());
    ROW("capacity", std_v.capacity(), ft_v.capacity());
    print_vec("std", std_v);
    print_vec("ft ", ft_v);
  }

  {
    SUBTITLE("CONSTRUCTOR-6");
    ft::vector<int> v;
    ft::vector<int> fv;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    fv.push_back(1);
    fv.push_back(2);
    fv.push_back(3);
    ft::vector<int> ft_v(fv);
    ft::vector<int> std_v(v);

    LABEL("std", "ft");
    ROW("empty", std_v.empty(), ft_v.empty());
    ROW("size", std_v.size(), ft_v.size());
    ROW("capacity", std_v.capacity(), ft_v.capacity());
    print_vec("std", std_v);
    print_vec("ft ", ft_v);
  }

  {
    SUBTITLE("cpa operator & vector.assign(iter)");
    ft::vector<int> v;
    ft::vector<int> fv;
    v.push_back(1);
    v.push_back(-2);
    v.push_back(3);
    fv.push_back(1);
    fv.push_back(-2);
    fv.push_back(3);
    ft::vector<int> ft_v;
    ft::vector<int> std_v;

    ft_v = fv;
    std_v = v;

    LABEL("std", "ft");
    ROW("empty", std_v.empty(), ft_v.empty());
    ROW("size", std_v.size(), ft_v.size());
    ROW("capacity", std_v.capacity(), ft_v.capacity());
    print_vec("std", std_v);
    print_vec("ft ", ft_v);
    leakcheck();
  }

  {
    SUBTITLE("vector.assign(count, value)");
    ft::vector<int> ft_v;
    ft::vector<int> std_v;

    ft_v.assign(3, -3);
    std_v.assign(3, -3);

    LABEL("std", "ft");
    ROW("empty", std_v.empty(), ft_v.empty());
    ROW("size", std_v.size(), ft_v.size());
    ROW("capacity", std_v.capacity(), ft_v.capacity());
    print_vec("std", std_v);
    print_vec("ft ", ft_v);
  }

  {
    SUBTITLE("vector.at()");

    ft::vector<int> ft_v;
    ft::vector<int> std_v;

    ft_v.assign(3, -3);
    std_v.assign(3, -3);

    LABEL("std", "ft");
    ROW("at(0)", std_v.at(0), ft_v.at(0));
    ROW("at(1)", std_v.at(1), ft_v.at(1));
    ROW("at(2)", std_v.at(2), ft_v.at(2));
    TRYROW("at(3)", std_v.at(3), ft_v.at(3));
    TRYROW("at(-1)", std_v.at(-1), ft_v.at(-1));
    print_vec("std", std_v);
    print_vec("ft ", ft_v);
  }

  {
    SUBTITLE("vector[]");

    ft::vector<int> ft_v;
    ft::vector<int> std_v;

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
    print_vec("std", std_v);
    print_vec("ft ", ft_v);
  }
  {
    SUBTITLE("vector.front & back & data");

    ft::vector<int> ft_v;
    ft::vector<int> std_v;

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
    print_vec("std", std_v);
    print_vec("ft ", ft_v);
  }

  {
    SUBTITLE("iterator");

    ft::vector<int> ft_v;
    ft::vector<int> std_v;

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

    print_vec("std", std_v);
    print_vec("ft ", ft_v);

    SUBTITLE("reverse_iterator");

    *(++std_v.rbegin()) = -99;
    *(++ft_v.rbegin()) = -99;

    std::cout << "std: ";
    for (ft::vector<int>::reverse_iterator ri = std_v.rbegin(); ri != std_v.rend(); ++ri) {
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
    ft::vector<int> ft_v;
    ft::vector<int> std_v;

    ft_v.assign(3, -3);
    std_v.assign(3, -3);

    LABEL("std", "ft");
    ROW("capacity", std_v.capacity(), ft_v.capacity());
    ROW("size", std_v.size(), ft_v.size());

    ft_v.reserve(5);
    std_v.reserve(5);
    ROW("capacity", std_v.capacity(), ft_v.capacity());
    ROW("size", std_v.size(), ft_v.size());

    print_vec("std", std_v);
    print_vec("ft ", ft_v);

    SUBTITLE("vector.max_size()");

    LABEL("std", "ft");
    ROW("max_size", std_v.max_size(), ft_v.max_size());
  }

  {
    SUBTITLE("vector.clear()");
    ft::vector<int> ft_v;
    ft::vector<int> std_v;

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
    ft::vector<int> ft_v;
    ft::vector<int> std_v;

    LABEL("std", "ft");

    ft_v.insert(ft_v.end(), 2);
    std_v.insert(std_v.end(), 2);

    ROW("capacity", std_v.capacity(), ft_v.capacity());
    ROW("size", std_v.size(), ft_v.size());

    print_vec("std", std_v);
    print_vec("ft ", ft_v);

    ft_v.insert(ft_v.end(), 3);
    std_v.insert(std_v.end(), 3);

    ROW("capacity", std_v.capacity(), ft_v.capacity());
    ROW("size", std_v.size(), ft_v.size());

    print_vec("std", std_v);
    print_vec("ft ", ft_v);

    ft_v.insert(ft_v.begin(), 1);
    std_v.insert(std_v.begin(), 1);

    ROW("capacity", std_v.capacity(), ft_v.capacity());
    ROW("size", std_v.size(), ft_v.size());

    print_vec("std", std_v);
    print_vec("ft ", ft_v);

    ft_v.insert(ft_v.begin() + 1, -1);
    std_v.insert(std_v.begin() + 1, -1);

    ROW("capacity", std_v.capacity(), ft_v.capacity());
    ROW("size", std_v.size(), ft_v.size());

    print_vec("std", std_v);
    print_vec("ft ", ft_v);
  }
  {
    SUBTITLE("vector.insert(pos, count, value)");
    ft::vector<int> ft_v;
    ft::vector<int> std_v;

    LABEL("std", "ft");
    ft_v.insert(ft_v.end(), 3, 1);
    std_v.insert(std_v.end(), 3, 1);

    ROW("capacity", std_v.capacity(), ft_v.capacity());
    ROW("size", std_v.size(), ft_v.size());

    print_vec("std", std_v);
    print_vec("ft ", ft_v);

    ft_v.insert(ft_v.begin() + 1, 3, 2);
    std_v.insert(std_v.begin() + 1, 3, 2);

    ROW("capacity", std_v.capacity(), ft_v.capacity());
    ROW("size", std_v.size(), ft_v.size());

    print_vec("std", std_v);
    print_vec("ft ", ft_v);

    ft_v.insert(ft_v.begin(), 3, 3);
    std_v.insert(std_v.begin(), 3, 3);

    ROW("capacity", std_v.capacity(), ft_v.capacity());
    ROW("size", std_v.size(), ft_v.size());

    print_vec("std", std_v);
    print_vec("ft ", ft_v);
  }

  {
    SUBTITLE("vector.insert(pos, iter)");
    ft::vector<int> ft_v;
    ft::vector<int> std_v;

    ft::vector<int> std_1;
    ft::vector<int> std_2;
    ft::vector<int> std_3;

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

    print_vec("std", std_v);
    print_vec("ft ", ft_v);

    ft_v.insert(ft_v.begin() + 1, std_2.begin(), std_2.end());
    std_v.insert(std_v.begin() + 1, std_2.begin(), std_2.end());

    ROW("capacity", std_v.capacity(), ft_v.capacity());
    ROW("size", std_v.size(), ft_v.size());

    print_vec("std", std_v);
    print_vec("ft ", ft_v);

    ft_v.insert(ft_v.begin(), std_3.begin(), std_3.end());
    std_v.insert(std_v.begin(), std_3.begin(), std_3.end());

    ROW("capacity", std_v.capacity(), ft_v.capacity());
    ROW("size", std_v.size(), ft_v.size());

    print_vec("std", std_v);
    print_vec("ft ", ft_v);

    // std_v.insert(std_v.end(), std_1.end(), std_1.begin());
    // ft_v.insert(ft_v.end(), std_1.end(), std_1.begin());

    // ROW("capacity", std_v.capacity(), ft_v.capacity());
    // ROW("size", std_v.size(), ft_v.size());

    // print_vec("std", std_v);
    // print_vec("ft ", ft_v);
  }

  {
    SUBTITLE("vector.erase(pos)");

    ft::vector<int> std_v;
    ft::vector<int> ft_v;
    std_v.push_back(1);
    std_v.push_back(2);
    std_v.push_back(3);
    ft_v.push_back(1);
    ft_v.push_back(2);
    ft_v.push_back(3);

    LABEL("std", "ft");
    ROW("capacity", std_v.capacity(), ft_v.capacity());
    ROW("size", std_v.size(), ft_v.size());

    print_vec("std", std_v);
    print_vec("ft ", ft_v);

    std_v.erase(std_v.begin() + 1);
    ft_v.erase(ft_v.begin() + 1);
    ROW("capacity", std_v.capacity(), ft_v.capacity());
    ROW("size", std_v.size(), ft_v.size());

    print_vec("std", std_v);
    print_vec("ft ", ft_v);

    std_v.erase(std_v.end() - 1);
    ft_v.erase(ft_v.end() - 1);
    ROW("capacity", std_v.capacity(), ft_v.capacity());
    ROW("size", std_v.size(), ft_v.size());

    print_vec("std", std_v);
    print_vec("ft ", ft_v);

    std_v.erase(std_v.begin());
    ft_v.erase(ft_v.begin());
    ROW("capacity", std_v.capacity(), ft_v.capacity());
    ROW("size", std_v.size(), ft_v.size());

    print_vec("std", std_v);
    print_vec("ft ", ft_v);

    /* Error Both
     * ft_v.erase(ft_v.begin());
     * std_v.erase(std_v.begin());
     * ROW("capacity", std_v.capacity(), ft_v.capacity());
     * ROW("size", std_v.size(), ft_v.size());
     * print_vec("std", std_v);
     * print_vec("ft ", ft_v);
     */
  }

  {
    SUBTITLE("vector.erase(iter)");
    ft::vector<int> ft_v;
    ft::vector<int> std_v;

    ft::vector<int> std_1;
    ft::vector<int> std_2;
    ft::vector<int> std_3;

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

    print_vec("std", std_v);
    print_vec("ft ", ft_v);

    ft_v.erase(ft_v.begin(), ft_v.begin() + 3);
    std_v.erase(std_v.begin(), std_v.begin() + 3);

    ROW("capacity", std_v.capacity(), ft_v.capacity());
    ROW("size", std_v.size(), ft_v.size());

    print_vec("std", std_v);
    print_vec("ft ", ft_v);

    ft_v.erase(ft_v.begin() + 3, ft_v.begin() + 6);
    std_v.erase(std_v.begin() + 3, std_v.begin() + 6);

    ROW("capacity", std_v.capacity(), ft_v.capacity());
    ROW("size", std_v.size(), ft_v.size());

    print_vec("std", std_v);
    print_vec("ft ", ft_v);

    ft_v.erase(ft_v.end() - 3, ft_v.end());
    std_v.erase(std_v.end() - 3, std_v.end());

    ROW("capacity", std_v.capacity(), ft_v.capacity());
    ROW("size", std_v.size(), ft_v.size());

    print_vec("std", std_v);
    print_vec("ft ", ft_v);

    ft_v.erase(ft_v.end() - 3, ft_v.end());
    std_v.erase(std_v.end() - 3, std_v.end());

    ROW("capacity", std_v.capacity(), ft_v.capacity());
    ROW("size", std_v.size(), ft_v.size());

    print_vec("std", std_v);
    print_vec("ft ", ft_v);
  }

  {
    SUBTITLE("vector.pop_back()");
    ft::vector<int> std_v;
    ft::vector<int> ft_v;

    std_v.assign(2, 2);
    ft_v.assign((size_t)2, 2);

    LABEL("std", "ft");
    ROW("capacity", std_v.capacity(), ft_v.capacity());
    ROW("size", std_v.size(), ft_v.size());

    print_vec("std", std_v);
    print_vec("ft ", ft_v);

    std_v.pop_back();
    ft_v.pop_back();

    ROW("capacity", std_v.capacity(), ft_v.capacity());
    ROW("size", std_v.size(), ft_v.size());

    print_vec("std", std_v);
    print_vec("ft ", ft_v);

    std_v.pop_back();
    ft_v.pop_back();

    ROW("capacity", std_v.capacity(), ft_v.capacity());
    ROW("size", std_v.size(), ft_v.size());

    print_vec("std", std_v);
    print_vec("ft ", ft_v);

    /* Error Both
// std_v.pop_back();
// ft_v.pop_back();

// ROW("capacity", std_v.capacity(), ft_v.capacity());
// ROW("size", std_v.size(), ft_v.size());

// print_vec("std", std_v);
// print_vec("ft ", ft_v);
     */
  }

  {
    SUBTITLE("vector.resize(count)");

    ft::vector<int> std_v;
    ft::vector<int> ft_v;

    std_v.push_back(1);
    std_v.push_back(2);
    std_v.push_back(3);
    ft_v.push_back(1);
    ft_v.push_back(2);
    ft_v.push_back(3);

    LABEL("std", "ft");
    ROW("capacity", std_v.capacity(), ft_v.capacity());
    ROW("size", std_v.size(), ft_v.size());

    print_vec("std", std_v);
    print_vec("ft ", ft_v);

    std_v.resize(5);
    ft_v.resize(5);

    ROW("capacity", std_v.capacity(), ft_v.capacity());
    ROW("size", std_v.size(), ft_v.size());

    print_vec("std", std_v);
    print_vec("ft ", ft_v);

    std_v.resize(2);
    ft_v.resize(2);

    ROW("capacity", std_v.capacity(), ft_v.capacity());
    ROW("size", std_v.size(), ft_v.size());

    print_vec("std", std_v);
    print_vec("ft ", ft_v);

    std_v.resize(6, 4);
    ft_v.resize(6, 4);

    ROW("capacity", std_v.capacity(), ft_v.capacity());
    ROW("size", std_v.size(), ft_v.size());

    print_vec("std", std_v);
    print_vec("ft ", ft_v);
  }

  {
    SUBTITLE("vector.swap(other)");

    ft::vector<int> std_v;
    ft::vector<int> ft_v;

    ft::vector<int> std_v2;
    ft::vector<int> ft_v2;
    std_v.push_back(1);
    std_v.push_back(1);
    std_v.push_back(1);
    ft_v.push_back(1);
    ft_v.push_back(1);
    ft_v.push_back(1);
    std_v2.assign(5, 2);
    ft_v2.assign((size_t)5, 2);

    print_vec("std ", std_v);
    print_vec("std2", std_v2);

    print_vec("ft  ", ft_v);
    print_vec("ft2 ", ft_v2);

    std::cout << '\n';

    ft_v.swap(ft_v2);
    std_v.swap(std_v2);

    print_vec("std ", std_v);
    print_vec("std2", std_v2);

    print_vec("ft  ", ft_v);
    print_vec("ft2 ", ft_v2);

    std::cout << '\n';

    ft_v.swap(ft_v2);
    std_v.swap(std_v2);

    print_vec("std ", std_v);
    print_vec("std2", std_v2);

    print_vec("ft  ", ft_v);
    print_vec("ft2 ", ft_v2);
  }

  {
    SUBTITLE("ft::swap");
    ft::vector<int> std_v;
    ft::vector<int> ft_v;

    ft::vector<int> std_v2;
    ft::vector<int> ft_v2;
    std_v.push_back(1);
    std_v.push_back(1);
    std_v.push_back(1);
    ft_v.push_back(1);
    ft_v.push_back(1);
    ft_v.push_back(1);
    std_v2.assign(5, 2);
    ft_v2.assign(5, 2);

    print_vec("std ", std_v);
    print_vec("std2", std_v2);

    print_vec("ft  ", ft_v);
    print_vec("ft2 ", ft_v2);

    std::cout << '\n';

    ft::swap(ft_v, ft_v2);
    std::swap(std_v, std_v2);

    print_vec("std ", std_v);
    print_vec("std2", std_v2);

    print_vec("ft  ", ft_v);
    print_vec("ft2 ", ft_v2);

    std::cout << '\n';

    ft::swap(ft_v, ft_v2);
    std::swap(std_v, std_v2);

    print_vec("std ", std_v);
    print_vec("std2", std_v2);

    print_vec("ft  ", ft_v);
    print_vec("ft2 ", ft_v2);
  }

  {
    SUBTITLE("operator==(eq)");

    ft::vector<int> std_v;
    ft::vector<int> ft_v;

    std_v.push_back(1);
    std_v.push_back(2);
    std_v.push_back(3);
    ft_v.push_back(1);
    ft_v.push_back(2);
    ft_v.push_back(3);

    ft::vector<int> std_v2(std_v);
    ft::vector<int> ft_v2(ft_v);

    LABEL("std", "ft");
    ROW("equal", (std_v == std_v2), (ft_v == ft_v2));
    std_v.pop_back();
    ft_v.pop_back();
    ROW("equal", (std_v == std_v2), (ft_v == ft_v2));
  }
  {
    SUBTITLE("operator!=(nq)");

    ft::vector<int> std_v;
    ft::vector<int> ft_v;

    std_v.push_back(1);
    std_v.push_back(2);
    std_v.push_back(3);
    ft_v.push_back(1);
    ft_v.push_back(2);
    ft_v.push_back(3);

    ft::vector<int> std_v2(std_v);
    ft::vector<int> ft_v2(ft_v);

    LABEL("std", "ft");
    ROW("not equal", (std_v != std_v2), (ft_v != ft_v2));
    std_v.pop_back();
    ft_v.pop_back();
    ROW("not equal", (std_v != std_v2), (ft_v != ft_v2));
  }
  {
    SUBTITLE("operator<(l)");
    ft::vector<int> std_v;
    ft::vector<int> ft_v;
    ft::vector<int> std_v2;
    ft::vector<int> ft_v2;

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
    ft::vector<int> std_v;
    ft::vector<int> ft_v;
    ft::vector<int> std_v2;
    ft::vector<int> ft_v2;

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
    ft::vector<int> std_v;
    ft::vector<int> ft_v;
    ft::vector<int> std_v2;
    ft::vector<int> ft_v2;

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
    ft::vector<int> std_v;
    ft::vector<int> ft_v;
    ft::vector<int> std_v2;
    ft::vector<int> ft_v2;

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
void stack_functional_test() {
  TITLE("stack");
  SUBTITLE("interface");
  {
    ft::stack<int> fs;
    ft::stack<int> s;
    std::cout << "* initial state *" << '\n';
    ROW("size ", fs.size(), s.size());
    ROW("empty", fs.empty(), s.empty());
    fs.push(123);
    s.push(123);
    std::cout << "* after push '123' *" << '\n';
    ROW("top  ", fs.top(), s.top());
    ROW("size ", fs.size(), s.size());
    ROW("empty", fs.empty(), s.empty());
    fs.pop();
    s.pop();
    std::cout << "* after pop *" << '\n';
    ROW("size ", fs.size(), s.size());
    ROW("empty", fs.empty(), s.empty());
  }
  std::cout << std::endl;

  SUBTITLE("Compare Operator Test");
  {
    std::cout << "=equal=" << '\n';
    {
      ft::stack<int> fs1, fs2;
      ft::stack<int> s1, s2;
      LABEL("ft", "std");
      ROW("eq", (fs1 == fs2), (s1 == s2));
      s1.push(10);
      fs1.push(10);
      ROW("eq", (fs1 == fs2), (s1 == s2));
      s2.push(10);
      fs2.push(10);
      ROW("eq", (fs1 == fs2), (s1 == s2));
    }
    std::cout << std::endl;

    std::cout << "=not equal=" << '\n';
    {
      ft::stack<int> fs1, fs2;
      ft::stack<int> s1, s2;
      LABEL("ft", "std");
      ROW("nq", (fs1 != fs2), (s1 != s2));
      s1.push(10);
      fs1.push(10);
      ROW("nq", (fs1 != fs2), (s1 != s2));
      s2.push(10);
      fs2.push(10);
      ROW("nq", (fs1 != fs2), (s1 != s2));
    }
    std::cout << std::endl;

    std::cout << "=greater=" << '\n';
    {
      ft::stack<int> fs1, fs2;
      ft::stack<int> s1, s2;
      LABEL("ft", "std");
      ROW("g", (fs1 > fs2), (s1 > s2));
      s1.push(10);
      fs1.push(10);
      ROW("g", (fs1 > fs2), (s1 > s2));
      s2.push(10);
      fs2.push(10);
      ROW("g", (fs1 > fs2), (s1 > s2));
    }
    std::cout << std::endl;

    std::cout << "=greater equal=" << '\n';
    {
      ft::stack<int> fs1, fs2;
      ft::stack<int> s1, s2;
      LABEL("ft", "std");
      ROW("ge", (fs1 >= fs2), (s1 >= s2));
      s1.push(10);
      fs1.push(10);
      ROW("ge", (fs1 >= fs2), (s1 >= s2));
      s2.push(10);
      fs2.push(10);
      ROW("ge", (fs1 >= fs2), (s1 >= s2));
    }
    std::cout << std::endl;

    std::cout << "=less=" << '\n';
    {
      ft::stack<int> fs1, fs2;
      ft::stack<int> s1, s2;
      LABEL("ft", "std");
      ROW("l", (fs1 < fs2), (s1 < s2));
      s1.push(10);
      fs1.push(10);
      ROW("l", (fs1 < fs2), (s1 < s2));
      s2.push(10);
      fs2.push(10);
      ROW("l", (fs1 < fs2), (s1 < s2));
    }
    std::cout << std::endl;

    std::cout << "=less equal=" << '\n';
    {
      ft::stack<int> fs1, fs2;
      ft::stack<int> s1, s2;
      LABEL("ft", "std");
      ROW("le", (fs1 <= fs2), (s1 <= s2));
      s1.push(10);
      fs1.push(10);
      ROW("le", (fs1 <= fs2), (s1 <= s2));
      s2.push(10);
      fs2.push(10);
      ROW("le", (fs1 <= fs2), (s1 <= s2));
    }
    std::cout << std::endl;
  }
}
void map_functional_test() {
  TITLE("rbtree_iterator");
  {
    SUBTITLE("iterator");
    ft::map<int, int> ft_m;
    ft::map<int, int> std_m;
    ft_m.insert(ft::make_pair(1, -1));
    ft_m.insert(ft::make_pair(1, 2));

    std_m.insert(ft::make_pair(1, -1));
    std_m.insert(ft::make_pair(1, 2));

    ft_m.insert(ft::make_pair(2, 2));
    ft_m.insert(ft::make_pair(3, 3));
    ft_m.insert(ft::make_pair(4, 4));

    std_m.insert(ft::make_pair(2, 2));
    std_m.insert(ft::make_pair(3, 3));
    std_m.insert(ft::make_pair(4, 4));

    ft::map<int, int>::iterator it_std = std_m.begin();
    for (; it_std != std_m.end(); ++it_std) {
      std::cout << it_std->first << ", " << it_std->second << std::endl;
    }

    std::cout << '\n';

    ft::map<int, int>::iterator it = ft_m.begin();
    for (; it != ft_m.end(); ++it) {
      std::cout << it->first << ", " << it->second << std::endl;
    }

    std::cout << '\n';

    ft::map<int, int>::iterator it_std2 = std_m.end();
    it_std2--;
    for (; it_std2 != std_m.begin(); --it_std2) {
      std::cout << it_std2->first << ", " << it_std2->second << std::endl;
    }

    std::cout << '\n';

    ft::map<int, int>::iterator it2 = ft_m.end();
    it2--;
    for (; it2 != ft_m.begin(); --it2) {
      std::cout << it2->first << ", " << it2->second << std::endl;
    }

    SUBTITLE("reverse_iterator");

    ft::map<int, int>::reverse_iterator it_std_r = std_m.rbegin();
    for (; it_std_r != std_m.rend(); ++it_std_r) {
      std::cout << it_std_r->first << ", " << it_std_r->second << std::endl;
    }

    std::cout << '\n';

    ft::map<int, int>::reverse_iterator it_r = ft_m.rbegin();
    for (; it_r != ft_m.rend(); ++it_r) {
      std::cout << it_r->first << ", " << it_r->second << std::endl;
    }

    std::cout << '\n';
  }
  {
    SUBTITLE("const_iterator");
    ft::map<int, int> ft_m;
    ft::map<int, int> std_m;
    ft_m.insert(ft::make_pair(1, -1));
    ft_m.insert(ft::make_pair(1, 2));

    std_m.insert(ft::make_pair(1, -1));
    std_m.insert(ft::make_pair(1, 2));

    ft_m.insert(ft::make_pair(2, 2));
    ft_m.insert(ft::make_pair(3, 3));
    ft_m.insert(ft::make_pair(4, 4));

    std_m.insert(ft::make_pair(2, 2));
    std_m.insert(ft::make_pair(3, 3));
    std_m.insert(ft::make_pair(4, 4));

    ft::map<int, int>::const_iterator it_std = std_m.begin();
    for (; it_std != std_m.end(); ++it_std) {
      std::cout << it_std->first << ", " << it_std->second << std::endl;
    }

    std::cout << '\n';

    ft::map<int, int>::const_iterator it = ft_m.begin();
    for (; it != ft_m.end(); ++it) {
      std::cout << it->first << ", " << it->second << std::endl;
    }

    std::cout << '\n';

    ft::map<int, int>::const_iterator it_std2 = std_m.end();
    it_std2--;
    for (; it_std2 != std_m.begin(); --it_std2) {
      std::cout << it_std2->first << ", " << it_std2->second << std::endl;
    }

    std::cout << '\n';

    ft::map<int, int>::const_iterator it2 = ft_m.end();
    it2--;
    for (; it2 != ft_m.begin(); --it2) {
      std::cout << it2->first << ", " << it2->second << std::endl;
    }

    SUBTITLE("const_reverse_iterator");

    ft::map<int, int>::const_reverse_iterator it_std_r = std_m.rbegin();
    for (; it_std_r != std_m.rend(); ++it_std_r) {
      std::cout << it_std_r->first << ", " << it_std_r->second << std::endl;
    }

    std::cout << '\n';

    ft::map<int, int>::const_reverse_iterator it_r = ft_m.rbegin();
    for (; it_r != ft_m.rend(); ++it_r) {
      std::cout << it_r->first << ", " << it_r->second << std::endl;
    }

    std::cout << '\n';
  }

  TITLE("map");
  {
    SUBTITLE("CONSTRUCTOR 1");
    ft::map<int, char> ft_m;
    ft::map<int, char> std_m;

    LABEL("std", "ft");
    ROW("empty", std_m.empty(), ft_m.empty());
    ROW("size", std_m.size(), ft_m.size());
  }
  {
    SUBTITLE("CONSTRUCTOR 3");
    ft::map<int, int> fm;
    ft::map<int, int> sm;

    fm.insert(ft::map<int, int>::value_type(1, 1));
    fm.insert(ft::map<int, int>::value_type(2, 2));
    fm.insert(ft::map<int, int>::value_type(3, 3));
    fm.insert(ft::map<int, int>::value_type(4, 4));

    sm.insert(ft::map<int, int>::value_type(1, 1));
    sm.insert(ft::map<int, int>::value_type(2, 2));
    sm.insert(ft::map<int, int>::value_type(3, 3));
    sm.insert(ft::map<int, int>::value_type(4, 4));

    ft::map<int, int> ft_m(fm.begin(), fm.end());
    ft::map<int, int> std_m(sm.begin(), sm.end());

    LABEL("std", "ft");
    ROW("empty", std_m.empty(), ft_m.empty());
    ROW("size", std_m.size(), ft_m.size());

    print_map("std", std_m);
    print_map("ft ", ft_m);
  }
  {
    SUBTITLE("CONSTRUCTOR 4");
    ft::map<int, int> fm;
    ft::map<int, int> sm;

    fm.insert(ft::map<int, int>::value_type(1, 1));
    fm.insert(ft::map<int, int>::value_type(2, 2));
    fm.insert(ft::map<int, int>::value_type(3, 3));
    fm.insert(ft::map<int, int>::value_type(4, 4));

    sm.insert(ft::map<int, int>::value_type(1, 1));
    sm.insert(ft::map<int, int>::value_type(2, 2));
    sm.insert(ft::map<int, int>::value_type(3, 3));
    sm.insert(ft::map<int, int>::value_type(4, 4));

    ft::map<int, int> ft_m(fm);
    ft::map<int, int> std_m(sm);

    LABEL("std", "ft");
    ROW("empty", std_m.empty(), ft_m.empty());
    ROW("size", std_m.size(), ft_m.size());

    print_map("std", std_m);
    print_map("ft ", ft_m);
  }
  {
    SUBTITLE("operator(cpa)");
    ft::map<int, int> fm;
    ft::map<int, int> sm;

    fm.insert(ft::map<int, int>::value_type(1, 1));
    fm.insert(ft::map<int, int>::value_type(2, 2));
    fm.insert(ft::map<int, int>::value_type(3, 3));
    fm.insert(ft::map<int, int>::value_type(4, 4));

    sm.insert(ft::map<int, int>::value_type(1, 1));
    sm.insert(ft::map<int, int>::value_type(2, 2));
    sm.insert(ft::map<int, int>::value_type(3, 3));
    sm.insert(ft::map<int, int>::value_type(4, 4));

    ft::map<int, int> ft_m;
    ft::map<int, int> std_m;

    ft_m = fm;
    std_m = sm;

    LABEL("std", "ft");
    ROW("empty", std_m.empty(), ft_m.empty());
    ROW("size", std_m.size(), ft_m.size());

    print_map("std", std_m);
    print_map("ft ", ft_m);
  }
  {
    SUBTITLE("map.at()");

    ft::map<int, int> ft_m;
    ft::map<int, int> std_m;

    ft_m.insert(ft::map<int, int>::value_type(1, 1));
    ft_m.insert(ft::map<int, int>::value_type(2, 2));
    ft_m.insert(ft::map<int, int>::value_type(3, 3));
    ft_m.insert(ft::map<int, int>::value_type(4, 4));

    std_m.insert(ft::map<int, int>::value_type(1, 1));
    std_m.insert(ft::map<int, int>::value_type(2, 2));
    std_m.insert(ft::map<int, int>::value_type(3, 3));
    std_m.insert(ft::map<int, int>::value_type(4, 4));

    LABEL("std", "ft");
    ROW("at(1)", std_m.at(1), ft_m.at(1));
    ROW("at(2)", std_m.at(2), ft_m.at(2));
    ROW("at(3)", std_m.at(3), ft_m.at(3));
    TRYROW("at(-1)", std_m.at(-1), ft_m.at(-1));
    print_map("std", std_m);
    print_map("ft ", ft_m);
  }

  {
    SUBTITLE("map[]");

    ft::map<int, int> ft_m;
    ft::map<int, int> std_m;

    ft_m.insert(ft::map<int, int>::value_type(1, 1));
    ft_m.insert(ft::map<int, int>::value_type(2, 2));
    ft_m.insert(ft::map<int, int>::value_type(3, 3));
    ft_m.insert(ft::map<int, int>::value_type(4, 4));

    std_m.insert(ft::map<int, int>::value_type(1, 1));
    std_m.insert(ft::map<int, int>::value_type(2, 2));
    std_m.insert(ft::map<int, int>::value_type(3, 3));
    std_m.insert(ft::map<int, int>::value_type(4, 4));

    LABEL("std", "ft");
    ROW("[1]", std_m[1], ft_m[1]);
    ROW("[2]", std_m[2], ft_m[2]);
    ROW("[3]", std_m[3], ft_m[3]);
    // ROW("[-10]", std_m[-10], ft_m[-10]);
    // ROW("[-1]", std_m[-1], ft_m[-1]);
    // ROW("[-2]", std_m[-2], ft_m[-2]);
    print_map("std", std_m);
    print_map("ft ", ft_m);
  }

  {
    SUBTITLE("map.max_size()");
    ft::map<int, int> ft_m;
    ft::map<int, int> std_m;

    ROW("max_size", std_m.max_size(), ft_m.max_size());
  }

  {
    SUBTITLE("map.clear()");
    ft::map<int, int> ft_m;
    ft::map<int, int> std_m;

    ft_m.insert(ft::map<int, int>::value_type(1, 1));
    ft_m.insert(ft::map<int, int>::value_type(2, 2));
    ft_m.insert(ft::map<int, int>::value_type(3, 3));
    ft_m.insert(ft::map<int, int>::value_type(4, 4));

    std_m.insert(ft::map<int, int>::value_type(1, 1));
    std_m.insert(ft::map<int, int>::value_type(2, 2));
    std_m.insert(ft::map<int, int>::value_type(3, 3));
    std_m.insert(ft::map<int, int>::value_type(4, 4));

    LABEL("std", "ft");
    ROW("empty", std_m.empty(), ft_m.empty());
    ROW("size", std_m.size(), ft_m.size());

    ft_m.clear();
    std_m.clear();

    std::cout << '\n';

    ROW("empty", std_m.empty(), ft_m.empty());
    ROW("size", std_m.size(), ft_m.size());
  }
  {
    SUBTITLE("map.insert(value)");
    ft::map<int, int> ft_m;
    ft::map<int, int> std_m;

    ft_m.insert(ft::map<int, int>::value_type(1, 1));
    ft_m.insert(ft::map<int, int>::value_type(1, 1));

    std_m.insert(ft::map<int, int>::value_type(1, 1));
    std_m.insert(ft::map<int, int>::value_type(1, 1));

    print_map("std", std_m);
    print_map("ft ", ft_m);

    ft_m.insert(ft::map<int, int>::value_type(2, 2));

    std_m.insert(ft::map<int, int>::value_type(2, 2));

    print_map("std", std_m);
    print_map("ft ", ft_m);

    ft_m.insert(ft::map<int, int>::value_type(3, 2));
    ft_m.insert(ft::map<int, int>::value_type(-1, 1));

    std_m.insert(ft::map<int, int>::value_type(3, 2));
    std_m.insert(ft::map<int, int>::value_type(-1, 1));

    print_map("std", std_m);
    print_map("ft ", ft_m);
  }
  {
    SUBTITLE("map.insert(hint, value)");
    ft::map<int, int> ft_m;
    ft::map<int, int> std_m;

    ft_m.insert(ft::map<int, int>::value_type(1, 1));
    ft_m.insert(ft::map<int, int>::value_type(2, 2));
    ft_m.insert(ft::map<int, int>::value_type(3, 3));
    ft_m.insert(ft::map<int, int>::value_type(4, 4));

    std_m.insert(ft::map<int, int>::value_type(1, 1));
    std_m.insert(ft::map<int, int>::value_type(2, 2));
    std_m.insert(ft::map<int, int>::value_type(3, 3));
    std_m.insert(ft::map<int, int>::value_type(4, 4));

    ft::map<int, int>::iterator it = std_m.end();

    --it;
    --it;
    std_m.insert(it, ft::map<int, int>::value_type(-1, 1));
    ft_m.insert(--(--(ft_m.end())), ft::map<int, int>::value_type(-1, 1));
    print_map("std", std_m);
    print_map("ft ", ft_m);
  }
  {
    SUBTITLE("map.insert(iter)");
    ft::map<int, int> ft_m;
    ft::map<int, int> std_m;

    ft::map<int, int> std_1;
    ft::map<int, int> std_2;
    ft::map<int, int> std_3;

    std_1.insert(ft::map<int, int>::value_type(1, 1));
    std_1.insert(ft::map<int, int>::value_type(2, 2));
    std_1.insert(ft::map<int, int>::value_type(3, 3));
    std_1.insert(ft::map<int, int>::value_type(-4, 4));

    std_2.insert(std_1.begin(), std_1.end());

    std_1.insert(ft::map<int, int>::value_type(-1, 1));
    std_1.insert(ft::map<int, int>::value_type(2, 2));
    std_1.insert(ft::map<int, int>::value_type(-3, 3));
    std_1.insert(ft::map<int, int>::value_type(4, 4));

    std_3.insert(std_1.begin(), std_1.end());

    LABEL("std", "ft");

    ft_m.insert(std_1.begin(), std_1.end());
    std_m.insert(std_1.begin(), std_1.end());

    ft_m.insert(std_1.begin(), std_1.end());
    std_m.insert(std_1.begin(), std_1.end());

    ROW("size", std_m.size(), ft_m.size());

    print_map("std", std_m);
    print_map("ft ", ft_m);

    ft_m.insert(std_2.begin(), std_2.end());
    std_m.insert(std_2.begin(), std_2.end());

    ROW("size", std_m.size(), ft_m.size());

    print_map("std", std_m);
    print_map("ft ", ft_m);

    ft_m.insert(std_3.begin(), std_3.end());
    std_m.insert(std_3.begin(), std_3.end());

    ROW("size", std_m.size(), ft_m.size());

    print_map("std", std_m);
    print_map("ft ", ft_m);
  }
  {
    SUBTITLE("map.erase(pos)");

    ft::map<int, int> std_v;
    ft::map<int, int> ft_v;
    std_v.insert(ft::map<int, int>::value_type(1, 1));
    std_v.insert(ft::map<int, int>::value_type(2, 2));
    std_v.insert(ft::map<int, int>::value_type(3, 3));
    ft_v.insert(ft::map<int, int>::value_type(1, 1));
    ft_v.insert(ft::map<int, int>::value_type(2, 2));
    ft_v.insert(ft::map<int, int>::value_type(3, 3));

    LABEL("std", "ft");
    ROW("size", std_v.size(), ft_v.size());

    print_map("std", std_v);
    print_map("ft ", ft_v);

    std_v.erase(++std_v.begin());
    ft_v.erase(++ft_v.begin());
    ROW("size", std_v.size(), ft_v.size());

    print_map("std", std_v);
    print_map("ft ", ft_v);

    std_v.erase(--std_v.end());
    ft_v.erase(--ft_v.end());
    ROW("size", std_v.size(), ft_v.size());

    print_map("std", std_v);
    print_map("ft ", ft_v);

    std_v.erase(std_v.begin());
    ft_v.erase(ft_v.begin());
    ROW("size", std_v.size(), ft_v.size());

    print_map("std", std_v);
    print_map("ft ", ft_v);

    /* Error std
     * ft_v.erase(ft_v.begin());
     * std_v.erase(std_v.begin());
     *
     * ROW("size", std_v.size(), ft_v.size());
     * print_map("std", std_v);
     * print_map("ft ", ft_v);
     */
  }

  {
    SUBTITLE("map.erase(iter)");
    ft::map<int, int> ft_v;
    ft::map<int, int> std_v;

    ft::map<int, int> std_1;

    std_1.insert(ft::map<int, int>::value_type(1, 1));
    std_1.insert(ft::map<int, int>::value_type(2, 2));
    std_1.insert(ft::map<int, int>::value_type(3, 3));
    std_1.insert(ft::map<int, int>::value_type(-4, 4));
    std_1.insert(ft::map<int, int>::value_type(-1, 1));
    std_1.insert(ft::map<int, int>::value_type(2, 2));
    std_1.insert(ft::map<int, int>::value_type(-3, 3));
    std_1.insert(ft::map<int, int>::value_type(4, 4));
    std_1.insert(ft::map<int, int>::value_type(5, 5));
    std_1.insert(ft::map<int, int>::value_type(6, 6));

    LABEL("std", "ft");

    ft_v.insert(std_1.begin(), std_1.end());
    std_v.insert(std_1.begin(), std_1.end());

    ROW("size", std_v.size(), ft_v.size());

    print_map("std", std_v);
    print_map("ft ", ft_v);

    ft_v.erase(ft_v.begin(), ++(++(ft_v.begin())));
    std_v.erase(std_v.begin(), ++(++std_v.begin()));

    ROW("size", std_v.size(), ft_v.size());

    print_map("std", std_v);
    print_map("ft ", ft_v);

    ft_v.erase(--(--(ft_v.end())), ft_v.end());
    std_v.erase(--(--std_v.end()), std_v.end());

    ROW("size", std_v.size(), ft_v.size());

    print_map("std", std_v);
    print_map("ft ", ft_v);

    ft_v.erase(++(++(ft_v.begin())), --(--(ft_v.end())));
    std_v.erase(++(++std_v.begin()), --(--std_v.end()));

    ROW("size", std_v.size(), ft_v.size());

    print_map("std", std_v);
    print_map("ft ", ft_v);

    ft_v.erase(ft_v.begin(), ft_v.end());
    std_v.erase(std_v.begin(), std_v.end());

    ROW("size", std_v.size(), ft_v.size());

    print_map("std", std_v);
    print_map("ft ", ft_v);
  }
  {
    SUBTITLE("map.erase(key)");
    ft::map<int, int> ft_v;
    ft::map<int, int> std_v;

    ft::map<int, int> std_1;

    std_1.insert(ft::map<int, int>::value_type(2, 2));
    std_1.insert(ft::map<int, int>::value_type(3, 3));
    std_1.insert(ft::map<int, int>::value_type(-4, 4));
    std_1.insert(ft::map<int, int>::value_type(-1, 1));
    std_1.insert(ft::map<int, int>::value_type(2, 2));
    std_1.insert(ft::map<int, int>::value_type(-3, 3));
    std_1.insert(ft::map<int, int>::value_type(4, 4));
    std_1.insert(ft::map<int, int>::value_type(5, 5));
    std_1.insert(ft::map<int, int>::value_type(6, 6));

    ft_v.insert(std_1.begin(), std_1.end());
    std_v.insert(std_1.begin(), std_1.end());

    LABEL("std", "ft");

    std_v.erase(2);
    ft_v.erase(2);
    ROW("size", std_v.size(), ft_v.size());

    print_map("std", std_v);
    print_map("ft ", ft_v);

    std_v.erase(-4);
    ft_v.erase(-4);
    ROW("size", std_v.size(), ft_v.size());

    print_map("std", std_v);
    print_map("ft ", ft_v);

    std_v.erase(-3);
    ft_v.erase(-3);
    ROW("size", std_v.size(), ft_v.size());

    print_map("std", std_v);
    print_map("ft ", ft_v);

    std_v.erase(6);
    ft_v.erase(6);
    ROW("size", std_v.size(), ft_v.size());

    print_map("std", std_v);
    print_map("ft ", ft_v);
  }

  {
    SUBTITLE("map.swap(other)");

    ft::map<int, int> std_m;
    ft::map<int, int> ft_m;

    ft::map<int, int> std_m2;
    ft::map<int, int> ft_m2;

    ft_m.insert(ft::map<int, int>::value_type(1, 1));
    ft_m.insert(ft::map<int, int>::value_type(2, 2));
    ft_m.insert(ft::map<int, int>::value_type(3, 3));
    ft_m.insert(ft::map<int, int>::value_type(4, 4));

    ft_m2.insert(ft::map<int, int>::value_type(-1, -1));
    ft_m2.insert(ft::map<int, int>::value_type(-2, -2));
    ft_m2.insert(ft::map<int, int>::value_type(-3, -3));
    ft_m2.insert(ft::map<int, int>::value_type(-4, -4));

    std_m.insert(ft::map<int, int>::value_type(1, 1));
    std_m.insert(ft::map<int, int>::value_type(2, 2));
    std_m.insert(ft::map<int, int>::value_type(3, 3));
    std_m.insert(ft::map<int, int>::value_type(4, 4));

    std_m2.insert(ft::map<int, int>::value_type(-1, -1));
    std_m2.insert(ft::map<int, int>::value_type(-2, -2));
    std_m2.insert(ft::map<int, int>::value_type(-3, -3));
    std_m2.insert(ft::map<int, int>::value_type(-4, -4));

    print_map("std ", std_m);
    print_map("std2", std_m2);

    print_map("ft  ", ft_m);
    print_map("ft2 ", ft_m2);

    std::cout << '\n';

    ft_m.swap(ft_m2);
    std_m.swap(std_m2);

    print_map("std ", std_m);
    print_map("std2", std_m2);

    print_map("ft  ", ft_m);
    print_map("ft2 ", ft_m2);

    std::cout << '\n';

    ft_m.swap(ft_m2);
    std_m.swap(std_m2);

    print_map("std ", std_m);
    print_map("std2", std_m2);

    print_map("ft  ", ft_m);
    print_map("ft2 ", ft_m2);
  }
  {
    SUBTITLE("map.swap(other)");

    ft::map<int, int> std_m;
    ft::map<int, int> ft_m;

    ft::map<int, int> std_m2;
    ft::map<int, int> ft_m2;

    ft_m.insert(ft::map<int, int>::value_type(1, 1));
    ft_m.insert(ft::map<int, int>::value_type(2, 2));
    ft_m.insert(ft::map<int, int>::value_type(3, 3));
    ft_m.insert(ft::map<int, int>::value_type(4, 4));

    ft_m2.insert(ft::map<int, int>::value_type(-1, -1));
    ft_m2.insert(ft::map<int, int>::value_type(-2, -2));
    ft_m2.insert(ft::map<int, int>::value_type(-3, -3));
    ft_m2.insert(ft::map<int, int>::value_type(-4, -4));

    std_m.insert(ft::map<int, int>::value_type(1, 1));
    std_m.insert(ft::map<int, int>::value_type(2, 2));
    std_m.insert(ft::map<int, int>::value_type(3, 3));
    std_m.insert(ft::map<int, int>::value_type(4, 4));

    std_m2.insert(ft::map<int, int>::value_type(-1, -1));
    std_m2.insert(ft::map<int, int>::value_type(-2, -2));
    std_m2.insert(ft::map<int, int>::value_type(-3, -3));
    std_m2.insert(ft::map<int, int>::value_type(-4, -4));

    print_map("std ", std_m);
    print_map("std2", std_m2);

    print_map("ft  ", ft_m);
    print_map("ft2 ", ft_m2);

    std::cout << '\n';

    ft::swap(ft_m, ft_m2);
    std::swap(std_m, std_m2);

    print_map("std ", std_m);
    print_map("std2", std_m2);

    print_map("ft  ", ft_m);
    print_map("ft2 ", ft_m2);

    std::cout << '\n';

    ft::swap(ft_m, ft_m2);
    std::swap(std_m, std_m2);

    print_map("std ", std_m);
    print_map("std2", std_m2);

    print_map("ft  ", ft_m);
    print_map("ft2 ", ft_m2);
  }
  {
    SUBTITLE("map.count(key)");
    ft::map<int, int> std_m;
    ft::map<int, int> ft_m;

    ft_m.insert(ft::map<int, int>::value_type(10, 10));
    ft_m.insert(ft::map<int, int>::value_type(20, 20));
    ft_m.insert(ft::map<int, int>::value_type(30, 30));
    ft_m.insert(ft::map<int, int>::value_type(40, 40));

    std_m.insert(ft::map<int, int>::value_type(10, 10));
    std_m.insert(ft::map<int, int>::value_type(20, 20));
    std_m.insert(ft::map<int, int>::value_type(30, 30));
    std_m.insert(ft::map<int, int>::value_type(40, 40));

    LABEL("std", "ft");
    ROW("count", std_m.count(20), ft_m.count(20));
    ROW("count", std_m.count(15), ft_m.count(15));
  }
  {
    SUBTITLE("map.find(key)");
    ft::map<int, int> std_m;
    ft::map<int, int> ft_m;

    ft_m.insert(ft::map<int, int>::value_type(10, 10));
    ft_m.insert(ft::map<int, int>::value_type(20, 20));
    ft_m.insert(ft::map<int, int>::value_type(30, 30));
    ft_m.insert(ft::map<int, int>::value_type(40, 40));

    std_m.insert(ft::map<int, int>::value_type(10, 10));
    std_m.insert(ft::map<int, int>::value_type(20, 20));
    std_m.insert(ft::map<int, int>::value_type(30, 30));
    std_m.insert(ft::map<int, int>::value_type(40, 40));

    LABEL("std", "ft");
    ROW("first", std_m.find(20)->first, ft_m.find(20)->first);
    ROW("second", std_m.find(20)->second, ft_m.find(20)->second);
    ROW("first", std_m.find(15)->first, ft_m.find(15)->first);
    ROW("second", std_m.find(15)->second, ft_m.find(15)->second);
  }
  {
    SUBTITLE("map.equal_range(key)");
    ft::map<int, int> ft_v;
    ft::map<int, int> std_v;

    ft::map<int, int> std_1;

    std_1.insert(ft::map<int, int>::value_type(2, 2));
    std_1.insert(ft::map<int, int>::value_type(3, 3));
    std_1.insert(ft::map<int, int>::value_type(-4, 4));
    std_1.insert(ft::map<int, int>::value_type(-1, 1));
    std_1.insert(ft::map<int, int>::value_type(2, 2));
    std_1.insert(ft::map<int, int>::value_type(-3, 3));
    std_1.insert(ft::map<int, int>::value_type(4, 4));
    std_1.insert(ft::map<int, int>::value_type(5, 5));
    std_1.insert(ft::map<int, int>::value_type(6, 6));

    // print_map("std", std_v);
    // print_map("ft ", ft_v);

    // ft::map<int, int>::iterator stdi = std_v.equal_range(2).first;
    // ft::map<int, int>::iterator  fti = ft_v.equal_range(2).first;

    ft_v.insert(std_1.begin(), std_1.end());
    std_v.insert(std_1.begin(), std_1.end());

    print_map("std", std_v);
    print_map("ft ", ft_v);

    {
      ft::map<int, int>::iterator stdi2 = std_v.equal_range(2).first;
      ft::map<int, int>::iterator fti2 = ft_v.equal_range(2).first;
      ft::map<int, int>::iterator stdi3 = std_v.equal_range(2).second;
      ft::map<int, int>::iterator fti3 = ft_v.equal_range(2).second;

      LABEL("std", "ft");
      ROW("first", stdi2->first, fti2->first);
      ROW("second", stdi2->second, fti2->second);
      ROW("first", stdi3->first, fti3->first);
      ROW("second", stdi3->second, fti3->second);
    }
    {
      ft::map<int, int>::iterator stdi4 = std_v.equal_range(5).first;
      ft::map<int, int>::iterator fti4 = ft_v.equal_range(5).first;
      ft::map<int, int>::iterator stdi5 = std_v.equal_range(5).second;
      ft::map<int, int>::iterator fti5 = ft_v.equal_range(5).second;

      LABEL("std", "ft");
      ROW("first", stdi4->first, fti4->first);
      ROW("second", stdi4->second, fti4->second);
      ROW("first", stdi5->first, fti5->first);
      ROW("second", stdi5->second, fti5->second);
    }
    {
      ft::map<int, int>::iterator stdi4 = std_v.equal_range(0).first;
      ft::map<int, int>::iterator fti4 = ft_v.equal_range(0).first;
      ft::map<int, int>::iterator stdi5 = std_v.equal_range(0).second;
      ft::map<int, int>::iterator fti5 = ft_v.equal_range(0).second;

      LABEL("std", "ft");
      ROW("first", stdi4->first, fti4->first);
      ROW("second", stdi4->second, fti4->second);
      ROW("first", stdi5->first, fti5->first);
      ROW("second", stdi5->second, fti5->second);
    }
    {
      ft::map<int, int>::iterator stdi4 = std_v.equal_range(-4).first;
      ft::map<int, int>::iterator fti4 = ft_v.equal_range(-4).first;
      ft::map<int, int>::iterator stdi5 = std_v.equal_range(-4).second;
      ft::map<int, int>::iterator fti5 = ft_v.equal_range(-4).second;

      LABEL("std", "ft");
      ROW("first", stdi4->first, fti4->first);
      ROW("second", stdi4->second, fti4->second);
      ROW("first", stdi5->first, fti5->first);
      ROW("second", stdi5->second, fti5->second);
    }
    {
      ft::map<int, int>::iterator stdi4 = std_v.equal_range(-5).first;
      ft::map<int, int>::iterator fti4 = ft_v.equal_range(-5).first;
      ft::map<int, int>::iterator stdi5 = std_v.equal_range(-5).second;
      ft::map<int, int>::iterator fti5 = ft_v.equal_range(-5).second;

      LABEL("std", "ft");
      ROW("first", stdi4->first, fti4->first);
      ROW("second", stdi4->second, fti4->second);
      ROW("first", stdi5->first, fti5->first);
      ROW("second", stdi5->second, fti5->second);
    }
  }

  {
    SUBTITLE("map.upper_bound(key)");
    ft::map<int, int> std_m;
    ft::map<int, int> ft_m;

    ft_m.insert(ft::map<int, int>::value_type(10, 10));
    ft_m.insert(ft::map<int, int>::value_type(20, 20));
    ft_m.insert(ft::map<int, int>::value_type(30, 30));
    ft_m.insert(ft::map<int, int>::value_type(40, 40));

    std_m.insert(ft::map<int, int>::value_type(10, 10));
    std_m.insert(ft::map<int, int>::value_type(20, 20));
    std_m.insert(ft::map<int, int>::value_type(30, 30));
    std_m.insert(ft::map<int, int>::value_type(40, 40));

    ft_m.lower_bound(15);

    LABEL("std", "ft");

    ROW("first", std_m.upper_bound(-10)->first, ft_m.upper_bound(-10)->first);
    ROW("second", std_m.upper_bound(-10)->second, ft_m.upper_bound(-10)->second);

    ROW("first", std_m.upper_bound(15)->first, ft_m.upper_bound(15)->first);
    ROW("second", std_m.upper_bound(15)->second, ft_m.upper_bound(15)->second);

    ROW("first", std_m.upper_bound(10)->first, ft_m.upper_bound(10)->first);
    ROW("second", std_m.upper_bound(10)->second, ft_m.upper_bound(10)->second);

    ROW("first", std_m.upper_bound(10)->first, ft_m.upper_bound(10)->first);
    ROW("second", std_m.upper_bound(10)->second, ft_m.upper_bound(10)->second);

    ROW("first", std_m.upper_bound(11)->first, ft_m.upper_bound(11)->first);
    ROW("second", std_m.upper_bound(11)->second, ft_m.upper_bound(11)->second);

    // ROW("first", std_m.upper_bound(40)->first, ft_m.upper_bound(40)->first);
    // ROW("second", std_m.upper_bound(40)->second, ft_m.upper_bound(40)->second);

    // ROW("first", std_m.upper_bound(41)->first, ft_m.upper_bound(41)->first);
    // ROW("second", std_m.upper_bound(41)->second, ft_m.upper_bound(41)->second);
  }
  {
    SUBTITLE("map.lower_bound(key)");
    ft::map<int, int> std_m;
    ft::map<int, int> ft_m;

    ft_m.insert(ft::map<int, int>::value_type(10, 10));
    ft_m.insert(ft::map<int, int>::value_type(20, 20));
    ft_m.insert(ft::map<int, int>::value_type(30, 30));
    ft_m.insert(ft::map<int, int>::value_type(40, 40));

    std_m.insert(ft::map<int, int>::value_type(10, 10));
    std_m.insert(ft::map<int, int>::value_type(20, 20));
    std_m.insert(ft::map<int, int>::value_type(30, 30));
    std_m.insert(ft::map<int, int>::value_type(40, 40));

    ft_m.lower_bound(15);

    LABEL("std", "ft");

    ROW("first", std_m.lower_bound(-10)->first, ft_m.lower_bound(-10)->first);
    ROW("second", std_m.lower_bound(-10)->second, ft_m.lower_bound(-10)->second);

    ROW("first", std_m.lower_bound(15)->first, ft_m.lower_bound(15)->first);
    ROW("second", std_m.lower_bound(15)->second, ft_m.lower_bound(15)->second);

    ROW("first", std_m.lower_bound(10)->first, ft_m.lower_bound(10)->first);
    ROW("second", std_m.lower_bound(10)->second, ft_m.lower_bound(10)->second);

    ROW("first", std_m.lower_bound(10)->first, ft_m.lower_bound(10)->first);
    ROW("second", std_m.lower_bound(10)->second, ft_m.lower_bound(10)->second);

    ROW("first", std_m.lower_bound(11)->first, ft_m.lower_bound(11)->first);
    ROW("second", std_m.lower_bound(11)->second, ft_m.lower_bound(11)->second);

    ROW("first", std_m.lower_bound(40)->first, ft_m.lower_bound(40)->first);
    ROW("second", std_m.lower_bound(40)->second, ft_m.lower_bound(40)->second);

    // ROW("first", std_m.lower_bound(41)->first, ft_m.lower_bound(41)->first);
    // ROW("second", std_m.lower_bound(41)->second, ft_m.lower_bound(41)->second);
  }
  {
    SUBTITLE("operator==(eq)");

    ft::map<int, int> std_v;
    ft::map<int, int> ft_v;

    std_v.insert(ft::map<int, int>::value_type(1, 1));
    std_v.insert(ft::map<int, int>::value_type(2, 2));
    std_v.insert(ft::map<int, int>::value_type(3, 3));
    ft_v.insert(ft::map<int, int>::value_type(1, 1));
    ft_v.insert(ft::map<int, int>::value_type(2, 2));
    ft_v.insert(ft::map<int, int>::value_type(3, 3));

    ft::map<int, int> std_v2(std_v);
    ft::map<int, int> ft_v2(ft_v);

    LABEL("std", "ft");
    ROW("equal", (std_v == std_v2), (ft_v == ft_v2));
    std_v.erase(1);
    ft_v.erase(1);
    ROW("equal", (std_v == std_v2), (ft_v == ft_v2));
  }
  {
    SUBTITLE("operator!=(nq)");

    ft::map<int, int> std_v;
    ft::map<int, int> ft_v;

    std_v.insert(ft::map<int, int>::value_type(1, 1));
    std_v.insert(ft::map<int, int>::value_type(2, 2));
    std_v.insert(ft::map<int, int>::value_type(3, 3));
    ft_v.insert(ft::map<int, int>::value_type(1, 1));
    ft_v.insert(ft::map<int, int>::value_type(2, 2));
    ft_v.insert(ft::map<int, int>::value_type(3, 3));

    ft::map<int, int> std_v2(std_v);
    ft::map<int, int> ft_v2(ft_v);

    LABEL("std", "ft");
    ROW("not equal", (std_v != std_v2), (ft_v != ft_v2));
    std_v.erase(1);
    ft_v.erase(1);
    ROW("not equal", (std_v != std_v2), (ft_v != ft_v2));
  }
  {
    SUBTITLE("operator<(l)");
    ft::map<int, int> std_v;
    ft::map<int, int> ft_v;
    ft::map<int, int> std_v2;
    ft::map<int, int> ft_v2;

    LABEL("std", "ft");
    ROW("less", (std_v < std_v2), (ft_v < ft_v2));

    ft_v2.insert(ft::map<int, int>::value_type(1, 1));
    std_v2.insert(ft::map<int, int>::value_type(1, 1));

    ROW("less", (std_v < std_v2), (ft_v < ft_v2));

    ft_v.insert(ft::map<int, int>::value_type(2, 2));
    std_v.insert(ft::map<int, int>::value_type(2, 2));

    ROW("less", (std_v < std_v2), (ft_v < ft_v2));

    ft_v2.insert(ft::map<int, int>::value_type(3, 3));
    std_v2.insert(ft::map<int, int>::value_type(3, 3));

    ROW("less", (std_v < std_v2), (ft_v < ft_v2));
  }
  {
    SUBTITLE("operator<=(le)");
    ft::map<int, int> std_v;
    ft::map<int, int> ft_v;
    ft::map<int, int> std_v2;
    ft::map<int, int> ft_v2;

    LABEL("std", "ft");
    ROW("less equal", (std_v <= std_v2), (ft_v <= ft_v2));

    ft_v2.insert(ft::map<int, int>::value_type(1, 1));
    std_v2.insert(ft::map<int, int>::value_type(1, 1));

    ROW("less equal", (std_v <= std_v2), (ft_v <= ft_v2));

    ft_v.insert(ft::map<int, int>::value_type(2, 2));
    std_v.insert(ft::map<int, int>::value_type(2, 2));

    ROW("less equal", (std_v <= std_v2), (ft_v <= ft_v2));

    ft_v2.insert(ft::map<int, int>::value_type(3, 3));
    std_v2.insert(ft::map<int, int>::value_type(3, 3));

    ROW("less equal", (std_v <= std_v2), (ft_v <= ft_v2));
  }
  {
    SUBTITLE("operator>(g)");
    ft::map<int, int> std_v;
    ft::map<int, int> ft_v;
    ft::map<int, int> std_v2;
    ft::map<int, int> ft_v2;

    LABEL("std", "ft");
    ROW("grater", (std_v > std_v2), (ft_v > ft_v2));

    ft_v2.insert(ft::map<int, int>::value_type(1, 1));
    std_v2.insert(ft::map<int, int>::value_type(1, 1));

    ROW("grater", (std_v > std_v2), (ft_v > ft_v2));

    ft_v.insert(ft::map<int, int>::value_type(2, 2));
    std_v.insert(ft::map<int, int>::value_type(2, 2));

    ROW("grater", (std_v > std_v2), (ft_v > ft_v2));

    ft_v2.insert(ft::map<int, int>::value_type(3, 3));
    std_v2.insert(ft::map<int, int>::value_type(3, 3));

    ROW("grater", (std_v > std_v2), (ft_v > ft_v2));
  }
  {
    SUBTITLE("operator>=(ge)");
    ft::map<int, int> std_v;
    ft::map<int, int> ft_v;
    ft::map<int, int> std_v2;
    ft::map<int, int> ft_v2;

    LABEL("std", "ft");
    ROW("grater equal", (std_v >= std_v2), (ft_v >= ft_v2));

    ft_v2.insert(ft::map<int, int>::value_type(1, 1));
    std_v2.insert(ft::map<int, int>::value_type(1, 1));

    ROW("grater equal", (std_v >= std_v2), (ft_v >= ft_v2));

    ft_v.insert(ft::map<int, int>::value_type(2, 2));
    std_v.insert(ft::map<int, int>::value_type(2, 2));

    ROW("grater equal", (std_v >= std_v2), (ft_v >= ft_v2));

    ft_v2.insert(ft::map<int, int>::value_type(3, 3));
    std_v2.insert(ft::map<int, int>::value_type(3, 3));

    ROW("grater equal", (std_v >= std_v2), (ft_v >= ft_v2));
  }
}

int main(int argc, char** argv) {
  if (argc != 2) {
    std::cerr << "Usage: ./test seed" << std::endl;
    std::cerr << "Provide a seed please" << std::endl;
    std::cerr << "Count value:" << COUNT << std::endl;
    return 1;
  }
  const int seed = atoi(argv[1]);
  srand(seed);

  subject_test();

  vector_functional_test();
  stack_functional_test();
  map_functional_test();

  return (0);
}