#ifndef rbtree_HPP
#define rbtree_HPP

#include <iostream>

#include "pair.hpp"

namespace ft {

enum NodeColor { BLACK, RED };

template <typename Value>
struct rbtreeNode {
  typedef Value             value_type;
  typedef enum NodeColor    color;
  typedef rbtreeNode*       pointer;
  typedef rbtreeNode&       reference;
  typedef const rbtreeNode& const_reference;

  value_type value_;
  color      color_;
  pointer    left_, right_, parent_;

  ~rbtreeNode() {}
  rbtreeNode(const value_type& v, reference nil)
      : value_(v), color_(RED), left_(&nil), right_(&nil), parent_(&nil) {}
  rbtreeNode(color c) : color_(c), left_(NULL), right_(NULL), parent_(NULL) {}
  // rbtreeNode(const rbtreeNode& node)
  //     : value_(node.value_),
  //       color_(node.color_),
  //       left_(node.left_),
  //       right_(node.right_),
  //       parent_(node.parent_) {}
 private:
  template <typename T>
  void swap(T& a, T& b) {
    T tmp;
    tmp = a;
    a = b;
    b = tmp;
  }

 public:
  void swap(rbtreeNode& other) {
    swap(parent_, other.parent_);
    swap(left_, other.left_);
    swap(right_, other.right_);
    swap(color_, other.color_);
  }
  void printNode() {
    std::cout << "value : " << value_.first << ", " << value_.second << '\n';
    std::cout << "color : " << color_ << '\n';
    std::cout << "this  : " << this << '\n';
    std::cout << "left  : " << left_ << '\n';
    std::cout << "right : " << right_ << '\n';
    std::cout << "parent: " << parent_ << '\n';
    std::cout << std::endl;
  }
};

template <typename Key, typename Value, typename Compare, typename Allocator, typename Extract>
class rbtree {
  typedef Key                                              key_type;
  typedef Value                                            value_type;
  typedef rbtreeNode<value_type>                           node;
  typedef typename node::color                             node_color;
  typedef typename node::pointer                           node_pointer;
  typedef typename node::reference                         node_reference;
  typedef typename node::const_reference                   const_node_reference;
  typedef typename Allocator::template rebind<node>::other node_allocator;

  const Extract extract_;
  const Compare comp_;
  node          nil_;
  node_pointer  root_;
  node_pointer  inserted_;
  bool          error_;

 private:
  bool isRed(node_pointer n) { return n->color_ == RED; }
  void colorFlip(node_pointer n) {
    n->color_ = static_cast<node_color>(!n->color_);
    n->left_->color_ = static_cast<node_color>(!n->left_->color_);
    n->right_->color_ = static_cast<node_color>(!n->right_->color_);
  }
  node_pointer rotateLeft(node_pointer np) {
    node_pointer nr = np->right_;
    nr->parent_ = np->parent_;
    np->parent_ = nr;
    np->right_ = nr->left_;
    nr->left_ = np;
    nr->color_ = np->color_;
    np->color_ = RED;
    return nr;
  }
  node_pointer rotateRight(node_pointer np) {
    node_pointer nl = np->left_;
    nl->parent_ = np->parent_;
    np->parent_ = nl;
    np->left_ = nl->right_;
    nl->right_ = np;
    nl->color_ = np->color_;
    np->color_ = RED;
    return nl;
  }
  node_pointer fixUp(node_pointer np) {
    if (isRed(np->left_) && isRed(np->left_->right_))
      np->left_ = rotateLeft(np->left_);
    if (!isRed(np->left_) && isRed(np->right_))
      np = rotateLeft(np);
    if (isRed(np->left_) && isRed(np->left_->left_))
      np = rotateRight(np);
    if (isRed(np->left_) && isRed(np->right_))
      colorFlip(np);
    return np;
  }
  node_pointer insert(node_pointer np, const value_type& p) {
    if (np == &nil_) {
      inserted_ = new node(p, nil_);
      return inserted_;
    }
    if (comp_(extract_(np->value_), p.first)) {
      np->right_ = insert(np->right_, p);
      np->right_->parent_ = np;
    } else if (comp_(p.first, extract_(np->value_))) {
      np->left_ = insert(np->left_, p);
      np->left_->parent_ = np;
    } else {
      inserted_ = np;
      error_ = true;
    }
    return fixUp(np);
  }

  node_pointer moveRedRight(node_pointer np) {
    colorFlip(np);
    if (isRed(np->left_->left_)) {
      np = rotateLeft(np);
      colorFlip(np);
    }
    return np;
  }

  node_pointer moveRedLeft(node_pointer np) {
    colorFlip(np);
    if (isRed(np->right_->left_)) {
      np->right_ = rotateRight(np->right_);
      np = rotateLeft(np);
      colorFlip(np);
    }
    return np;
  }
  node_pointer leftMost(node_pointer np) {
    while (np->left_ != &nil_)
      np = np->left_;
    return np;
  }
  node_pointer removeMin(node_pointer np) {
    if (np->left_ == &nil_) {
      delete np;
      return &nil_;
    }
    if (!isRed(np->left_) && !isRed(np->left_->left_))
      np = moveRedLeft(np);
    np->left_ = removeMin(np->left_);
    return fixUp(np);
  }
  node_pointer remove(node_pointer np, const key_type& k) {
    if (np == &nil_) {
      error_ = true;
      return &nil_;
    }

    if (comp_(k, extract_(np->value_))) {
      if (!isRed(np->left_) && !isRed(np->left_->left_))
        np = moveRedLeft(np);
      np->left_ = remove(np->left_, k);
    } else {
      bool same;
      if (isRed(np->left_))
        np = rotateRight(np);
      same = !comp_(extract_(np->value_), k);
      if (same && np->right_ == &nil_) {
        delete np;
        return &nil_;
      }
      if (!isRed(np->right_) && !isRed(np->right_->right_))
        np = moveRedRight(np);
      same = !comp_(extract_(np->value_), k);
      if (same) {
        node_pointer min = leftMost(np->right_);
        np->swap(*min);
        np->right_ = removeMin(np->right_);
      } else
        np->right_ = remove(np->right_, k);
    }
    return fixUp(np);
  }
  void removeTree(node_pointer np) {
    if (np == &nil_)
      return;
    removeTree(np->left_);
    removeTree(np->right_);
    delete np;
  }
  node_pointer search(const key_type& k) {
    node_pointer curr = root_;
    while (curr != &nil_) {
      if (comp_(extract_(curr->value_), k))
        curr = curr->right_;
      else if (comp_(k, extract_(curr->value_)))
        curr = curr->left_;
      else
        return curr;
    }
    error_ = true;
    return &nil_;
  }

 public:
  ~rbtree() {
    removeTree(root_);
    nil_.left_ = NULL;
    nil_.right_ = NULL;
    nil_.parent_ = NULL;
    root_ = &nil_;
    inserted_ = NULL;
    error_ = false;
  }
  rbtree() : nil_(BLACK), root_(&nil_), inserted_(NULL), error_(false), comp_(), extract_() {}
  node_reference insert(const value_type& v) {
    error_ = false;
    root_ = insert(root_, v);
    nil_.left_ = root_;
    nil_.right_ = leftMost(root_);
    root_->color_ = BLACK;
    return *inserted_;
  }
  // node_reference insert(node_pointer hint, const value_type& v) {
  //   error_ = false;
  //   hint->parent_ = insert(hint->parent_, v);
  //   nil_.left_ = root_;
  //   nil_.right_ = leftMost(root_);
  //   root_->color_ = BLACK;
  //   return *inserted_;
  // }
  void remove(const key_type& k) {
    error_ = false;
    root_ = remove(root_, k);
    nil_.left_ = root_;
    nil_.right_ = leftMost(root_);
    root_->color_ = BLACK;
  }
  value_type& search_value(const key_type& k) {
    error_ = false;
    return search(k)->value_;
  }
  node_reference find(const key_type& k) {
    error_ = false;
    return *search(k);
  }
  node_reference nil() { return nil_; }
  node_reference leftMost() { return *nil_.right_; }
  bool           error() { return error_; }
  node_reference bound(const key_type& k) {
    node_pointer curr = root_;
    node_pointer prev;
    while (curr != &nil_) {
      prev = curr;
      if (comp_(k, extract_(curr->value_)))
        curr = curr->left_;
      else
        curr = curr->right_;
    }
    return *prev;
  }
};

}  // namespace ft

#endif  // rbtree_HPP