#ifndef lexicographical_compare_HPP
#define lexicographical_compare_HPP

namespace ft {

template <typename T>
struct Grater {
  bool operator()(const T& o1, const T& o2) { return o1 > o2; }
};

template <typename T>
struct GraterEqual {
  bool operator()(const T& o1, const T& o2) { return o1 >= o2; }
};

template <typename T>
struct LessEqual {
  bool operator()(const T& o1, const T& o2) { return o1 <= o2; }
};

template <class InputIt1, class InputIt2>
bool lexicographical_compare(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2) {
  for (; first1 != last1 && first2 != last2; ++first1, ++first2) {
    if (*first1 < *first2)
      return true;
    if (*first2 < *first1)
      return false;
  }
  return (first1 == last1) && (first2 != last2);
}

template <class InputIt1, class InputIt2, class Compare>
bool lexicographical_compare(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2,
                             Compare comp) {
  for (; first2 != last2; ++first1, ++first2) {
    if (first1 == last1 || comp(*first1, *first2))
      return true;
    if (comp(*first2, *first1))
      return false;
  }
  return false;
}

}  // namespace ft

#endif  // lexicographical_compare_HPP