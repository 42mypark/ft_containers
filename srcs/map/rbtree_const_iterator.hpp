#ifndef rbtree_const_iterator_HPP
#define rbtree_const_iterator_HPP
#include "iterator_traits.hpp"
#include "rbtree.hpp"

namespace ft {

template <typename Value>
class rbtree_iterator;

template <typename Value>
class rbtree_const_iterator {
 public:
  typedef typename std::ptrdiff_t             difference_type;
  typedef Value                               value_type;
  typedef const value_type*                   pointer;
  typedef const value_type&                   reference;
  typedef bidirectional_iterator_tag          iterator_category;
  typedef rbtreeNode<value_type>              node_type;
  typedef typename node_type::const_pointer   const_node_pointer;
  typedef typename node_type::const_reference const_node_reference;

 protected:
  const_node_pointer current_;

 private:
  // Member Method
  bool isLeft() { return current_->parent_->left_ == current_; }
  bool isRight() { return current_->parent_->right_ == current_; }
  bool isNil() { return current_->parent_ == NULL; }
  bool isLeftNil() { return current_->left_->parent_ == NULL; }
  bool isRightNil() { return current_->right_->parent_ == NULL; }

 public:
  // Constructor & Destructor
  ~rbtree_const_iterator() {}
  rbtree_const_iterator() : current_(NULL) {}
  rbtree_const_iterator(const_node_reference node) : current_(&node) {}
  rbtree_const_iterator(const rbtree_const_iterator& it) : current_(it.base()) {}
  rbtree_const_iterator(const rbtree_iterator<value_type>& it) : current_(it.base()) {}

  // Member Interface
  const_node_pointer base() const { return current_; }

  // Member Operator
  rbtree_const_iterator& operator=(const rbtree_const_iterator<Value>& other) {
    current_ = other.base();
    return *this;
  }

  reference operator*() const { return current_->value_; }
  pointer   operator->() const { return &(current_->value_); }
  reference operator[](difference_type n) const { return *(*this + n); }

  rbtree_const_iterator& operator++() {
    if (isNil())
      return *this;
    if (!isRightNil()) {
      current_ = current_->right_;
      while (!isLeftNil())
        current_ = current_->left_;
    } else if (isRightNil() && isLeft()) {
      current_ = current_->parent_;
    } else if (isRightNil() && isRight()) {
      current_ = current_->parent_;
      while (!isLeft())
        current_ = current_->parent_;
      current_ = current_->parent_;
    }
    return *this;
  }
  rbtree_const_iterator operator++(int) {
    rbtree_const_iterator tmp = *this;
    ++(*this);
    return tmp;
  }

  rbtree_const_iterator& operator--() {
    if (isNil() || !isLeftNil()) {
      current_ = current_->left_;
      while (!isRightNil())
        current_ = current_->right_;
    } else if (isLeftNil() && isRight()) {
      current_ = current_->parent_;
    } else if (isLeftNil() && isLeft()) {
      current_ = current_->parent_;
      while (!isRight())
        current_ = current_->parent_;
      current_ = current_->parent_;
    }
    return *this;
  }
  rbtree_const_iterator operator--(int) {
    rbtree_const_iterator tmp = *this;
    --(*this);
    return tmp;
  }

  rbtree_const_iterator operator+(difference_type n) const {
    rbtree_const_iterator tmp = *this;
    for (difference_type i = 0; i < n; ++i)
      ++tmp;
    return tmp;
  }
  rbtree_const_iterator operator-(difference_type n) const {
    rbtree_const_iterator tmp = *this;
    for (difference_type i = 0; i < n; ++i)
      --tmp;
    return tmp;
  }
  rbtree_const_iterator& operator+=(difference_type n) {
    for (difference_type i = 0; i < n; ++i)
      ++(*this);
    return *this;
  }
  rbtree_const_iterator& operator-=(difference_type n) {
    for (difference_type i = 0; i < n; ++i)
      --(*this);
    return *this;
  }
};

// Non Member Operator

template <typename Value1, typename Value2>
bool operator==(const rbtree_const_iterator<Value1>& lhs, const rbtree_const_iterator<Value2>& rhs) {
  return lhs.base() == rhs.base();
}

template <typename Value1, typename Value2>
bool operator!=(const rbtree_const_iterator<Value1>& lhs, const rbtree_const_iterator<Value2>& rhs) {
  return lhs.base() != rhs.base();
}

template <typename Value1, typename Value2>
bool operator==(const rbtree_iterator<Value1>& lhs, const rbtree_const_iterator<Value2>& rhs) {
  return lhs.base() == rhs.base();
}

template <typename Value1, typename Value2>
bool operator!=(const rbtree_iterator<Value1>& lhs, const rbtree_const_iterator<Value2>& rhs) {
  return lhs.base() != rhs.base();
}

template <typename Value1, typename Value2>
bool operator==(const rbtree_const_iterator<Value1>& lhs, const rbtree_iterator<Value2>& rhs) {
  return lhs.base() == rhs.base();
}

template <typename Value1, typename Value2>
bool operator!=(const rbtree_const_iterator<Value1>& lhs, const rbtree_iterator<Value2>& rhs) {
  return lhs.base() != rhs.base();
}

template <typename Value>
rbtree_const_iterator<Value> operator+(typename rbtree_const_iterator<Value>::difference_type n,
                                       const rbtree_const_iterator<Value>&                    it) {
  return it + n;
}

}  // namespace ft

#endif  // rbtree_const_iterator_HPP