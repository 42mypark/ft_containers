#include "../system/system_methods.ipp"
#include UTILITIES
#include MAP

bool iterator_traits_test() {
  std::vector<string> res;
  std::vector<string> res2;
  g_start1 = g_end1 = timer();

  res.push_back(typeid(std::iterator_traits<std::map<int, int>::iterator>::iterator_category).name());
  res.push_back(typeid(std::iterator_traits<std::map<int, int>::iterator>::value_type).name());
  res.push_back(typeid(std::iterator_traits<std::map<int, int>::iterator>::difference_type).name());
  res.push_back(typeid(std::iterator_traits<std::map<int, int>::iterator>::pointer).name());
  res.push_back(typeid(std::iterator_traits<std::map<int, int>::iterator>::reference).name());
  res.push_back(typeid(std::iterator_traits<std::map<int, int>::reverse_iterator>::iterator_category).name());
  res.push_back(typeid(std::iterator_traits<std::map<int, int>::reverse_iterator>::value_type).name());
  res.push_back(typeid(std::iterator_traits<std::map<int, int>::reverse_iterator>::difference_type).name());
  res.push_back(typeid(std::iterator_traits<std::map<int, int>::reverse_iterator>::pointer).name());
  res.push_back(typeid(std::iterator_traits<std::map<int, int>::reverse_iterator>::reference).name());

  res2.push_back(typeid(ft::iterator_traits<std::map<int, int>::iterator>::iterator_category).name());
  res2.push_back(typeid(ft::iterator_traits<std::map<int, int>::iterator>::value_type).name());
  res2.push_back(typeid(ft::iterator_traits<std::map<int, int>::iterator>::difference_type).name());
  res2.push_back(typeid(ft::iterator_traits<std::map<int, int>::iterator>::pointer).name());
  res2.push_back(typeid(ft::iterator_traits<std::map<int, int>::iterator>::reference).name());
  res2.push_back(typeid(ft::iterator_traits<std::map<int, int>::reverse_iterator>::iterator_category).name());
  res2.push_back(typeid(ft::iterator_traits<std::map<int, int>::reverse_iterator>::value_type).name());
  res2.push_back(typeid(ft::iterator_traits<std::map<int, int>::reverse_iterator>::difference_type).name());
  res2.push_back(typeid(ft::iterator_traits<std::map<int, int>::reverse_iterator>::pointer).name());
  res2.push_back(typeid(ft::iterator_traits<std::map<int, int>::reverse_iterator>::reference).name());

  return res == res2;
}

int main() { exit(run_bool_unit_test("iterators_traits", iterator_traits_test)); }
