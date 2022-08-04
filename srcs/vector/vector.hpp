#ifndef vector_HPP
#define vector_HPP

#include <cstddef>
#include <iostream>
#include <limits>
#include <memory>
#include <stdexcept>

#include "array_const_iterator.hpp"
#include "array_iterator.hpp"
#include "enable_if.hpp"
#include "is_integral.hpp"
#include "lexicographical_compare.hpp"
#include "reverse_iterator.hpp"

namespace ft {

template <typename T, typename Allocator = std::allocator<T> >
class vector {
 public:
  // Types
  typedef T                                      value_type;
  typedef Allocator                              allocator_type;
  typedef std::size_t                            size_type;
  typedef std::ptrdiff_t                         difference_type;
  typedef T&                                     reference;
  typedef const T&                               const_reference;
  typedef typename allocator_type::pointer       pointer;
  typedef typename allocator_type::const_pointer const_pointer;
  typedef ft::array_iterator<pointer>            iterator;
  typedef ft::array_const_iterator<pointer>      const_iterator;
  typedef ft::reverse_iterator<iterator>         reverse_iterator;
  typedef ft::reverse_iterator<const_iterator>   const_reverse_iterator;

 protected:
  pointer        begin_;
  pointer        end_;
  pointer        capacity_;
  allocator_type alloc_;

  // Method
 private:
  void expand(size_type new_cap);

  // Destructor & Constructor
 public:
  ~vector() { alloc_.deallocate(begin_, capacity_ - begin_); }
  vector();                                                                                                // 1
  explicit vector(const allocator_type& alloc);                                                            // 2
  explicit vector(size_type count, const T& value = T(), const allocator_type& alloc = allocator_type());  // 3
  template <typename InputIt>
  vector(InputIt first, InputIt last, const allocator_type& alloc = allocator_type(),
         typename enable_if<!is_integral<InputIt>::value>::type* = 0);  // 4
  vector(const vector& other);                                          // 6
  vector(const vector& other, const allocator_type& alloc);             // 7

  // Interface
 public:
  allocator_type get_allocator() const { return alloc_; };
  vector&        operator=(const vector& other);
  void           assign(size_type count, const T& value);
  template <typename InputIt>
  void assign(InputIt first, InputIt last, typename enable_if<!is_integral<InputIt>::value>::type* = 0);

  // Element access memeber function
  reference         at(size_type pos);
  const_reference   at(size_type pos) const;
  reference         operator[](size_type pos) { return *(begin_ + pos); }
  const_reference   operator[](size_type pos) const { return *(begin_ + pos); }
  reference         front() { return *begin_; }
  const_reference   front() const { return *begin_; }
  reference         back() { return *(end_ - 1); }
  const_reference   back() const { return *(end_ - 1); }
  value_type*       data() { return begin_; }
  const value_type* data() const { return begin_; }

  // Iterator
  iterator               begin() { return iterator(begin_); }
  const_iterator         begin() const { return const_iterator(begin_); }
  iterator               end() { return iterator(end_); }
  const_iterator         end() const { return const_iterator(end_); }
  reverse_iterator       rbegin() { return reverse_iterator(iterator(end_)); }
  const_reverse_iterator rbegin() const { return const_reverse_iterator(iterator(end_)); }
  reverse_iterator       rend() { return reverse_iterator(iterator(begin_)); }
  const_reverse_iterator rend() const { return const_reverse_iterator(iterator(begin_)); }

  // Capacity
  bool      empty() const { return end_ == begin_; }
  size_type size() const { return end_ - begin_; }
  size_type max_size() const { return std::numeric_limits<difference_type>::max() / sizeof(T); }
  size_type capacity() const { return capacity_ - begin_; }
  void      reserve(size_type new_cap);

  // Modifiers
  void     clear() { end_ = begin_; }
  iterator insert(iterator pos, const T& value);
  void     insert(iterator pos, size_type count, const T& value);
  template <class InputIt>
  void insert(iterator pos, InputIt first, InputIt last, typename enable_if<!is_integral<InputIt>::value>::type* = 0);
  iterator erase(iterator pos);
  iterator erase(iterator first, iterator last);
  void     push_back(const T& value);
  void     pop_back() { --end_; }
  void     resize(size_type count, T value = T());
  void     swap(vector& other);
};  // class vector

// Constructor

template <typename T, typename A>
vector<T, A>::vector() {  // 1
  begin_    = alloc_.allocate(0);
  end_      = begin_;
  capacity_ = begin_;
}
template <typename T, typename A>
vector<T, A>::vector(const allocator_type& alloc) : alloc_(alloc) {  // 2
  begin_    = alloc_.allocate(0);
  end_      = begin_;
  capacity_ = begin_;
}
template <typename T, typename A>
vector<T, A>::vector(size_type count, const T& value, const allocator_type& alloc) : alloc_(alloc) {  // 3
  begin_ = alloc_.allocate(count);
  for (end_ = begin_; end_ - begin_ < static_cast<difference_type>(count); ++end_)
    *end_ = value;
  capacity_ = begin_ + count;
}

template <typename T, typename A>
template <typename InputIt>
vector<T, A>::vector(InputIt first, InputIt last, const allocator_type& alloc,
                     typename enable_if<!is_integral<InputIt>::value>::type*)
    : begin_(NULL), end_(NULL), capacity_(NULL), alloc_(alloc) {  // 5
  assign(first, last);
}

template <typename T, typename A>
vector<T, A>::vector(const vector& other) : begin_(NULL), end_(NULL), capacity_(NULL) {  // 6
  assign(other.begin(), other.end());
}
template <typename T, typename A>
vector<T, A>::vector(const vector& other, const allocator_type& alloc)
    : begin_(NULL), end_(NULL), capacity_(NULL), alloc_(alloc) {  // 7
  assign(other.begin(), other.end());
}

// Constructor end

// Method
template <typename T, class A>
void vector<T, A>::expand(size_type new_cap) {
  pointer tmp = alloc_.allocate(new_cap);
  for (pointer it = begin_; it != end_; ++it) {
    tmp[it - begin_] = *it;
  }
  alloc_.deallocate(begin_, capacity_ - begin_);
  size_type old_end = end_ - begin_;
  begin_            = tmp;
  end_              = begin_ + old_end;
  capacity_         = begin_ + new_cap;
}

// Interface

// Member Function::Assignment

template <typename T, typename A>
vector<T, A>& vector<T, A>::operator=(const vector& other) {
  if (this != &other)
    assign(other.begin(), other.end());
  return (*this);
}

template <typename T, typename A>
void vector<T, A>::assign(size_type count, const T& value) {
  if (capacity_ - begin_ < static_cast<difference_type>(count)) {
    pointer tmp = alloc_.allocate(count);
    alloc_.deallocate(begin_, capacity_ - begin_);
    begin_    = tmp;
    capacity_ = begin_ + count;
  }
  end_ = begin_;
  for (size_type i = 0; i < count; ++i) {
    *end_ = value;
    ++end_;
  }
}

template <typename T, typename A>
template <typename InputIt>
void vector<T, A>::assign(InputIt first, InputIt last, typename enable_if<!is_integral<InputIt>::value>::type*) {
  difference_type count = static_cast<difference_type>(last - first);
  if (capacity_ - begin_ < count) {
    pointer tmp = alloc_.allocate(count);
    alloc_.deallocate(begin_, capacity_ - begin_);
    begin_    = tmp;
    capacity_ = begin_ + count;
  }
  for (end_ = begin_; end_ < begin_ + count; ++first, ++end_)
    *end_ = *first;
}

// Memeber Funciton::Element Access

template <typename T, class A>
typename vector<T, A>::reference vector<T, A>::at(size_type pos) {
  if (pos >= size())
    throw std::out_of_range("ft::vector.at() : out of range");
  return *(begin_ + pos);
}

template <typename T, class A>
typename vector<T, A>::const_reference vector<T, A>::at(size_type pos) const {
  if (pos >= size())
    throw std::out_of_range("ft::vector.at() : out of range");
  return *(begin_ + pos);
}

// Member Function::Capacity

template <typename T, class A>
void vector<T, A>::reserve(size_type new_cap) {
  if (capacity_ - begin_ >= static_cast<difference_type>(new_cap))
    return;
  pointer tmp = alloc_.allocate(new_cap);
  for (pointer it = begin_; it != end_; ++it) {
    tmp[it - begin_] = *it;
  }
  alloc_.deallocate(begin_, capacity_ - begin_);
  end_      = tmp + (end_ - begin_);
  begin_    = tmp;
  capacity_ = begin_ + new_cap;
}

// Member Function::Insert

template <typename T, class A>
typename vector<T, A>::iterator vector<T, A>::insert(iterator pos, const T& value) {
  size_type index = pos.base() - begin_;
  if (end_ == capacity_) {
    size_type old_cap = capacity_ - begin_;
    size_type needed  = 1;
    size_type new_cap = old_cap * 2 > needed ? old_cap * 2 : needed;
    expand(new_cap);
  }
  pos = begin_ + index;
  for (pointer it = end_ - 1; it != pos.base() - 1; --it) {
    *(it + 1) = *it;
  }
  ++end_;
  *pos = value;
  return pos;
}

template <typename T, class A>
void vector<T, A>::insert(iterator pos, size_type count, const T& value) {
  if (count == 0)
    return;
  size_type index = pos.base() - begin_;
  if (end_ + count > capacity_) {
    size_type old_cap = capacity_ - begin_;
    size_type needed  = capacity_ - begin_ + count;
    size_type new_cap = old_cap * 2 > needed ? old_cap * 2 : needed;
    expand(new_cap);
  }
  pos       = begin_ + index;
  pointer p = pos.base();
  for (pointer it = end_ - 1; it != p - 1; --it) {
    *(it + count) = *it;
  }
  for (pointer it = p; it != p + count; ++it) {
    *it = value;
  }
  end_ += count;
}

template <typename T, class A>
template <class InputIt>
void vector<T, A>::insert(iterator pos, InputIt first, InputIt last,
                          typename enable_if<!is_integral<InputIt>::value>::type*) {
  size_type count = last - first;
  if (count == 0 || last < first)
    return;
  size_type index = pos.base() - begin_;
  if (end_ + count > capacity_) {
    size_type old_cap = capacity_ - begin_;
    size_type needed  = capacity_ - begin_ + count;
    size_type new_cap = old_cap * 2 > needed ? old_cap * 2 : needed;
    expand(new_cap);
  }
  pos       = begin_ + index;
  pointer p = pos.base();
  for (pointer it = end_ - 1; it != p - 1; --it) {
    *(it + count) = *it;
  }
  for (size_type i = 0; i < count; ++i) {
    *(p + i) = *(first + i);
  }
  end_ += count;
}

// Member Function::Erase

template <typename T, class A>
typename vector<T, A>::iterator vector<T, A>::erase(iterator pos) {
  pointer p = pos.base();
  for (pointer it = p; it + 1 != end_; ++it) {
    *it = *(it + 1);
  }
  --end_;
  return pos;
}

template <typename T, class A>
typename vector<T, A>::iterator vector<T, A>::erase(iterator first, iterator last) {
  if (first >= last)
    return last;
  int     i;
  pointer f = first.base();
  pointer l = last.base();
  for (i = 0; l + i != end_; ++i) {
    *(f + i) = *(l + i);
  }
  end_ = first.base() + i;
  return first;
}

// Member Function::push_back

template <typename T, class A>
void vector<T, A>::push_back(const T& value) {
  if (end_ == capacity_) {
    size_type old_cap = capacity_ - begin_;
    size_type needed  = 1;
    size_type new_cap = old_cap * 2 > needed ? old_cap * 2 : needed;
    expand(new_cap);
  }
  *end_ = value;
  ++end_;
}

template <typename T, class A>
void vector<T, A>::resize(size_type count, T value) {
  size_type old_cap = capacity_ - begin_;
  if (count > old_cap) {
    size_type new_cap = old_cap * 2 > count ? old_cap * 2 : count;
    expand(new_cap);
  } else if (static_cast<difference_type>(count) < end_ - begin_) {
    end_ = begin_ + count;
  }
  for (size_type i = end_ - begin_; i < count; ++i) {
    *(begin_ + i) = value;
    ++end_;
  }
}

template <typename T, class A>
void vector<T, A>::swap(vector& other) {
  pointer tmp     = begin_;
  begin_          = other.begin_;
  other.begin_    = tmp;
  tmp             = end_;
  end_            = other.end_;
  other.end_      = tmp;
  tmp             = capacity_;
  capacity_       = other.capacity_;
  other.capacity_ = tmp;
}

// Non Member Function

template <typename T, class A>
void swap(vector<T, A>& lhs, vector<T, A>& rhs) {
  lhs.swap(rhs);
}

template <typename T, typename A>
bool operator==(const ft::vector<T, A>& lhs, const ft::vector<T, A>& rhs) {
  typename ft::vector<T, A>::const_iterator li = lhs.begin();
  typename ft::vector<T, A>::const_iterator ri = rhs.begin();
  for (; li != lhs.end() && ri != rhs.end(); ++li, ++ri) {
    if (*li != *ri)
      return false;
  }
  return li == lhs.end() && ri == rhs.end();
}
template <typename T, typename A>
bool operator!=(const ft::vector<T, A>& lhs, const ft::vector<T, A>& rhs) {
  return !(lhs == rhs);
}

template <typename T, typename A>
bool operator<(const ft::vector<T, A>& lhs, const ft::vector<T, A>& rhs) {
  return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}
template <typename T, typename A>
bool operator<=(const ft::vector<T, A>& lhs, const ft::vector<T, A>& rhs) {
  return !(rhs < lhs);
}
template <typename T, typename A>
bool operator>(const ft::vector<T, A>& lhs, const ft::vector<T, A>& rhs) {
  return rhs < lhs;
}
template <typename T, typename A>
bool operator>=(const ft::vector<T, A>& lhs, const ft::vector<T, A>& rhs) {
  return !(lhs < rhs);
}

// Non Member function end

}  // namespace ft

#endif  // vector_HPP