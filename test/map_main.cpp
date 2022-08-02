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
  TITLE("rbtree_iterator");
  {
    SUBTITLE("iterator");
    ft::map<int, int>  ft_m;
    std::map<int, int> std_m;
    ft_m.insert(ft::make_pair(1, -1));
    ft_m.insert(ft::make_pair(1, 2));

    std_m.insert(std::make_pair(1, -1));
    std_m.insert(std::make_pair(1, 2));

    ft_m.insert(ft::make_pair(2, 2));
    ft_m.insert(ft::make_pair(3, 3));
    ft_m.insert(ft::make_pair(4, 4));

    std_m.insert(std::make_pair(2, 2));
    std_m.insert(std::make_pair(3, 3));
    std_m.insert(std::make_pair(4, 4));

    std::map<int, int>::iterator it_std = std_m.begin();
    for (; it_std != std_m.end(); ++it_std) {
      std::cout << it_std->first << ", " << it_std->second << std::endl;
    }

    std::cout << '\n';

    ft::map<int, int>::iterator it = ft_m.begin();
    for (; it != ft_m.end(); ++it) {
      std::cout << it->first << ", " << it->second << std::endl;
    }

    std::cout << '\n';

    std::map<int, int>::iterator it_std2 = std_m.end();
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

    std::map<int, int>::reverse_iterator it_std_r = std_m.rbegin();
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
    ft::map<int, int>  ft_m;
    std::map<int, int> std_m;
    ft_m.insert(ft::make_pair(1, -1));
    ft_m.insert(ft::make_pair(1, 2));

    std_m.insert(std::make_pair(1, -1));
    std_m.insert(std::make_pair(1, 2));

    ft_m.insert(ft::make_pair(2, 2));
    ft_m.insert(ft::make_pair(3, 3));
    ft_m.insert(ft::make_pair(4, 4));

    std_m.insert(std::make_pair(2, 2));
    std_m.insert(std::make_pair(3, 3));
    std_m.insert(std::make_pair(4, 4));

    std::map<int, int>::const_iterator it_std = std_m.begin();
    for (; it_std != std_m.end(); ++it_std) {
      std::cout << it_std->first << ", " << it_std->second << std::endl;
    }

    std::cout << '\n';

    ft::map<int, int>::const_iterator it = ft_m.begin();
    for (; it != ft_m.end(); ++it) {
      std::cout << it->first << ", " << it->second << std::endl;
    }

    std::cout << '\n';

    std::map<int, int>::const_iterator it_std2 = std_m.end();
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

    std::map<int, int>::const_reverse_iterator it_std_r = std_m.rbegin();
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

    ft_m = fm;
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
    print_cont("std", std_m);
    print_cont("ft ", ft_m);
  }

  { SUBTITLE("map.max_size()"); }

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

    ft_m.insert(ft::map<int, int>::value_type(1, 1));
    ft_m.insert(ft::map<int, int>::value_type(2, 2));
    ft_m.insert(ft::map<int, int>::value_type(3, 3));
    ft_m.insert(ft::map<int, int>::value_type(4, 4));

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

  { SUBTITLE("map.erase(pos)"); }
  { SUBTITLE("map.erase(iter)"); }
  { SUBTITLE("map.erase(key)"); }

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
    ROW("first", std_m.find(15)->first, ft_m.find(15)->first);
    ROW("second", std_m.find(15)->second, ft_m.find(15)->second);
  }

  { SUBTITLE("map.equal_range(key)"); }

  {
    SUBTITLE("map.upper_bound(key)");
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

    ROW("first", std_m.upper_bound(40)->first, ft_m.upper_bound(40)->first);
    ROW("second", std_m.upper_bound(40)->second, ft_m.upper_bound(40)->second);

    ROW("first", std_m.upper_bound(41)->first, ft_m.upper_bound(41)->first);
    ROW("second", std_m.upper_bound(41)->second, ft_m.upper_bound(41)->second);
  }
  {
    SUBTITLE("map.lower_bound(key)");
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

    ROW("first", std_m.lower_bound(41)->first, ft_m.lower_bound(41)->first);
    ROW("second", std_m.lower_bound(41)->second, ft_m.lower_bound(41)->second);
  }
  {
    SUBTITLE("operator==(eq)");

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