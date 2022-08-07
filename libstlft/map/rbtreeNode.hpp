#ifndef rbtreeNode_HPP
#define rbtreeNode_HPP

#include "utility.hpp"

enum NodeColor { BLACK, RED };

template <typename Value>
struct rbtreeNode {
  typedef Value             value_type;
  typedef enum NodeColor    color;
  typedef rbtreeNode*       pointer;
  typedef const rbtreeNode* const_pointer;
  typedef rbtreeNode&       reference;
  typedef const rbtreeNode& const_reference;

  value_type value_;
  color      color_;
  pointer    left_, right_, parent_;

  ~rbtreeNode() {}
  rbtreeNode(const value_type& v, reference nil) : value_(v), color_(RED), left_(&nil), right_(&nil), parent_(&nil) {}
  rbtreeNode(const value_type& v, pointer parent, reference nil)
      : value_(v), color_(RED), left_(&nil), right_(&nil), parent_(parent) {}
  rbtreeNode(color c) : color_(c), left_(this), right_(this), parent_(NULL) {}
  rbtreeNode(const_reference n)
      : value_(n.value_), color_(n.color_), left_(n.left_), right_(n.right_), parent_(n.parent_) {}

 private:
  rbtreeNode() {}
  void selfToTarget(pointer self, pointer target);
  void changeSurround(reference node, reference other, reference nil);

 public:
  rbtreeNode& operator=(const_reference n);
  void        swap(rbtreeNode& other, reference nil);
};

template <typename Value>
rbtreeNode<Value>& rbtreeNode<Value>::operator=(const_reference n) {
  value_  = n.value_;
  color_  = n.color_;
  left_   = n.left_;
  right_  = n.right_;
  parent_ = n.parent_;
  return *this;
}

template <typename Value>
void rbtreeNode<Value>::selfToTarget(pointer self, pointer target) {
  if (self->parent_ == self)
    self->parent_ = target;
  if (self->left_ == self)
    self->left_ = target;
  if (self->right_ == self)
    self->right_ = target;
}

template <typename Value>
void rbtreeNode<Value>::changeSurround(reference node, reference other, reference nil) {
  if (node.left_ != &nil)
    node.left_->parent_ = &node;
  if (node.right_ != &nil)
    node.right_->parent_ = &node;
  if (node.parent_->left_ == &other)
    node.parent_->left_ = &node;
  if (node.parent_->right_ == &other)
    node.parent_->right_ = &node;
}

template <typename Value>
void rbtreeNode<Value>::swap(reference other, reference nil) {
  ft::swap(parent_, other.parent_);
  ft::swap(left_, other.left_);
  ft::swap(right_, other.right_);
  ft::swap(color_, other.color_);
  selfToTarget(this, &other);
  selfToTarget(&other, this);
  changeSurround(*this, other, nil);
  changeSurround(other, *this, nil);
}

#endif  // rbtreeNode_HPP