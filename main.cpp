#include <map>
#include <vector>

#include "map.hpp"
#include "vector.hpp"

int main() {
  ft::vector<int> v;

  v.push_back(1);
  // v.insert(ft::make_pair(1, 1));

  ft::vector<int>::iterator it = v.begin();

  // ft::vector<nt>::const_iterator cit = it;
  ft::vector<int>::const_iterator cit2 = v.begin();

  // *cit2 = ft::make_pair(2, 2);
  // *cit2 = 2;
  cit2 = ++it;
  // it = cit2;

  ft::vector<int>::iterator it3 = v.begin();

  // it = cit3;
}
