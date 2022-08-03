#ifndef is_integral_HPP
#define is_integral_HPP

#include <type_traits>

#include "integral_constant.hpp"
#include "remove_cv.hpp"

namespace ft {

typedef integral_constant<bool, true>  true_type;
typedef integral_constant<bool, false> false_type;

template <typename T>
struct is_integral_helper : public false_type {};

template <>
struct is_integral_helper<bool> : public true_type {};

template <>
struct is_integral_helper<char> : public true_type {};

template <>
struct is_integral_helper<signed char> : public true_type {};

template <>
struct is_integral_helper<unsigned char> : public true_type {};

template <>
struct is_integral_helper<char16_t> : public true_type {};

template <>
struct is_integral_helper<char32_t> : public true_type {};

template <>
struct is_integral_helper<short> : public true_type {};

template <>
struct is_integral_helper<unsigned short> : public true_type {};

template <>
struct is_integral_helper<int> : public true_type {};

template <>
struct is_integral_helper<unsigned int> : public true_type {};

template <>
struct is_integral_helper<long> : public true_type {};

template <>
struct is_integral_helper<unsigned long> : public true_type {};

template <>
struct is_integral_helper<unsigned long long> : public true_type {};

template <>
struct is_integral_helper<long long> : public true_type {};

template <>
struct is_integral_helper<wchar_t> : public true_type {};

template <typename T>
struct is_integral : public is_integral_helper<typename remove_cv<T>::type>::type {};

template <typename T>
bool operator==(const is_integral<T>&, const std::is_integral<T>&) {
  return is_integral<T>::value == std::is_integral<T>::value;
}

template <typename T>
bool operator==(const std::is_integral<T>&, const is_integral<T>&) {
  return is_integral<T>::value == std::is_integral<T>::value;
}

}  // namespace ft

#endif