#include <iostream>
#include <iterator>
#include <map>

#include "iterator_traits.hpp"
#include "macro.hpp"

int main() {
  TITLE("iterator_traits");
  SUBTITLE("iterator");
  ROW("category", typeid(std::iterator_traits<std::map<int, int>::iterator>::iterator_category).name(),
      typeid(ft::iterator_traits<std::map<int, int>::iterator>::iterator_category).name());
  ROW("value_type", typeid(std::iterator_traits<std::map<int, int>::iterator>::value_type).name(),
      typeid(ft::iterator_traits<std::map<int, int>::iterator>::value_type).name());
  ROW("difference_type", typeid(std::iterator_traits<std::map<int, int>::iterator>::difference_type).name(),
      typeid(ft::iterator_traits<std::map<int, int>::iterator>::difference_type).name());
  ROW("pointer", typeid(std::iterator_traits<std::map<int, int>::iterator>::pointer).name(),
      typeid(ft::iterator_traits<std::map<int, int>::iterator>::pointer).name());
  ROW("reference", typeid(std::iterator_traits<std::map<int, int>::iterator>::reference).name(),
      typeid(ft::iterator_traits<std::map<int, int>::iterator>::reference).name());
  SUBTITLE("reverse_iterator");
  ROW("category", typeid(std::iterator_traits<std::map<int, int>::reverse_iterator>::iterator_category).name(),
      typeid(ft::iterator_traits<std::map<int, int>::reverse_iterator>::iterator_category).name());
  ROW("value_type", typeid(std::iterator_traits<std::map<int, int>::reverse_iterator>::value_type).name(),
      typeid(ft::iterator_traits<std::map<int, int>::reverse_iterator>::value_type).name());
  ROW("difference_type", typeid(std::iterator_traits<std::map<int, int>::reverse_iterator>::difference_type).name(),
      typeid(ft::iterator_traits<std::map<int, int>::reverse_iterator>::difference_type).name());
  ROW("pointer", typeid(std::iterator_traits<std::map<int, int>::reverse_iterator>::pointer).name(),
      typeid(ft::iterator_traits<std::map<int, int>::reverse_iterator>::pointer).name());
  ROW("reference", typeid(std::iterator_traits<std::map<int, int>::reverse_iterator>::reference).name(),
      typeid(ft::iterator_traits<std::map<int, int>::reverse_iterator>::reference).name());
}