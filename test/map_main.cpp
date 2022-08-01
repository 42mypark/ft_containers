#include <map>

#include "macro.hpp"
#include "map.hpp"

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

  TITLE("map");
  {}
}