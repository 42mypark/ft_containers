#include <iostream>

#include "pair.hpp"

namespace ft {

enum NodeColor { BLACK, RED };

template <typename Value>
struct rbtreeNode {
  typedef Value          value_type;
  typedef enum NodeColor color;
  typedef rbtreeNode*    pointer;
  typedef rbtreeNode&    reference;

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

template <typename Key, typename Value, typename Compare, typename Allocator>
class rbtree {
  typedef Key                                              key_type;
  typedef Value                                            value_type;
  typedef rbtreeNode<value_type>                           node;
  typedef enum NodeColor                                   node_color;
  typedef typename node::pointer                           node_pointer;
  typedef typename node::reference                         node_reference;
  typedef typename Allocator::template rebind<node>::other node_allocator;

  static const Compare comp_;
  node                 nil_;
  node_pointer         root_;

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
    if (np == &nil_)
      return new node(p, nil_);
    if (comp_((*np).value_.first, p.first)) {
      np->right_ = insert(np->right_, p);
      np->right_->parent_ = np;
    } else if (comp_(p.first, (*np).value_.first)) {
      np->left_ = insert(np->left_, p);
      np->left_->parent_ = np;
    } else
      np->value_ = p;
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
    if (comp_(k, (*np).value_.first)) {
      if (!isRed(np->left_) && !isRed(np->left_->left_))
        np = moveRedLeft(np);
      np->left_ = remove(np->left_, k);
    } else {
      if (isRed(np->left_))
        np = rotateRight(np);
      if (!comp_((*np).value_.first, k) && np->right_ == &nil_) {
        delete np;
        return &nil_;
      }
      if (!isRed(np->right_) && !isRed(np->right_->right_))
        np = moveRedRight(np);
      if (!comp_((*np).value_.first, k)) {
        node_pointer min = leftMost(np->right_);
        np->value_ = min->value_;
        np->right_ = removeMin(np->right_);
      } else
        np->right_ = remove(np->right_, k);
    }
    return fixUp(np);
  }

 public:
  rbtree() : nil_(BLACK), root_(&nil_) {}
  void insert(const value_type& v) {
    root_ = insert(root_, v);
    nil_.left_ = root_;
    root_->color_ = BLACK;
  }
  void remove(const key_type& k) {
    root_ = remove(root_, k);
    nil_.left_ = root_;
    root_->color_ = BLACK;
  }
  node_pointer search(const key_type& k) {
    node_pointer curr = root_;
    while (curr != &nil_) {
      if (comp_((*curr).value_.first, k))
        curr = curr->right_;
      else if (comp_(k, (*curr).value_.first))
        curr = curr->left_;
      else
        return curr;
    }
    return &nil_;
  }
};

}  // namespace ft
