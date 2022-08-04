#ifndef integral_constant_HPP
#define integral_constant_HPP

namespace ft {
template <typename T, T v>
struct integral_constant {
  static const T                  value = v;
  typedef T                       value_type;
  typedef integral_constant<T, v> type;
};
}  // namespace ft

#endif  // integral_constant_HPP
