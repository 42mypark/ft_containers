#include <iostream>
#include <map>

#include "macro.hpp"
#include "map.hpp"

template <typename Cont>
void print_cont(const std::string& tag, Cont c) {
  std::cout << tag << ": ";
  for (typename Cont::iterator it = c.begin(); it != c.end(); ++it) {
    std::cout << "(" << it->first << ", " << it->second << ") ";
  }
  std::cout << std::endl;
}

int main() {
  TITLE("map");
  {
    SUBTITLE("CONSTRUCTOR 1");
    ft::map<int, char>  ft_m;
    std::map<int, char> std_m;

    LABEL("std", "ft");
    ROW("empty", std_m.empty(), ft_m.empty());
    ROW("size", std_m.size(), ft_m.size());
  }
  {
    SUBTITLE("CONSTRUCTOR 3");
    ft::map<int, int>  fm;
    std::map<int, int> sm;

    fm.insert(ft::map<int, int>::value_type(1, 1));
    fm.insert(ft::map<int, int>::value_type(2, 2));
    fm.insert(ft::map<int, int>::value_type(3, 3));
    fm.insert(ft::map<int, int>::value_type(4, 4));

    sm.insert(std::map<int, int>::value_type(1, 1));
    sm.insert(std::map<int, int>::value_type(2, 2));
    sm.insert(std::map<int, int>::value_type(3, 3));
    sm.insert(std::map<int, int>::value_type(4, 4));

    ft::map<int, int>  ft_m(fm.begin(), fm.end());
    std::map<int, int> std_m(sm.begin(), sm.end());

    LABEL("std", "ft");
    ROW("empty", std_m.empty(), ft_m.empty());
    ROW("size", std_m.size(), ft_m.size());

    print_cont("std", std_m);
    print_cont("ft ", ft_m);
  }
  {
    SUBTITLE("CONSTRUCTOR 4");
    ft::map<int, int>  fm;
    std::map<int, int> sm;

    fm.insert(ft::map<int, int>::value_type(1, 1));
    fm.insert(ft::map<int, int>::value_type(2, 2));
    fm.insert(ft::map<int, int>::value_type(3, 3));
    fm.insert(ft::map<int, int>::value_type(4, 4));

    sm.insert(std::map<int, int>::value_type(1, 1));
    sm.insert(std::map<int, int>::value_type(2, 2));
    sm.insert(std::map<int, int>::value_type(3, 3));
    sm.insert(std::map<int, int>::value_type(4, 4));

    ft::map<int, int>  ft_m(fm);
    std::map<int, int> std_m(sm);

    LABEL("std", "ft");
    ROW("empty", std_m.empty(), ft_m.empty());
    ROW("size", std_m.size(), ft_m.size());

    print_cont("std", std_m);
    print_cont("ft ", ft_m);
  }
  {
    SUBTITLE("operator(cpa)");
    ft::map<int, int>  fm;
    std::map<int, int> sm;

    fm.insert(ft::map<int, int>::value_type(1, 1));
    fm.insert(ft::map<int, int>::value_type(2, 2));
    fm.insert(ft::map<int, int>::value_type(3, 3));
    fm.insert(ft::map<int, int>::value_type(4, 4));

    sm.insert(std::map<int, int>::value_type(1, 1));
    sm.insert(std::map<int, int>::value_type(2, 2));
    sm.insert(std::map<int, int>::value_type(3, 3));
    sm.insert(std::map<int, int>::value_type(4, 4));

    ft::map<int, int>  ft_m;
    std::map<int, int> std_m;

    ft_m  = fm;
    std_m = sm;

    LABEL("std", "ft");
    ROW("empty", std_m.empty(), ft_m.empty());
    ROW("size", std_m.size(), ft_m.size());

    print_cont("std", std_m);
    print_cont("ft ", ft_m);
  }
  {
    SUBTITLE("map.at()");

    ft::map<int, int>  ft_m;
    std::map<int, int> std_m;

    ft_m.insert(ft::map<int, int>::value_type(1, 1));
    ft_m.insert(ft::map<int, int>::value_type(2, 2));
    ft_m.insert(ft::map<int, int>::value_type(3, 3));
    ft_m.insert(ft::map<int, int>::value_type(4, 4));

    std_m.insert(std::map<int, int>::value_type(1, 1));
    std_m.insert(std::map<int, int>::value_type(2, 2));
    std_m.insert(std::map<int, int>::value_type(3, 3));
    std_m.insert(std::map<int, int>::value_type(4, 4));

    LABEL("std", "ft");
    ROW("at(1)", std_m.at(1), ft_m.at(1));
    ROW("at(2)", std_m.at(2), ft_m.at(2));
    ROW("at(3)", std_m.at(3), ft_m.at(3));
    TRYROW("at(-1)", std_m.at(-1), ft_m.at(-1));
    print_cont("std", std_m);
    print_cont("ft ", ft_m);
  }

  {
    SUBTITLE("map[]");

    ft::map<int, int>  ft_m;
    std::map<int, int> std_m;

    ft_m.insert(ft::map<int, int>::value_type(1, 1));
    ft_m.insert(ft::map<int, int>::value_type(2, 2));
    ft_m.insert(ft::map<int, int>::value_type(3, 3));
    ft_m.insert(ft::map<int, int>::value_type(4, 4));

    std_m.insert(std::map<int, int>::value_type(1, 1));
    std_m.insert(std::map<int, int>::value_type(2, 2));
    std_m.insert(std::map<int, int>::value_type(3, 3));
    std_m.insert(std::map<int, int>::value_type(4, 4));

    LABEL("std", "ft");
    ROW("[1]", std_m[1], ft_m[1]);
    ROW("[2]", std_m[2], ft_m[2]);
    ROW("[3]", std_m[3], ft_m[3]);
    // ROW("[-10]", std_m[-10], ft_m[-10]);
    // ROW("[-1]", std_m[-1], ft_m[-1]);
    // ROW("[-2]", std_m[-2], ft_m[-2]);
    std_m[6] = 6;
    ft_m[6]  = 6;
    print_cont("std", std_m);
    print_cont("ft ", ft_m);
  }

  {
    SUBTITLE("map.max_size()");
    ft::map<int, int>  ft_m;
    std::map<int, int> std_m;

    ROW("max_size", std_m.max_size(), ft_m.max_size());
  }

  {
    SUBTITLE("map.clear()");
    ft::map<int, int>  ft_m;
    std::map<int, int> std_m;

    ft_m.insert(ft::map<int, int>::value_type(1, 1));
    ft_m.insert(ft::map<int, int>::value_type(2, 2));
    ft_m.insert(ft::map<int, int>::value_type(3, 3));
    ft_m.insert(ft::map<int, int>::value_type(4, 4));

    std_m.insert(std::map<int, int>::value_type(1, 1));
    std_m.insert(std::map<int, int>::value_type(2, 2));
    std_m.insert(std::map<int, int>::value_type(3, 3));
    std_m.insert(std::map<int, int>::value_type(4, 4));

    LABEL("std", "ft");
    ROW("empty", std_m.empty(), ft_m.empty());
    ROW("size", std_m.size(), ft_m.size());

    ft_m.clear();
    std_m.clear();

    std::cout << '\n';

    ROW("empty", std_m.empty(), ft_m.empty());
    ROW("size", std_m.size(), ft_m.size());

    ft_m.insert(ft::map<int, int>::value_type(1, 1));

    std_m.insert(std::map<int, int>::value_type(1, 1));

    std::cout << '\n';

    ROW("empty", std_m.empty(), ft_m.empty());
    ROW("size", std_m.size(), ft_m.size());
  }
  {
    SUBTITLE("map.insert(value)");
    ft::map<int, int>  ft_m;
    std::map<int, int> std_m;

    ft_m.insert(ft::map<int, int>::value_type(1, 1));
    ft_m.insert(ft::map<int, int>::value_type(1, 1));

    std_m.insert(std::map<int, int>::value_type(1, 1));
    std_m.insert(std::map<int, int>::value_type(1, 1));

    print_cont("std", std_m);
    print_cont("ft ", ft_m);

    ft_m.insert(ft::map<int, int>::value_type(2, 2));

    std_m.insert(std::map<int, int>::value_type(2, 2));

    print_cont("std", std_m);
    print_cont("ft ", ft_m);

    ft_m.insert(ft::map<int, int>::value_type(3, 2));
    ft_m.insert(ft::map<int, int>::value_type(-1, 1));

    std_m.insert(std::map<int, int>::value_type(3, 2));
    std_m.insert(std::map<int, int>::value_type(-1, 1));

    print_cont("std", std_m);
    print_cont("ft ", ft_m);
  }
  {
    SUBTITLE("map.insert(hint, value)");
    ft::map<int, int>  ft_m;
    std::map<int, int> std_m;

    for (int i = 0; i < 50; i++) {
      ft_m.insert(ft::map<int, int>::value_type(i, i));
    }
    // ft_m.insert(ft::map<int, int>::value_type(2, 2));
    // ft_m.insert(ft::map<int, int>::value_type(3, 3));
    // ft_m.insert(ft::map<int, int>::value_type(1, 1));
    // ft_m.insert(ft::map<int, int>::value_type(5, 1));
    // ft_m.insert(ft::map<int, int>::value_type(10, 1));
    // ft_m.insert(ft::map<int, int>::value_type(8, 1));
    // ft_m.insert(ft::map<int, int>::value_type(200, 1));
    // ft_m.insert(ft::map<int, int>::value_type(150, 1));
    // ft_m.insert(ft::map<int, int>::value_type(14, 1));
    // ft_m.insert(ft::map<int, int>::value_type(41, 1));
    // ft_m.insert(ft::map<int, int>::value_type(32, 1));
    // ft_m.insert(ft::map<int, int>::value_type(42, 1));
    // ft_m.insert(ft::map<int, int>::value_type(65, 1));
    // ft_m.insert(ft::map<int, int>::value_type(72, 1));
    // ft_m.insert(ft::map<int, int>::value_type(48, 1));
    // ft_m.insert(ft::map<int, int>::value_type(33, 1));

    std_m.insert(std::map<int, int>::value_type(1, 1));
    std_m.insert(std::map<int, int>::value_type(2, 2));
    std_m.insert(std::map<int, int>::value_type(3, 3));
    std_m.insert(std::map<int, int>::value_type(4, 4));

    std::map<int, int>::iterator it = std_m.end();

    --it;
    --it;
    std_m.insert(it, std::map<int, int>::value_type(-1, 1));
    ft_m.insert(ft_m.end() - 2, ft::map<int, int>::value_type(-1, 1));
    print_cont("std", std_m);
    print_cont("ft ", ft_m);
  }
  {
    SUBTITLE("map.insert(iter)");
    ft::map<int, int>  ft_m;
    std::map<int, int> std_m;

    std::map<int, int> std_1;
    std::map<int, int> std_2;
    std::map<int, int> std_3;

    std_1.insert(std::map<int, int>::value_type(1, 1));
    std_1.insert(std::map<int, int>::value_type(2, 2));
    std_1.insert(std::map<int, int>::value_type(3, 3));
    std_1.insert(std::map<int, int>::value_type(-4, 4));

    std_2.insert(std_1.begin(), std_1.end());

    std_1.insert(std::map<int, int>::value_type(-1, 1));
    std_1.insert(std::map<int, int>::value_type(2, 2));
    std_1.insert(std::map<int, int>::value_type(-3, 3));
    std_1.insert(std::map<int, int>::value_type(4, 4));

    std_3.insert(std_1.begin(), std_1.end());

    LABEL("std", "ft");

    ft_m.insert(std_1.begin(), std_1.end());
    std_m.insert(std_1.begin(), std_1.end());

    ft_m.insert(std_1.begin(), std_1.end());
    std_m.insert(std_1.begin(), std_1.end());

    ROW("size", std_m.size(), ft_m.size());

    print_cont("std", std_m);
    print_cont("ft ", ft_m);

    ft_m.insert(std_2.begin(), std_2.end());
    std_m.insert(std_2.begin(), std_2.end());

    ROW("size", std_m.size(), ft_m.size());

    print_cont("std", std_m);
    print_cont("ft ", ft_m);

    ft_m.insert(std_3.begin(), std_3.end());
    std_m.insert(std_3.begin(), std_3.end());

    ROW("size", std_m.size(), ft_m.size());

    print_cont("std", std_m);
    print_cont("ft ", ft_m);
  }
  {
    SUBTITLE("map.erase(pos)");

    std::map<int, int> std_v;
    ft::map<int, int>  ft_v;

    std_v.insert(std::map<int, int>::value_type(1, 1));
    std_v.insert(std::map<int, int>::value_type(2, 2));
    std_v.insert(std::map<int, int>::value_type(3, 3));
    ft_v.insert(ft::map<int, int>::value_type(1, 1));
    ft_v.erase(ft_v.begin());
    print_cont("ft ", ft_v);
    ft_v.insert(ft::map<int, int>::value_type(1, 1));
    ft_v.insert(ft::map<int, int>::value_type(2, 2));
    ft_v.insert(ft::map<int, int>::value_type(3, 3));

    LABEL("std", "ft");
    ROW("size", std_v.size(), ft_v.size());

    print_cont("std", std_v);
    print_cont("ft ", ft_v);

    std_v.erase(std_v.begin());
    ft_v.erase(ft_v.begin());
    ROW("size", std_v.size(), ft_v.size());

    print_cont("std", std_v);
    print_cont("ft ", ft_v);

    std_v.erase(++std_v.begin());
    ft_v.erase(ft_v.begin() + 1);
    ROW("size", std_v.size(), ft_v.size());

    print_cont("std", std_v);
    print_cont("ft ", ft_v);

    std_v.erase(--std_v.end());
    ft_v.erase(ft_v.end() - 1);
    ROW("size", std_v.size(), ft_v.size());

    print_cont("std", std_v);
    print_cont("ft ", ft_v);

    /* Error std
     * ft_v.erase(ft_v.begin());
     * std_v.erase(std_v.begin());
     *
     * ROW("size", std_v.size(), ft_v.size());
     * print_cont("std", std_v);
     * print_cont("ft ", ft_v);
     */
  }

  {
    SUBTITLE("map.erase(iter)");
    ft::map<int, int>  ft_v;
    std::map<int, int> std_v;

    std::map<int, int> std_1;

    std_1.insert(std::map<int, int>::value_type(1, 1));
    std_1.insert(std::map<int, int>::value_type(2, 2));
    std_1.insert(std::map<int, int>::value_type(3, 3));
    std_1.insert(std::map<int, int>::value_type(-4, 4));
    std_1.insert(std::map<int, int>::value_type(-1, 1));
    std_1.insert(std::map<int, int>::value_type(2, 2));
    std_1.insert(std::map<int, int>::value_type(-3, 3));
    std_1.insert(std::map<int, int>::value_type(4, 4));
    std_1.insert(std::map<int, int>::value_type(5, 5));
    std_1.insert(std::map<int, int>::value_type(6, 6));

    LABEL("std", "ft");

    ft_v.insert(std_1.begin(), std_1.end());
    std_v.insert(std_1.begin(), std_1.end());

    ROW("size", std_v.size(), ft_v.size());

    print_cont("std", std_v);
    print_cont("ft ", ft_v);

    ft_v.erase(ft_v.begin(), ft_v.begin() + 2);
    std_v.erase(std_v.begin(), ++(++std_v.begin()));

    ROW("size", std_v.size(), ft_v.size());

    print_cont("std", std_v);
    print_cont("ft ", ft_v);

    ft_v.erase(ft_v.end() - 2, ft_v.end());
    std_v.erase(--(--std_v.end()), std_v.end());

    ROW("size", std_v.size(), ft_v.size());

    print_cont("std", std_v);
    print_cont("ft ", ft_v);

    ft_v.erase(ft_v.begin() + 2, ft_v.end() - 2);
    std_v.erase(++(++std_v.begin()), --(--std_v.end()));

    ROW("size", std_v.size(), ft_v.size());

    print_cont("std", std_v);
    print_cont("ft ", ft_v);

    ft_v.erase(ft_v.begin(), ft_v.end());
    std_v.erase(std_v.begin(), std_v.end());

    ROW("size", std_v.size(), ft_v.size());

    print_cont("std", std_v);
    print_cont("ft ", ft_v);
  }
  {
    SUBTITLE("map.erase(key)");
    ft::map<int, int>  ft_v;
    std::map<int, int> std_v;

    std::map<int, int> std_1;

    std_1.insert(std::map<int, int>::value_type(2, 2));
    std_1.insert(std::map<int, int>::value_type(3, 3));
    std_1.insert(std::map<int, int>::value_type(-4, 4));
    std_1.insert(std::map<int, int>::value_type(-1, 1));
    std_1.insert(std::map<int, int>::value_type(2, 2));
    std_1.insert(std::map<int, int>::value_type(-3, 3));
    std_1.insert(std::map<int, int>::value_type(4, 4));
    std_1.insert(std::map<int, int>::value_type(5, 5));
    std_1.insert(std::map<int, int>::value_type(6, 6));

    ft_v.insert(std_1.begin(), std_1.end());
    std_v.insert(std_1.begin(), std_1.end());

    LABEL("std", "ft");

    ROW("ret", std_v.erase(2), ft_v.erase(2));
    ROW("size", std_v.size(), ft_v.size());

    print_cont("std", std_v);
    print_cont("ft ", ft_v);

    ROW("ret", std_v.erase(-4), ft_v.erase(-4));
    ROW("size", std_v.size(), ft_v.size());

    print_cont("std", std_v);
    print_cont("ft ", ft_v);

    ROW("ret", std_v.erase(-3), ft_v.erase(-3));
    ROW("size", std_v.size(), ft_v.size());

    print_cont("std", std_v);
    print_cont("ft ", ft_v);

    ROW("ret", std_v.erase(6), ft_v.erase(6));
    ROW("size", std_v.size(), ft_v.size());

    print_cont("std", std_v);
    print_cont("ft ", ft_v);

    ROW("ret", std_v.erase(7), ft_v.erase(7));
    ROW("size", std_v.size(), ft_v.size());

    print_cont("std", std_v);
    print_cont("ft ", ft_v);
  }

  {
    SUBTITLE("map.swap(other)");

    std::map<int, int> std_m;
    ft::map<int, int>  ft_m;

    std::map<int, int> std_m2;
    ft::map<int, int>  ft_m2;

    for (int i = 0; i < 4; i++) {
      ft_m.insert(ft::map<int, int>::value_type(i, i));
      std_m.insert(std::map<int, int>::value_type(i, i));
    }

    ft_m.swap(ft_m2);
    std_m.swap(std_m2);

    ft_m.swap(ft_m2);
    std_m.swap(std_m2);

    ft_m2.insert(ft::map<int, int>::value_type(-1, -1));
    ft_m2.insert(ft::map<int, int>::value_type(-2, -2));
    ft_m2.insert(ft::map<int, int>::value_type(-3, -3));
    ft_m2.insert(ft::map<int, int>::value_type(-4, -4));

    std_m2.insert(std::map<int, int>::value_type(-1, -1));
    std_m2.insert(std::map<int, int>::value_type(-2, -2));
    std_m2.insert(std::map<int, int>::value_type(-3, -3));
    std_m2.insert(std::map<int, int>::value_type(-4, -4));

    print_cont("std ", std_m);
    print_cont("std2", std_m2);

    print_cont("ft  ", ft_m);
    print_cont("ft2 ", ft_m2);

    std::cout << '\n';

    ft_m.swap(ft_m2);
    std_m.swap(std_m2);

    print_cont("std ", std_m);
    print_cont("std2", std_m2);

    print_cont("ft  ", ft_m);
    print_cont("ft2 ", ft_m2);

    std::cout << '\n';

    ft_m.swap(ft_m2);
    std_m.swap(std_m2);

    print_cont("std ", std_m);
    print_cont("std2", std_m2);

    print_cont("ft  ", ft_m);
    print_cont("ft2 ", ft_m2);
  }
  {
    SUBTITLE("map.swap(other)");

    std::map<int, int> std_m;
    ft::map<int, int>  ft_m;

    std::map<int, int> std_m2;
    ft::map<int, int>  ft_m2;

    ft_m.insert(ft::map<int, int>::value_type(1, 1));
    ft_m.insert(ft::map<int, int>::value_type(2, 2));
    ft_m.insert(ft::map<int, int>::value_type(3, 3));
    ft_m.insert(ft::map<int, int>::value_type(4, 4));

    ft_m2.insert(ft::map<int, int>::value_type(-1, -1));
    ft_m2.insert(ft::map<int, int>::value_type(-2, -2));
    ft_m2.insert(ft::map<int, int>::value_type(-3, -3));
    ft_m2.insert(ft::map<int, int>::value_type(-4, -4));

    std_m.insert(std::map<int, int>::value_type(1, 1));
    std_m.insert(std::map<int, int>::value_type(2, 2));
    std_m.insert(std::map<int, int>::value_type(3, 3));
    std_m.insert(std::map<int, int>::value_type(4, 4));

    std_m2.insert(std::map<int, int>::value_type(-1, -1));
    std_m2.insert(std::map<int, int>::value_type(-2, -2));
    std_m2.insert(std::map<int, int>::value_type(-3, -3));
    std_m2.insert(std::map<int, int>::value_type(-4, -4));

    print_cont("std ", std_m);
    print_cont("std2", std_m2);

    print_cont("ft  ", ft_m);
    print_cont("ft2 ", ft_m2);

    std::cout << '\n';

    ft::swap(ft_m, ft_m2);
    std::swap(std_m, std_m2);

    print_cont("std ", std_m);
    print_cont("std2", std_m2);

    print_cont("ft  ", ft_m);
    print_cont("ft2 ", ft_m2);

    std::cout << '\n';

    ft::swap(ft_m, ft_m2);
    std::swap(std_m, std_m2);

    print_cont("std ", std_m);
    print_cont("std2", std_m2);

    print_cont("ft  ", ft_m);
    print_cont("ft2 ", ft_m2);
  }
  {
    SUBTITLE("map.count(key)");
    std::map<int, int> std_m;
    ft::map<int, int>  ft_m;

    ft_m.insert(ft::map<int, int>::value_type(10, 10));
    ft_m.insert(ft::map<int, int>::value_type(20, 20));
    ft_m.insert(ft::map<int, int>::value_type(30, 30));
    ft_m.insert(ft::map<int, int>::value_type(40, 40));

    std_m.insert(std::map<int, int>::value_type(10, 10));
    std_m.insert(std::map<int, int>::value_type(20, 20));
    std_m.insert(std::map<int, int>::value_type(30, 30));
    std_m.insert(std::map<int, int>::value_type(40, 40));

    LABEL("std", "ft");
    ROW("count", std_m.count(20), ft_m.count(20));
    ROW("count", std_m.count(15), ft_m.count(15));
  }
  {
    SUBTITLE("map.find(key)");
    std::map<int, int> std_m;
    ft::map<int, int>  ft_m;

    ft_m.insert(ft::map<int, int>::value_type(10, 10));
    ft_m.insert(ft::map<int, int>::value_type(20, 20));
    ft_m.insert(ft::map<int, int>::value_type(30, 30));
    ft_m.insert(ft::map<int, int>::value_type(40, 40));

    std_m.insert(std::map<int, int>::value_type(10, 10));
    std_m.insert(std::map<int, int>::value_type(20, 20));
    std_m.insert(std::map<int, int>::value_type(30, 30));
    std_m.insert(std::map<int, int>::value_type(40, 40));

    LABEL("std", "ft");
    ROW("first", std_m.find(20)->first, ft_m.find(20)->first);
    ROW("second", std_m.find(20)->second, ft_m.find(20)->second);
    // ROW("first", std_m.find(15)->first, ft_m.find(15)->first);
    // ROW("second", std_m.find(15)->second, ft_m.find(15)->second);
  }
  {
    SUBTITLE("map.equal_range(key)");
    ft::map<int, int>  ft_v;
    std::map<int, int> std_v;

    std::map<int, int> std_1;

    std_1.insert(std::map<int, int>::value_type(2, 2));
    std_1.insert(std::map<int, int>::value_type(3, 3));
    std_1.insert(std::map<int, int>::value_type(-4, 4));
    std_1.insert(std::map<int, int>::value_type(-1, 1));
    std_1.insert(std::map<int, int>::value_type(2, 2));
    std_1.insert(std::map<int, int>::value_type(-3, 3));
    std_1.insert(std::map<int, int>::value_type(4, 4));
    std_1.insert(std::map<int, int>::value_type(5, 5));
    std_1.insert(std::map<int, int>::value_type(6, 6));

    // print_cont("std", std_v);
    // print_cont("ft ", ft_v);

    // std::map<int, int>::iterator stdi = std_v.equal_range(2).first;
    // ft::map<int, int>::iterator  fti = ft_v.equal_range(2).first;

    ft_v.insert(std_1.begin(), std_1.end());
    std_v.insert(std_1.begin(), std_1.end());

    print_cont("std", std_v);
    print_cont("ft ", ft_v);

    {
      std::map<int, int>::iterator stdi2 = std_v.equal_range(2).first;
      ft::map<int, int>::iterator  fti2  = ft_v.equal_range(2).first;
      std::map<int, int>::iterator stdi3 = std_v.equal_range(2).second;
      ft::map<int, int>::iterator  fti3  = ft_v.equal_range(2).second;

      LABEL("std", "ft");
      ROW("first", stdi2->first, fti2->first);
      ROW("second", stdi2->second, fti2->second);
      ROW("first", stdi3->first, fti3->first);
      ROW("second", stdi3->second, fti3->second);
    }
    {
      std::map<int, int>::iterator stdi4 = std_v.equal_range(5).first;
      ft::map<int, int>::iterator  fti4  = ft_v.equal_range(5).first;
      std::map<int, int>::iterator stdi5 = std_v.equal_range(5).second;
      ft::map<int, int>::iterator  fti5  = ft_v.equal_range(5).second;

      LABEL("std", "ft");
      ROW("first", stdi4->first, fti4->first);
      ROW("second", stdi4->second, fti4->second);
      ROW("first", stdi5->first, fti5->first);
      ROW("second", stdi5->second, fti5->second);
    }
    {
      std::map<int, int>::iterator stdi4 = std_v.equal_range(0).first;
      ft::map<int, int>::iterator  fti4  = ft_v.equal_range(0).first;
      std::map<int, int>::iterator stdi5 = std_v.equal_range(0).second;
      ft::map<int, int>::iterator  fti5  = ft_v.equal_range(0).second;

      LABEL("std", "ft");
      ROW("first", stdi4->first, fti4->first);
      ROW("second", stdi4->second, fti4->second);
      ROW("first", stdi5->first, fti5->first);
      ROW("second", stdi5->second, fti5->second);
    }
    {
      std::map<int, int>::iterator stdi4 = std_v.equal_range(-4).first;
      ft::map<int, int>::iterator  fti4  = ft_v.equal_range(-4).first;
      std::map<int, int>::iterator stdi5 = std_v.equal_range(-4).second;
      ft::map<int, int>::iterator  fti5  = ft_v.equal_range(-4).second;

      LABEL("std", "ft");
      ROW("first", stdi4->first, fti4->first);
      ROW("second", stdi4->second, fti4->second);
      ROW("first", stdi5->first, fti5->first);
      ROW("second", stdi5->second, fti5->second);
    }
    {
      std::map<int, int>::iterator stdi4 = std_v.equal_range(-5).first;
      ft::map<int, int>::iterator  fti4  = ft_v.equal_range(-5).first;
      std::map<int, int>::iterator stdi5 = std_v.equal_range(-5).second;
      ft::map<int, int>::iterator  fti5  = ft_v.equal_range(-5).second;

      LABEL("std", "ft");
      ROW("first", stdi4->first, fti4->first);
      ROW("second", stdi4->second, fti4->second);
      ROW("first", stdi5->first, fti5->first);
      ROW("second", stdi5->second, fti5->second);
    }
  }

  {
    SUBTITLE("map.upper_bound(key)");
    std::map<int, int> std_m;
    ft::map<int, int>  ft_m;

    ft_m.insert(ft::map<int, int>::value_type(-1, -1));
    ft_m.insert(ft::map<int, int>::value_type(5, 5));
    ft_m.insert(ft::map<int, int>::value_type(10, 10));
    ft_m.insert(ft::map<int, int>::value_type(12, 12));
    ft_m.insert(ft::map<int, int>::value_type(20, 20));
    ft_m.insert(ft::map<int, int>::value_type(27, 27));
    ft_m.insert(ft::map<int, int>::value_type(30, 30));
    ft_m.insert(ft::map<int, int>::value_type(40, 40));

    std_m.insert(std::map<int, int>::value_type(-1, -1));
    std_m.insert(std::map<int, int>::value_type(5, 5));
    std_m.insert(std::map<int, int>::value_type(10, 10));
    std_m.insert(std::map<int, int>::value_type(12, 12));
    std_m.insert(std::map<int, int>::value_type(20, 20));
    std_m.insert(std::map<int, int>::value_type(27, 27));
    std_m.insert(std::map<int, int>::value_type(30, 30));
    std_m.insert(std::map<int, int>::value_type(40, 40));

    LABEL("std", "ft");

    for (int i = -10; i < 40; i++) {
      ROW("first", std_m.upper_bound(i)->first, ft_m.upper_bound(i)->first);
      ROW("second", std_m.upper_bound(i)->second, ft_m.upper_bound(i)->second);
    }
  }
  {
    SUBTITLE("map.lower_bound(key)");
    std::map<int, int> std_m;
    ft::map<int, int>  ft_m;

    ft_m.insert(ft::map<int, int>::value_type(-1, -1));
    ft_m.insert(ft::map<int, int>::value_type(5, 5));
    ft_m.insert(ft::map<int, int>::value_type(10, 10));
    ft_m.insert(ft::map<int, int>::value_type(12, 12));
    ft_m.insert(ft::map<int, int>::value_type(20, 20));
    ft_m.insert(ft::map<int, int>::value_type(27, 27));
    ft_m.insert(ft::map<int, int>::value_type(30, 30));
    ft_m.insert(ft::map<int, int>::value_type(40, 40));

    std_m.insert(std::map<int, int>::value_type(-1, -1));
    std_m.insert(std::map<int, int>::value_type(5, 5));
    std_m.insert(std::map<int, int>::value_type(10, 10));
    std_m.insert(std::map<int, int>::value_type(12, 12));
    std_m.insert(std::map<int, int>::value_type(20, 20));
    std_m.insert(std::map<int, int>::value_type(27, 27));
    std_m.insert(std::map<int, int>::value_type(30, 30));
    std_m.insert(std::map<int, int>::value_type(40, 40));

    LABEL("std", "ft");

    for (int i = -10; i < 40; i++) {
      ROW("first", std_m.lower_bound(i)->first, ft_m.lower_bound(i)->first);
      ROW("second", std_m.lower_bound(i)->second, ft_m.lower_bound(i)->second);
    }
  }
  {
    SUBTITLE("operator==(eq)");
    {
      std::map<int, int> std_v;
      ft::map<int, int>  ft_v;

      std_v.insert(std::map<int, int>::value_type(1, 1));
      std_v.insert(std::map<int, int>::value_type(2, 2));
      std_v.insert(std::map<int, int>::value_type(3, 3));
      ft_v.insert(ft::map<int, int>::value_type(1, 1));
      ft_v.insert(ft::map<int, int>::value_type(2, 2));
      ft_v.insert(ft::map<int, int>::value_type(3, 3));

      std::map<int, int> std_v2(std_v);
      ft::map<int, int>  ft_v2(ft_v);

      LABEL("std", "ft");
      ROW("equal", (std_v == std_v2), (ft_v == ft_v2));
      std_v.erase(1);
      ft_v.erase(1);
      ROW("equal", (std_v == std_v2), (ft_v == ft_v2));
      std_v2.erase(1);
      ft_v2.erase(1);
      ROW("equal", (std_v == std_v2), (ft_v == ft_v2));
    }

    {
      std::map<std::string, std::string> std_v;
      ft::map<std::string, std::string>  ft_v;

      std_v.insert(std::map<std::string, std::string>::value_type("apple", "apple"));
      std_v.insert(std::map<std::string, std::string>::value_type("2", "2"));
      std_v.insert(std::map<std::string, std::string>::value_type("3", "3"));
      ft_v.insert(ft::map<std::string, std::string>::value_type("apple", "apple"));
      ft_v.insert(ft::map<std::string, std::string>::value_type("2", "2"));
      ft_v.insert(ft::map<std::string, std::string>::value_type("3", "3"));

      std::map<std::string, std::string> std_v2(std_v);
      ft::map<std::string, std::string>  ft_v2(ft_v);

      LABEL("std", "ft");
      ROW("equal", (std_v == std_v2), (ft_v == ft_v2));
      std_v.erase("apple");
      ft_v.erase("apple");
      ROW("equal", (std_v == std_v2), (ft_v == ft_v2));
      std_v2.erase("apple");
      ft_v2.erase("apple");
      ROW("equal", (std_v == std_v2), (ft_v == ft_v2));
    }
  }
  {
    SUBTITLE("operator!=(nq)");

    std::map<int, int> std_v;
    ft::map<int, int>  ft_v;

    std_v.insert(std::map<int, int>::value_type(1, 1));
    std_v.insert(std::map<int, int>::value_type(2, 2));
    std_v.insert(std::map<int, int>::value_type(3, 3));
    ft_v.insert(ft::map<int, int>::value_type(1, 1));
    ft_v.insert(ft::map<int, int>::value_type(2, 2));
    ft_v.insert(ft::map<int, int>::value_type(3, 3));

    std::map<int, int> std_v2(std_v);
    ft::map<int, int>  ft_v2(ft_v);

    LABEL("std", "ft");
    ROW("not equal", (std_v != std_v2), (ft_v != ft_v2));
    std_v.erase(1);
    ft_v.erase(1);
    ROW("not equal", (std_v != std_v2), (ft_v != ft_v2));

    {
      std::map<std::string, std::string> std_v;
      ft::map<std::string, std::string>  ft_v;

      std_v.insert(std::map<std::string, std::string>::value_type("apple", "apple"));
      std_v.insert(std::map<std::string, std::string>::value_type("2", "2"));
      std_v.insert(std::map<std::string, std::string>::value_type("3", "3"));
      ft_v.insert(ft::map<std::string, std::string>::value_type("apple", "apple"));
      ft_v.insert(ft::map<std::string, std::string>::value_type("2", "2"));
      ft_v.insert(ft::map<std::string, std::string>::value_type("3", "3"));

      std::map<std::string, std::string> std_v2(std_v);
      ft::map<std::string, std::string>  ft_v2(ft_v);

      LABEL("std", "ft");
      ROW("equal", (std_v != std_v2), (ft_v != ft_v2));
      std_v.erase("apple");
      ft_v.erase("apple");
      ROW("equal", (std_v != std_v2), (ft_v != ft_v2));
      std_v2.erase("apple");
      ft_v2.erase("apple");
      ROW("equal", (std_v != std_v2), (ft_v != ft_v2));
    }
  }
  {
    SUBTITLE("operator<(l)");
    std::map<int, int> std_v;
    ft::map<int, int>  ft_v;
    std::map<int, int> std_v2;
    ft::map<int, int>  ft_v2;

    LABEL("std", "ft");
    ROW("less", (std_v < std_v2), (ft_v < ft_v2));

    ft_v2.insert(ft::map<int, int>::value_type(1, 1));
    std_v2.insert(std::map<int, int>::value_type(1, 1));

    ROW("less", (std_v < std_v2), (ft_v < ft_v2));

    ft_v.insert(ft::map<int, int>::value_type(2, 2));
    std_v.insert(std::map<int, int>::value_type(2, 2));

    ROW("less", (std_v < std_v2), (ft_v < ft_v2));

    ft_v2.insert(ft::map<int, int>::value_type(3, 3));
    std_v2.insert(std::map<int, int>::value_type(3, 3));

    ROW("less", (std_v < std_v2), (ft_v < ft_v2));
  }
  {
    SUBTITLE("operator<=(le)");
    std::map<int, int> std_v;
    ft::map<int, int>  ft_v;
    std::map<int, int> std_v2;
    ft::map<int, int>  ft_v2;

    LABEL("std", "ft");
    ROW("less equal", (std_v <= std_v2), (ft_v <= ft_v2));

    ft_v2.insert(ft::map<int, int>::value_type(1, 1));
    std_v2.insert(std::map<int, int>::value_type(1, 1));

    ROW("less equal", (std_v <= std_v2), (ft_v <= ft_v2));

    ft_v.insert(ft::map<int, int>::value_type(2, 2));
    std_v.insert(std::map<int, int>::value_type(2, 2));

    ROW("less equal", (std_v <= std_v2), (ft_v <= ft_v2));

    ft_v2.insert(ft::map<int, int>::value_type(3, 3));
    std_v2.insert(std::map<int, int>::value_type(3, 3));

    ROW("less equal", (std_v <= std_v2), (ft_v <= ft_v2));
  }
  {
    SUBTITLE("operator>(g)");
    std::map<int, int> std_v;
    ft::map<int, int>  ft_v;
    std::map<int, int> std_v2;
    ft::map<int, int>  ft_v2;

    LABEL("std", "ft");
    ROW("grater", (std_v > std_v2), (ft_v > ft_v2));

    ft_v2.insert(ft::map<int, int>::value_type(1, 1));
    std_v2.insert(std::map<int, int>::value_type(1, 1));

    ROW("grater", (std_v > std_v2), (ft_v > ft_v2));

    ft_v.insert(ft::map<int, int>::value_type(2, 2));
    std_v.insert(std::map<int, int>::value_type(2, 2));

    ROW("grater", (std_v > std_v2), (ft_v > ft_v2));

    ft_v2.insert(ft::map<int, int>::value_type(3, 3));
    std_v2.insert(std::map<int, int>::value_type(3, 3));

    ROW("grater", (std_v > std_v2), (ft_v > ft_v2));
  }
  {
    SUBTITLE("operator>=(ge)");
    std::map<int, int> std_v;
    ft::map<int, int>  ft_v;
    std::map<int, int> std_v2;
    ft::map<int, int>  ft_v2;

    LABEL("std", "ft");
    ROW("grater equal", (std_v >= std_v2), (ft_v >= ft_v2));

    ft_v2.insert(ft::map<int, int>::value_type(1, 1));
    std_v2.insert(std::map<int, int>::value_type(1, 1));

    ROW("grater equal", (std_v >= std_v2), (ft_v >= ft_v2));

    ft_v.insert(ft::map<int, int>::value_type(2, 2));
    std_v.insert(std::map<int, int>::value_type(2, 2));

    ROW("grater equal", (std_v >= std_v2), (ft_v >= ft_v2));

    ft_v2.insert(ft::map<int, int>::value_type(3, 3));
    std_v2.insert(std::map<int, int>::value_type(3, 3));

    ROW("grater equal", (std_v >= std_v2), (ft_v >= ft_v2));
  }
}