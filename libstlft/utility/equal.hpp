#ifndef equal_HPP
#define equal_HPP

#include "enable_if.hpp"
#include "is_integral.hpp"

namespace ft {
template <class InputIt1, class InputIt2>
bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2,
           typename enable_if<!is_integral<InputIt1>::value>::type* = 0,
           typename enable_if<!is_integral<InputIt2>::value>::type* = 0) /*1*/ {
  for (; first1 != last1; ++first1, ++first2) {
    if (!(*first1 == *first2)) {
      return false;
    }
  }
  return true;
}

template <class InputIt1, class InputIt2, class BinaryPredicate>
bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2, BinaryPredicate p,
           typename enable_if<!is_integral<InputIt1>::value>::type* = 0,
           typename enable_if<!is_integral<InputIt2>::value>::type* = 0) /*3*/ {
  for (; first1 != last1; ++first1, ++first2) {
    if (!p(*first1, *first2)) {
      return false;
    }
  }
  return true;
}

}  // namespace ft

#endif  // equal_HPP
