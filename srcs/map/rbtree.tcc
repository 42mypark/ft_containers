#include "pair.hpp"

namespace ft {

enum NodeColor { BLACK, RED };

template <typename Key, typename Value>
struct rbtreeNode {
  typedef Key            key;
  typedef Value          value;
  typedef enum NodeColor color;
  typedef rbtreeNode*    pointer;
  typedef rbtreeNode&    reference;

  static const rbtreeNode nil(value(), BLACK);

  key     key_;
  value   value_;
  color   color_;
  pointer left_, right_, parent_;

  ~rbtreeNode() {}
  rbtreeNode(const value& p)
      : key_(p.frist), value_(p.second), color_(RED), left_(&nil), right_(&nil), parent_(&nil) {}
  rbtreeNode(const value& p, color c)
      : key_(p.frist), value_(p.second), color_(c), left_(&nil), right_(&nil), parent_(&nil) {}
  rbtreeNode(const rbtreeNode& node)
      : key_(node.key_),
        value_(node.value_),
        color_(node.color_),
        left_(node.left_),
        right_(node.right_),
        parent_(node.parent_) {}
};

template <typename Key, typename Value, typename Compare, typename Allocator>
class rbtree {
  typedef Key                                                           key;
  typedef Value                                                         value;
  typedef typename rbtreeNode<key, value>                               node;
  typedef typename rbtreeNode<key, value>::pointer                      node_pointer;
  typedef typename rbtreeNode<key, value>::reference                    node_reference;
  typedef typename Allocator::template rebind<struct rbtreeNode>::other node_allocator;

  const Compare comp_;
  node_pointer  root_;

 private:
  bool isRed(node_pointer n) { return n->color_ == RED; }
  void colorFlip(node_pointer n) {
    n->color_ = !n->color_;
    n->left_->color_ = !n->left_->color_;
    n->right_->color_ = !n->right_->color_;
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
  node_pointer insert(node_pointer np, const value& p) {
    if (np == &node::nil)
      return new rbtreeNode(p);
    if (comp_(np->key_, p.first)) {
      np->right_ = insert(np->right_, p);
      np->right_->parent_ = np;
    } else if (comp_(p.first, np->key_)) {
      np->left_ = insert(np->left_, p);
      np->left_->parent_ = np;
    } else
      np->value_ = p.second;
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
  node_pointer find_min(node_pointer np) {
    while (np->left != &node::nil)
      np = np->left;
    return np;
  }
  node_pointer remove_min(node_pointer np) {
    if (np->left_ == &node::nil) {
      delete np;
      return &node::nil;
    }
    if (!isRed(np->left_) && !isRed(np->left_->left_))
      np = moveRedLeft(np);
    np->left_ = remove_min(np->left_);
    return fixUp(np);
  }
  node_pointer remove(node_pointer np, const key& k) {
    if (comp_(k, np->key_)) {
      if (!isRed(np->left_) && !isRed(np->left_->left_))
        np = moveRedLeft(np);
      np->left_ = remove(np->left_);
    } else {
      if (isRed(np->left))
        np = rotateRight(np);
      if (!comp_(np->key_, k) && np->right == &node::nil) {
        delete np;
        return &node::nil;
      }
      if (!isRed(np->right_) && !isRed(np->right_->right_))
        np = moveRedRight(np);
      if (!comp_(np->key_, k)) {
        node_pointer min = find_min(np->right_);
        np->key_ = min->key_;
        np->value_ = min->value_;
        np->right_ = remove_min(np->right_);
      } else
        np->right = remove(np->right, k);
    }

    return fixUp(np);
  }

 public:
  rbtree() : root_(&node::nil) {}
  void insert(const key& k, const value v) {
    root_ = insert(root_, ft::make_pair(k, v));
    root_->color_ = BLACK;
  }
  void insert(const pair_type& p) {
    root_ = insert(root_, p);
    root_->color_ = BLACK;
  }
  void remove(const key& k) {
    root_ = remove(root_, k);
    root_->color_ = BLACK;
  }
  value search(const key& k) {
    node_pointer curr = root_;
    while (curr != &node::nil) {
      if (comp_(curr->key_, k))
        curr = curr->right_;
      else if (comp_(k, curr->key_))
        curr = curr->left_;
      else
        return curr->value_;
    }
    return value();
  }
};

}  // namespace ft
