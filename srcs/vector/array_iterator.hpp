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
 public:
  // Types
  typedef Iter                                              iterator_type;
  typedef typename iterator_traits<Iter>::iterator_category iterator_category;
  typedef typename iterator_traits<Iter>::value_type        value_type;
  typedef typename iterator_traits<Iter>::difference_type   difference_type;
  typedef typename iterator_traits<Iter>::pointer           pointer;
  typedef typename iterator_traits<Iter>::reference         reference;

 protected:
  pointer current_;

 public:
  // Constructor
  ~array_iterator() {}
  array_iterator() {}
  explicit array_iterator(iterator_type it) : current_(it) {}
  template <typename U>
  array_iterator(array_iterator<U>& other) : current_(other.base()) {}
  array_iterator(array_const_iterator<Iter>& other) : current_(other.base()) {}

  // Member function
  pointer base() const { return current_; }

  // Member operator
  template <typename U>
  array_iterator& operator=(array_iterator<U>& other) {
    current_ = other.base();
    return (*this);
  }
  array_iterator& operator=(array_const_iterator<Iter>& other) {
    current_ = other.base();
    return (*this);
  }
  array_iterator& operator=(pointer p) {
    current_ = p;
    return (*this);
  }

  reference operator*() const { return *current_; }
  pointer   operator->() const { return to_pointer(current_); }

  reference operator[](difference_type n) const { return *(*this + n); }

  array_iterator& operator++() {
    ++current_;
    return *this;
  }

  array_iterator operator++(int) {
    array_iterator tmp = *this;
    ++current_;
    return tmp;
  }

  array_iterator& operator--() {
    --current_;
    return *this;
  }

  array_iterator operator--(int) {
    array_iterator tmp = *this;
    --current_;
    return tmp;
  }

  array_iterator operator+(difference_type n) const { return array_iterator(current_ + n); }

  array_iterator operator-(difference_type n) const { return array_iterator(current_ - n); }

  array_iterator& operator+=(difference_type n) {
    current_ += n;
    return *this;
  }

  array_iterator& operator-=(difference_type n) {
    current_ -= n;
    return *this;
  }

 private:
  template <typename T>
  static T* to_pointer(T* p) {
    return p;
  }
  template <typename T>
  static pointer to_pointer(T t) {
    return t.operator->();
  }
};  // class array_iterator

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

}  // namespace ft

#endif  // reverse_iterator_HPP