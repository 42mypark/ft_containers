#ifndef array_iterator_HPP
#define array_iterator_HPP

#include <iterator>

#include "enable_if.hpp"
#include "is_integral.hpp"
#include "iterator_traits.hpp"

namespace ft {

template <typename Iter>
class array_const_iterator;

template <typename Iter>
class array_iterator {
  // Types
 public:
  typedef Iter                                              iterator_type;
  typedef typename iterator_traits<Iter>::iterator_category iterator_category;
  typedef typename iterator_traits<Iter>::value_type        value_type;
  typedef typename iterator_traits<Iter>::difference_type   difference_type;
  typedef typename iterator_traits<Iter>::pointer           pointer;
  typedef typename iterator_traits<Iter>::reference         reference;

  // Member Variable
 protected:
  pointer current_;

  // Destructor
 public:
  ~array_iterator() {}

  // Constructor
 public:
  array_iterator() {}
  explicit array_iterator(iterator_type it) : current_(it) {}
  template <typename U>
  array_iterator(array_iterator<U>& other) : current_(other.base()) {}
  array_iterator(array_const_iterator<Iter>& other) : current_(other.base()) {}

  // Interface
 public:
  pointer base() const { return current_; }

  // Member operator
  template <typename U>
  array_iterator& operator=(array_iterator<U>& other);
  array_iterator& operator=(array_const_iterator<Iter>& other);
  array_iterator& operator=(pointer p);
  reference       operator*() const;
  pointer         operator->() const;
  reference       operator[](difference_type n) const;
  array_iterator& operator++();
  array_iterator  operator++(int);
  array_iterator& operator--();
  array_iterator  operator--(int);
  array_iterator  operator+(difference_type n) const;
  array_iterator  operator-(difference_type n) const;
  array_iterator& operator+=(difference_type n);
  array_iterator& operator-=(difference_type n);

  // Static Functions
 private:
  template <typename T>
  static T* to_pointer(T* p);
  template <typename T>
  static pointer to_pointer(T t);

};  // class array_iterator

// Member Operator

template <typename Iter>
template <typename U>
array_iterator<Iter>& array_iterator<Iter>::operator=(array_iterator<U>& other) {
  current_ = other.base();
  return (*this);
}

template <typename Iter>
array_iterator<Iter>& array_iterator<Iter>::operator=(array_const_iterator<Iter>& other) {
  current_ = other.base();
  return (*this);
}

template <typename Iter>
array_iterator<Iter>& array_iterator<Iter>::operator=(pointer p) {
  current_ = p;
  return (*this);
}

template <typename Iter>
typename array_iterator<Iter>::reference array_iterator<Iter>::operator*() const {
  return *current_;
}

template <typename Iter>
typename array_iterator<Iter>::pointer array_iterator<Iter>::operator->() const {
  return to_pointer(current_);
}
template <typename Iter>
typename array_iterator<Iter>::reference array_iterator<Iter>::operator[](difference_type n) const {
  return *(*this + n);
}

template <typename Iter>
array_iterator<Iter>& array_iterator<Iter>::operator++() {
  ++current_;
  return *this;
}

template <typename Iter>
array_iterator<Iter> array_iterator<Iter>::operator++(int) {
  array_iterator tmp = *this;
  ++current_;
  return tmp;
}

template <typename Iter>
array_iterator<Iter>& array_iterator<Iter>::operator--() {
  --current_;
  return *this;
}

template <typename Iter>
array_iterator<Iter> array_iterator<Iter>::operator--(int) {
  array_iterator tmp = *this;
  --current_;
  return tmp;
}

template <typename Iter>
array_iterator<Iter> array_iterator<Iter>::operator+(difference_type n) const {
  return array_iterator(current_ + n);
}

template <typename Iter>
array_iterator<Iter> array_iterator<Iter>::operator-(difference_type n) const {
  return array_iterator(current_ - n);
}

template <typename Iter>
array_iterator<Iter>& array_iterator<Iter>::operator+=(difference_type n) {
  current_ += n;
  return *this;
}

template <typename Iter>
array_iterator<Iter>& array_iterator<Iter>::operator-=(difference_type n) {
  current_ -= n;
  return *this;
}

// Non-member operators

template <typename Iter1, typename Iter2>
bool operator==(const array_iterator<Iter1>& lhs, const array_iterator<Iter2>& rhs) {
  return lhs.base() == rhs.base();
}

template <typename Iter1, typename Iter2>
bool operator!=(const array_iterator<Iter1>& lhs, const array_iterator<Iter2>& rhs) {
  return lhs.base() != rhs.base();
}

template <typename Iter1, typename Iter2>
bool operator>(const array_iterator<Iter1>& lhs, const array_iterator<Iter2>& rhs) {
  return lhs.base() > rhs.base();
}

template <typename Iter1, typename Iter2>
bool operator>=(const array_iterator<Iter1>& lhs, const array_iterator<Iter2>& rhs) {
  return lhs.base() >= rhs.base();
}

template <typename Iter1, typename Iter2>
bool operator<(const array_iterator<Iter1>& lhs, const array_iterator<Iter2>& rhs) {
  return lhs.base() < rhs.base();
}

template <typename Iter1, typename Iter2>
bool operator<=(const array_iterator<Iter1>& lhs, const array_iterator<Iter2>& rhs) {
  return lhs.base() <= rhs.base();
}

template <typename Iter>
array_iterator<Iter> operator+(typename array_iterator<Iter>::difference_type n, const array_iterator<Iter>& it) {
  return array_iterator<Iter>(it.base() + n);
}

template <typename Iter>
typename array_iterator<Iter>::difference_type operator-(const array_iterator<Iter>& lhs,
                                                         const array_iterator<Iter>& rhs) {
  return lhs.base() - rhs.base();
}

// Static Functions
template <typename Iter>
template <typename T>
T* array_iterator<Iter>::to_pointer(T* p) {
  return p;
}

template <typename Iter>
template <typename T>
typename array_iterator<Iter>::pointer array_iterator<Iter>::to_pointer(T t) {
  return t.operator->();
}

}  // namespace ft

#endif  // reverse_iterator_HPP