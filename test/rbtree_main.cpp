#include <iostream>
#include <memory>

#include "map.hpp"
#include "rbtree.hpp"

int main() {
  ft::rbtree<int, ft::pair<int, int>, std::less<int>, std::allocator<ft::pair<int, int> >,
             ft::map<int, int>::extractor>
      tree;
  std::cout << "hey" << std::endl;
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