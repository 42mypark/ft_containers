#include "../system/system_methods.ipp"
#include "__service.ipp"

template <class T, class V>
std::vector<int> lower_bound_test(std::map<T, V> mp) {
  std::vector<int>                       v;
  std::map<int, int, std::greater<int> > mp2;
  int                                    _ratio = 1;
  mp.insert(std::make_pair(10, 10));
  mp2.insert(std::make_pair(10, 10));
  if (mp.lower_bound(11) == mp.end())
    v.push_back(1);
  if (mp2.lower_bound(1) == mp2.end())
    v.push_back(1);
  mp.insert(std::make_pair(20, 20));
  mp.insert(std::make_pair(30, 30));
  mp.insert(std::make_pair(40, 40));
  mp.insert(std::make_pair(50, 50));
  mp.insert(std::make_pair(60, 60));
  mp2.insert(std::make_pair(20, 20));
  mp2.insert(std::make_pair(30, 30));
  mp2.insert(std::make_pair(40, 40));
  mp2.insert(std::make_pair(50, 50));
  mp2.insert(std::make_pair(60, 60));
  std::map<int, int>::iterator it;
  for (int i = 10; i < 60; i += 1) {
    it = mp.lower_bound(i);
    v.push_back(it->first);
  }
  for (int i = 10; i < 60; i += 1) {
    it = mp2.lower_bound(i);
    v.push_back(it->first);
  }
  std::map<int, int> mp3;
  for (int i = 0, j = 0; i < 50 * _ratio; ++i, ++j) {
    mp3.insert(std::make_pair(i, j));
  }
  g_start1 = timer();
  mp3.lower_bound(49 * _ratio);
  g_end1 = timer();
  return v;
}

template <class T, class V>
std::vector<int> lower_bound_test(_map<T, V> mp) {
  std::vector<int>                   v;
  _map<int, int, std::greater<int> > mp2;
  int                                _ratio = 1;

  mp.insert(_make_pair(10, 10));
  mp2.insert(_make_pair(10, 10));
  if (mp.lower_bound(11) == mp.end())
    v.push_back(1);
  if (mp2.lower_bound(1) == mp2.end())
    v.push_back(1);
  mp.insert(_make_pair(20, 20));
  mp.insert(_make_pair(30, 30));
  mp.insert(_make_pair(40, 40));
  mp.insert(_make_pair(50, 50));
  mp.insert(_make_pair(60, 60));
  mp2.insert(_make_pair(20, 20));
  mp2.insert(_make_pair(30, 30));
  mp2.insert(_make_pair(40, 40));
  mp2.insert(_make_pair(50, 50));
  mp2.insert(_make_pair(60, 60));
  _map<int, int>::iterator it;
  for (int i = 10; i < 60; i += 1) {
    it = mp.lower_bound(i);
    v.push_back(it->first);
  }
  for (int i = 10; i < 60; i += 1) {
    it = mp2.lower_bound(i);
    v.push_back(it->first);
  }
  _map<int, int> mp3;
  for (int i = 0, j = 0; i < 50 * _ratio; ++i, ++j) {
    mp3.insert(_make_pair(i, j));
  }
  g_start2 = timer();
  mp3.lower_bound(49 * _ratio);
  g_end2 = timer();
  return v;
}

int main() { exit(run_map_unit_test<int, int>("lower_bound()", lower_bound_test, lower_bound_test)); }