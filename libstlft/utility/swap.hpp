#ifndef swap_HPP
#define swap_HPP

namespace ft {
template <typename T>
void swap(T& a, T& b) {
  T tmp;
  tmp = a;
  a = b;
  b = tmp;
}

}  // namespace ft

#endif  // swap_HPP