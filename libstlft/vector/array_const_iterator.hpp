#ifndef array_const_iterator_HPP
#define array_const_iterator_HPP

#include <iterator>

#include "enable_if.hpp"
#include "is_integral.hpp"
#include "iterator_traits.hpp"

namespace ft {

template <typename Pointer>
class array_iterator;

template <typename Pointer>
class array_const_iterator {
  // Types
 public:
  typedef Pointer                                              pointer_type;
  typedef typename iterator_traits<Pointer>::iterator_category iterator_category;
  typedef typename iterator_traits<Pointer>::value_type        value_type;
  typedef typename iterator_traits<Pointer>::difference_type   difference_type;
  typedef typename iterator_traits<Pointer>::pointer           pointer;
  typedef typename iterator_traits<Pointer>::reference         reference;

  // Member Variable
 protected:
  pointer current_;

  // Destructor
 public:
  ~array_const_iterator() {}

  // Constructor
 public:
  array_const_iterator() {}
  explicit array_const_iterator(pointer_type it) : current_(it) {}
  template <typename U>
  array_const_iterator(array_const_iterator<U>& other) : current_(other.base()) {}
  template <typename U>
  array_const_iterator(array_iterator<U> other) : current_(other.base()) {}

  // Interface
 public:
  pointer base() const { return current_; }

  // Member operator
  template <typename U>
  array_const_iterator& operator=(array_const_iterator<U>& other);
  // template <typename U>
  // array_const_iterator& operator=(array_iterator<U>& other);
  array_const_iterator& operator=(pointer p);
  reference             operator*() const;
  pointer               operator->() const;
  reference             operator[](difference_type n) const;
  array_const_iterator& operator++();
  array_const_iterator  operator++(int);
  array_const_iterator& operator--();
  array_const_iterator  operator--(int);
  array_const_iterator  operator+(difference_type n) const;
  array_const_iterator  operator-(difference_type n) const;
  array_const_iterator& operator+=(difference_type n);
  array_const_iterator& operator-=(difference_type n);

  // Static Functions
 private:
  template <typename T>
  static T* to_pointer(T* p);
  template <typename T>
  static pointer to_pointer(T t);

};  // class array_const_iterator

// Member Operator

template <typename Pointer>
template <typename U>
array_const_iterator<Pointer>& array_const_iterator<Pointer>::operator=(array_const_iterator<U>& other) {
  current_ = other.base();
  return (*this);
}

// template <typename Pointer>
// template <typename U>
// array_const_iterator<Pointer>& array_const_iterator<Pointer>::operator=(array_iterator<U>& other) {
//   current_ = other.base();
//   return (*this);
// }

template <typename Pointer>
array_const_iterator<Pointer>& array_const_iterator<Pointer>::operator=(pointer p) {
  current_ = p;
  return (*this);
}

template <typename Pointer>
typename array_const_iterator<Pointer>::reference array_const_iterator<Pointer>::operator*() const {
  return *current_;
}

template <typename Pointer>
typename array_const_iterator<Pointer>::pointer array_const_iterator<Pointer>::operator->() const {
  return to_pointer(current_);
}
template <typename Pointer>
typename array_const_iterator<Pointer>::reference array_const_iterator<Pointer>::operator[](difference_type n) const {
  return *(*this + n);
}

template <typename Pointer>
array_const_iterator<Pointer>& array_const_iterator<Pointer>::operator++() {
  ++current_;
  return *this;
}

template <typename Pointer>
array_const_iterator<Pointer> array_const_iterator<Pointer>::operator++(int) {
  array_const_iterator tmp = *this;
  ++current_;
  return tmp;
}

template <typename Pointer>
array_const_iterator<Pointer>& array_const_iterator<Pointer>::operator--() {
  --current_;
  return *this;
}

template <typename Pointer>
array_const_iterator<Pointer> array_const_iterator<Pointer>::operator--(int) {
  array_const_iterator tmp = *this;
  --current_;
  return tmp;
}

template <typename Pointer>
array_const_iterator<Pointer> array_const_iterator<Pointer>::operator+(difference_type n) const {
  return array_const_iterator(current_ + n);
}

template <typename Pointer>
array_const_iterator<Pointer> array_const_iterator<Pointer>::operator-(difference_type n) const {
  return array_const_iterator(current_ - n);
}

template <typename Pointer>
array_const_iterator<Pointer>& array_const_iterator<Pointer>::operator+=(difference_type n) {
  current_ += n;
  return *this;
}

template <typename Pointer>
array_const_iterator<Pointer>& array_const_iterator<Pointer>::operator-=(difference_type n) {
  current_ -= n;
  return *this;
}

// Static Functions
template <typename Pointer>
template <typename T>
T* array_const_iterator<Pointer>::to_pointer(T* p) {
  return p;
}

template <typename Pointer>
template <typename T>
typename array_const_iterator<Pointer>::pointer array_const_iterator<Pointer>::to_pointer(T t) {
  return t.operator->();
}

// Non-member operators

template <typename Iter1, typename Iter2>
bool operator==(const array_const_iterator<Iter1>& lhs, const array_const_iterator<Iter2>& rhs) {
  return lhs.base() == rhs.base();
}

template <typename Iter1, typename Iter2>
bool operator==(const array_const_iterator<Iter1>& lhs, const array_iterator<Iter2>& rhs) {
  return lhs.base() == rhs.base();
}

template <typename Iter1, typename Iter2>
bool operator==(const array_iterator<Iter1>& lhs, const array_const_iterator<Iter2>& rhs) {
  return lhs.base() == rhs.base();
}

template <typename Iter1, typename Iter2>
bool operator!=(const array_const_iterator<Iter1>& lhs, const array_const_iterator<Iter2>& rhs) {
  return lhs.base() != rhs.base();
}

template <typename Iter1, typename Iter2>
bool operator!=(const array_iterator<Iter1>& lhs, const array_const_iterator<Iter2>& rhs) {
  return lhs.base() != rhs.base();
}

template <typename Iter1, typename Iter2>
bool operator!=(const array_const_iterator<Iter1>& lhs, const array_iterator<Iter2>& rhs) {
  return lhs.base() != rhs.base();
}

template <typename Iter1, typename Iter2>
bool operator>(const array_const_iterator<Iter1>& lhs, const array_const_iterator<Iter2>& rhs) {
  return lhs.base() > rhs.base();
}

template <typename Iter1, typename Iter2>
bool operator>(const array_iterator<Iter1>& lhs, const array_const_iterator<Iter2>& rhs) {
  return lhs.base() > rhs.base();
}

template <typename Iter1, typename Iter2>
bool operator>(const array_const_iterator<Iter1>& lhs, const array_iterator<Iter2>& rhs) {
  return lhs.base() > rhs.base();
}

template <typename Iter1, typename Iter2>
bool operator>=(const array_const_iterator<Iter1>& lhs, const array_const_iterator<Iter2>& rhs) {
  return lhs.base() >= rhs.base();
}
template <typename Iter1, typename Iter2>
bool operator>=(const array_iterator<Iter1>& lhs, const array_const_iterator<Iter2>& rhs) {
  return lhs.base() >= rhs.base();
}
template <typename Iter1, typename Iter2>
bool operator>=(const array_const_iterator<Iter1>& lhs, const array_iterator<Iter2>& rhs) {
  return lhs.base() >= rhs.base();
}

template <typename Iter1, typename Iter2>
bool operator<(const array_const_iterator<Iter1>& lhs, const array_const_iterator<Iter2>& rhs) {
  return lhs.base() < rhs.base();
}
template <typename Iter1, typename Iter2>
bool operator<(const array_iterator<Iter1>& lhs, const array_const_iterator<Iter2>& rhs) {
  return lhs.base() < rhs.base();
}
template <typename Iter1, typename Iter2>
bool operator<(const array_const_iterator<Iter1>& lhs, const array_iterator<Iter2>& rhs) {
  return lhs.base() < rhs.base();
}

template <typename Iter1, typename Iter2>
bool operator<=(const array_const_iterator<Iter1>& lhs, const array_const_iterator<Iter2>& rhs) {
  return lhs.base() <= rhs.base();
}

template <typename Iter1, typename Iter2>
bool operator<=(const array_iterator<Iter1>& lhs, const array_const_iterator<Iter2>& rhs) {
  return lhs.base() <= rhs.base();
}
template <typename Iter1, typename Iter2>
bool operator<=(const array_const_iterator<Iter1>& lhs, const array_iterator<Iter2>& rhs) {
  return lhs.base() <= rhs.base();
}

template <typename Pointer>
array_const_iterator<Pointer> operator+(typename array_const_iterator<Pointer>::difference_type n,
                                        const array_const_iterator<Pointer>&                    it) {
  return array_const_iterator<Pointer>(it.base() + n);
}

template <typename Pointer>
typename array_const_iterator<Pointer>::difference_type operator-(const array_const_iterator<Pointer>& lhs,
                                                                  const array_const_iterator<Pointer>& rhs) {
  return lhs.base() - rhs.base();
}

template <typename Pointer>
typename array_const_iterator<Pointer>::difference_type operator-(const array_iterator<Pointer>&       lhs,
                                                                  const array_const_iterator<Pointer>& rhs) {
  return lhs.base() - rhs.base();
}

template <typename Pointer>
typename array_const_iterator<Pointer>::difference_type operator-(const array_const_iterator<Pointer>& lhs,
                                                                  const array_iterator<Pointer>&       rhs) {
  return lhs.base() - rhs.base();
}

}  // namespace ft

#endif  // reverse_iterator_HPP