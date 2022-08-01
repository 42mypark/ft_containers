#include <iostream>
#include <memory>

#include "macro.hpp"
#include "map.hpp"
#include "rbtree.hpp"

int main() {
  TITLE("rbtree");
  ft::rbtree<int, ft::pair<int, int>, std::less<int>, std::allocator<ft::pair<int, int> >,
             ft::map<int, int>::extractor>
      tree;
  tree.insert(ft::make_pair(1, 1));
  tree.insert(ft::make_pair(2, 2));
  tree.insert(ft::make_pair(-1, -1));
  tree.insert(ft::make_pair(-2, -2));
  tree.remove(-2);
  std::cout << tree.error() << std::endl;
  tree.remove(-2);
  std::cout << tree.error() << std::endl;
  std::cout << tree.search_value(2).first << std::endl;
}