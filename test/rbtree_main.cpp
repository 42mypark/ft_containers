#include <iostream>
#include <memory>

#include "rbtree.hpp"

int main() {
  ft::rbtree<int, ft::pair<int, int>, std::less<int>, std::allocator<ft::pair<int, int> > > tree;
  std::cout << "hey" << std::endl;
  tree.insert(ft::make_pair(1, 1));
  tree.insert(ft::make_pair(2, 2));
  tree.insert(ft::make_pair(-1, -1));
  tree.insert(ft::make_pair(-2, -2));
  tree.search(-2)->printNode();
  tree.search(-1)->printNode();
  tree.search(1)->printNode();
  tree.search(2)->printNode();
  tree.search(0)->printNode();
  tree.remove(-2);
  tree.search(-2)->printNode();
}