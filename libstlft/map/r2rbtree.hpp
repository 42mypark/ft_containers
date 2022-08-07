#ifndef rbtree2_HPP
#define rbtree2_HPP

#include <limits>

#include "pair.hpp"
#include "rbtreeNode.hpp"
#include "vector.hpp"

namespace ft {

template <typename Key, typename Value, typename Compare, typename Allocator, typename Extract>
class rbtree {
  // Types
 public:
  typedef Key                                              key_type;
  typedef Value                                            value_type;
  typedef std::size_t                                      size_type;
  typedef std::ptrdiff_t                                   difference_type;
  typedef rbtreeNode<value_type>                           node;
  typedef typename node::color                             node_color;
  typedef typename node::pointer                           node_pointer;
  typedef typename node::reference                         node_reference;
  typedef typename node::const_reference                   const_node_reference;
  typedef typename Allocator::template rebind<node>::other node_allocator;

  // Member Variable
 protected:
  node           nil_;
  node_pointer   root_;
  node_pointer   inserted_;
  node_allocator alloc_;
  bool           error_;
  const Compare  comp_;
  const Extract  extract_key_;
  node_pointer   cache_red_;

  // Method
 private:
  bool         isRed(node_pointer n) { return n->color_ == RED; }
  bool         isBlack(node_pointer n) { return n->color_ == BLACK; }
  bool         isLeft(node_pointer n) { return n->parent_->left_ == n; }
  bool         isRight(node_pointer n) { return n->parent_->right_ == n; }
  bool         isUncleBlack(node_pointer n);
  size_type    countHeight(node_pointer np);
  void         colorFlip(node_pointer n);
  node_pointer rotateLeft(node_pointer np);
  node_pointer rotateLeft(node_pointer current, node_pointer parent);
  node_pointer rotateRight(node_pointer np);
  node_pointer rotateRight(node_pointer current, node_pointer parent);
  void         resolveDoubleRed(node_pointer np);
  node_pointer fixUp(node_pointer np);
  void         fixRoot();
  node_pointer insert(node_pointer np, const value_type& p);
  void         insertNode(node_pointer& pos, node_pointer parent, const value_type& v);
  node_pointer moveRedRight(node_pointer np);
  node_pointer moveRedLeft(node_pointer np);
  void         moveRedDirection(node_pointer curr, node_pointer direction, node_pointer opposite);
  void         moveRedToTarget(const key_type& k);
  node_pointer leftMost(node_pointer np);
  node_pointer removeLeftMost(node_pointer np);
  node_pointer rightMost(node_pointer np);
  node_pointer removeMin(node_pointer np);
  node_pointer remove(node_pointer np, const key_type& k);
  void         removeNode(node_pointer np);
  void         removeTree(node_pointer np);
  node_pointer search(const key_type& k);
  node_pointer removeSearch(const key_type& k);

  // Desturctor
 public:
  ~rbtree();

  // Constructor
 private:
  rbtree(const rbtree& t) { static_cast<void>(t); }

 public:
  rbtree() : nil_(BLACK), root_(&nil_), inserted_(NULL), error_(false), comp_(), extract_key_(), cache_red_(&nil_) {}

  // Interface
 private:
  rbtree& operator=(const rbtree& t);

 public:
  node_reference       insert(const value_type& v);
  node_reference       insert(const value_type& v, node_pointer hint);
  void                 remove(const key_type& k);
  value_type&          searchValue(const key_type& k);
  node_reference       find(const key_type& k);
  node_reference       nil() { return nil_; }
  const_node_reference nil() const { return nil_; }
  node_reference       leftMost() { return *nil_.right_; }
  const_node_reference leftMost() const { return *nil_.right_; }
  bool                 error() { return error_; }
  node_reference       bound(const key_type& k);
  size_type            max_size() const { return std::numeric_limits<difference_type>::max() / sizeof(node); }
};  // class rbtree

// Desturctor
template <typename K, typename V, typename C, typename A, typename E>
rbtree<K, V, C, A, E>::~rbtree() {
  removeTree(root_);
  nil_.left_   = &nil_;
  nil_.right_  = &nil_;
  nil_.parent_ = NULL;
  root_        = &nil_;
  inserted_    = NULL;
  error_       = false;
  cache_red_   = &nil_;
}

// Member Operator

template <typename K, typename V, typename C, typename A, typename E>
rbtree<K, V, C, A, E>& rbtree<K, V, C, A, E>::operator=(const rbtree& t) {
  static_cast<void>(t);
  return *this;
}

// Method

template <typename K, typename V, typename C, typename A, typename E>
typename rbtree<K, V, C, A, E>::size_type rbtree<K, V, C, A, E>::countHeight(node_pointer np) {
  size_type count = 1;
  while (np->left_ != &nil_) {
    np = np->left_;
    ++count;
  }
  return count;
}

template <typename K, typename V, typename C, typename A, typename E>
bool rbtree<K, V, C, A, E>::isUncleBlack(node_pointer n) {
  return !(isRed(n->parent_->parent_->left_) && isRed(n->parent_->parent_->right_));
}

template <typename K, typename V, typename C, typename A, typename E>
typename rbtree<K, V, C, A, E>::node_pointer rbtree<K, V, C, A, E>::leftMost(node_pointer np) {
  while (np->left_ != &nil_)
    np = np->left_;
  return np;
}

template <typename K, typename V, typename C, typename A, typename E>
typename rbtree<K, V, C, A, E>::node_pointer rbtree<K, V, C, A, E>::rightMost(node_pointer np) {
  while (np->right_ != &nil_)
    np = np->right_;
  return np;
}

template <typename K, typename V, typename C, typename A, typename E>
void rbtree<K, V, C, A, E>::colorFlip(node_pointer n) {
  n->color_         = static_cast<node_color>(!n->color_);
  n->left_->color_  = static_cast<node_color>(!n->left_->color_);
  n->right_->color_ = static_cast<node_color>(!n->right_->color_);
}

template <typename K, typename V, typename C, typename A, typename E>
typename rbtree<K, V, C, A, E>::node_pointer rbtree<K, V, C, A, E>::rotateLeft(node_pointer np) {
  node_pointer nr = np->right_;
  nr->parent_     = np->parent_;
  np->parent_     = nr;
  np->right_      = nr->left_;
  nr->left_       = np;
  nr->color_      = np->color_;
  np->color_      = RED;
  if (np->right_ != &nil_)
    np->right_->parent_ = np;
  return nr;
}

template <typename K, typename V, typename C, typename A, typename E>
typename rbtree<K, V, C, A, E>::node_pointer rbtree<K, V, C, A, E>::rotateLeft(node_pointer current,
                                                                               node_pointer parent) {
  node_pointer& pos = isLeft(current) ? parent->left_ : parent->right_;

  pos = rotateLeft(current);
  if (current == root_)
    root_ = pos;
  return pos;
}

template <typename K, typename V, typename C, typename A, typename E>
typename rbtree<K, V, C, A, E>::node_pointer rbtree<K, V, C, A, E>::rotateRight(node_pointer np) {
  node_pointer nl = np->left_;
  nl->parent_     = np->parent_;
  np->parent_     = nl;
  np->left_       = nl->right_;
  nl->right_      = np;
  nl->color_      = np->color_;
  np->color_      = RED;
  if (np->left_ != &nil_)
    np->left_->parent_ = np;
  return nl;
}

template <typename K, typename V, typename C, typename A, typename E>
typename rbtree<K, V, C, A, E>::node_pointer rbtree<K, V, C, A, E>::rotateRight(node_pointer current,
                                                                                node_pointer parent) {
  node_pointer& pos = isLeft(current) ? parent->left_ : parent->right_;

  pos = rotateRight(current);
  if (current == root_)
    root_ = pos;
  return pos;
}

template <typename K, typename V, typename C, typename A, typename E>
void rbtree<K, V, C, A, E>::resolveDoubleRed(node_pointer np) {
  node_pointer curr   = np;
  node_pointer parent = curr->parent_;
  while (curr != root_ && parent != root_ && isRed(parent)) {
    // uncle black
    if (isUncleBlack(curr) && isLeft(parent)) {
      if (isRight(curr))
        parent = rotateLeft(parent, parent->parent_);
      rotateRight(parent->parent_, parent->parent_->parent_);
      colorFlip(parent->parent_);
      return;
    }
    if (isUncleBlack(curr) && isRight(parent)) {
      if (isLeft(curr))
        parent = rotateRight(parent, parent->parent_);
      rotateLeft(parent->parent_, parent->parent_->parent_);
      return;
    }
    // uncle red
    colorFlip(parent->parent_);
    curr   = curr->parent_->parent_;
    parent = curr->parent_;
  }
  while (curr != root_ && isRed(parent->left_) && isRed(parent->right_)) {
    colorFlip(parent);
    curr   = curr->parent_;
    parent = curr->parent_;
  }
}

template <typename K, typename V, typename C, typename A, typename E>
typename rbtree<K, V, C, A, E>::node_pointer rbtree<K, V, C, A, E>::moveRedRight(node_pointer np) {
  colorFlip(np);
  if (isRed(np->left_->left_)) {
    np = rotateLeft(np);
    colorFlip(np);
  }
  return np;
}

template <typename K, typename V, typename C, typename A, typename E>
typename rbtree<K, V, C, A, E>::node_pointer rbtree<K, V, C, A, E>::moveRedLeft(node_pointer np) {
  colorFlip(np);
  if (isRed(np->right_->left_)) {
    np->right_ = rotateRight(np->right_);
    np         = rotateLeft(np);
    colorFlip(np);
  }
  return np;
}

template <typename K, typename V, typename C, typename A, typename E>
typename rbtree<K, V, C, A, E>::node_pointer rbtree<K, V, C, A, E>::fixUp(node_pointer np) {
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

// template <typename K, typename V, typename C, typename A, typename E>
// typename rbtree<K, V, C, A, E>::node_pointer rbtree<K, V, C, A, E>::insert(node_pointer np, const value_type& p) {
//   if (np == &nil_) {
//     inserted_ = alloc_.allocate(1);
//     alloc_.construct(inserted_, node(p, nil_));
//     return inserted_;
//   }
//   if (comp_(extract_key_(p), extract_key_(np->value_))) {
//     np->left_          = insert(np->left_, p);
//     np->left_->parent_ = np;
//   } else if (comp_(extract_key_(np->value_), extract_key_(p))) {
//     np->right_          = insert(np->right_, p);
//     np->right_->parent_ = np;
//   } else {
//     inserted_ = np;
//     error_    = true;
//   }
//   return fixUp(np);
// }

template <typename K, typename V, typename C, typename A, typename E>
void rbtree<K, V, C, A, E>::insertNode(node_pointer& pos, node_pointer parent, const value_type& v) {
  pos = alloc_.allocate(1);
  alloc_.construct(pos, node(v, parent, nil_));
  inserted_ = pos;
}

template <typename K, typename V, typename C, typename A, typename E>
typename rbtree<K, V, C, A, E>::node_pointer rbtree<K, V, C, A, E>::insert(node_pointer np, const value_type& v) {
  (void)np;
  key_type     v_key    = extract_key_(v);
  node_pointer parent   = &bound(extract_key_(v));
  key_type     p_key    = extract_key_(parent->value_);
  bool         to_left  = comp_(v_key, p_key);
  bool         to_right = comp_(p_key, v_key);

  if (parent == &nil_) {
    insertNode(parent->left_, parent, v);
    root_ = inserted_;
  } else if (to_left)
    insertNode(parent->left_, parent, v);
  else if (to_right)
    insertNode(parent->right_, parent, v);
  else {
    error_    = true;
    inserted_ = parent;
    return root_;
  }

  if (isBlack(parent))
    return root_;

  resolveDoubleRed(inserted_);
  return root_;
}

template <typename K, typename V, typename C, typename A, typename E>
void rbtree<K, V, C, A, E>::moveRedToTarget(const key_type& k) {
  node_pointer curr     = cache_red_;
  bool         to_right = false;
  bool         to_left  = false;

  cache_red_->color_ = RED;
  while (curr != &nil_) {
    to_right = comp_(extract_key_(curr->value_), k);
    to_left  = comp_(k, extract_key_(curr->value_));
    if (!to_right && !to_left)
      break;
    if (to_right) {
      moveRedRight(curr);
      curr = curr->right_;
    } else {
      moveRedLeft(curr);
      curr = curr->left_;
    }
  }
}

template <typename K, typename V, typename C, typename A, typename E>
void rbtree<K, V, C, A, E>::removeNode(node_pointer np) {
  if (np == root_)
    root_ = &nil_;
  if (isLeft(np))
    np->parent_->left_ = &nil_;
  else
    np->parent_->right_ = &nil_;
  alloc_.deallocate(np, 1);
}

template <typename K, typename V, typename C, typename A, typename E>
typename rbtree<K, V, C, A, E>::node_pointer rbtree<K, V, C, A, E>::remove(node_pointer np, const key_type& k) {
  (void)np;
  node_pointer target = removeSearch(k);
  if (error_)
    return root_;

  if (target->right_ == &nil_) {
    if (isRed(target->left_))  // BLACK ( 3-node )
      rotateRight(target, target->parent_);
    else if (isBlack(target))  // BLACK ( 2-node )
      moveRedToTarget(k);
    removeNode(target);
    return root_;
  }

  node_pointer left_most = removeLeftMost(target->right_);
  if (isRed(left_most->right_))  // BLACK ( 3-node )
    rotateLeft(left_most, left_most->parent_);
  else if (isBlack(left_most))  // BLACK ( 2-node )
    moveRedToTarget(extract_key_(left_most->value_));
  if (target == root_)
    root_ = left_most;
  target->swap(*left_most, nil_);
  removeNode(target);

  return root_;
}

template <typename K, typename V, typename C, typename A, typename E>
void rbtree<K, V, C, A, E>::removeTree(node_pointer np) {
  if (np == &nil_)
    return;
  removeTree(np->left_);
  removeTree(np->right_);
  alloc_.deallocate(np, 1);
}

template <typename K, typename V, typename C, typename A, typename E>
typename rbtree<K, V, C, A, E>::node_pointer rbtree<K, V, C, A, E>::search(const key_type& k) {
  node_pointer curr = root_;
  while (curr != &nil_) {
    if (comp_(extract_key_(curr->value_), k))
      curr = curr->right_;
    else if (comp_(k, extract_key_(curr->value_)))
      curr = curr->left_;
    else
      return curr;
  }
  error_ = true;
  return &nil_;
}

template <typename K, typename V, typename C, typename A, typename E>
void rbtree<K, V, C, A, E>::moveRedDirection(node_pointer curr, node_pointer direction, node_pointer opposite) {
  // if (isRed(opposite->left_) && isRed(opposite->left_)) {
  //   colorFlip(opposite);
  //   if (isRed(curr))
  //     resolveDoubleRed(opposite);
  // }
  if (isBlack(direction) && isRed(opposite))
    rotateLeft(curr, curr->parent_);
}

template <typename K, typename V, typename C, typename A, typename E>
typename rbtree<K, V, C, A, E>::node_pointer rbtree<K, V, C, A, E>::removeLeftMost(node_pointer curr) {
  while (curr->left_ != &nil_) {
    if (isRed(curr))
      cache_red_ = curr;
    moveRedDirection(curr, curr->left_, curr->right_);
    curr = curr->left_;
  }
  return curr;
}

template <typename K, typename V, typename C, typename A, typename E>
typename rbtree<K, V, C, A, E>::node_pointer rbtree<K, V, C, A, E>::removeSearch(const key_type& k) {
  node_pointer curr     = root_;
  bool         to_left  = false;
  bool         to_right = false;

  while (curr != &nil_) {
    to_left  = comp_(k, extract_key_(curr->value_));
    to_right = comp_(extract_key_(curr->value_), k);

    if (isRed(curr))
      cache_red_ = curr;

    if (to_right) {  // function ..
      moveRedDirection(curr, curr->right_, curr->left_);
      curr = curr->right_;
    } else if (to_left) {
      moveRedDirection(curr, curr->left_, curr->right_);
      curr = curr->left_;
    } else
      return curr;
  }
  error_ = true;
  return &nil_;
}

template <typename K, typename V, typename C, typename A, typename E>
void rbtree<K, V, C, A, E>::fixRoot() {
  nil_.left_    = root_;
  nil_.right_   = leftMost(root_);
  root_->color_ = BLACK;
  cache_red_    = root_;
}

// Method End

// Interface

template <typename K, typename V, typename C, typename A, typename E>
typename rbtree<K, V, C, A, E>::node_reference rbtree<K, V, C, A, E>::insert(const value_type& v) {
  error_ = false;
  root_  = insert(root_, v);
  fixRoot();
  return *inserted_;
}

template <typename K, typename V, typename C, typename A, typename E>  // ?
typename rbtree<K, V, C, A, E>::node_reference rbtree<K, V, C, A, E>::insert(const value_type& v, node_pointer hint) {
  static_cast<void>(hint);
  error_ = false;
  root_  = insert(root_, v);
  fixRoot();
  return *inserted_;
}

template <typename K, typename V, typename C, typename A, typename E>
void rbtree<K, V, C, A, E>::remove(const key_type& k) {
  error_ = false;
  root_  = remove(root_, k);
  fixRoot();
}

template <typename K, typename V, typename C, typename A, typename E>
typename rbtree<K, V, C, A, E>::value_type& rbtree<K, V, C, A, E>::searchValue(const key_type& k) {
  error_ = false;

  node_pointer np = search(k);
  value_type   v(k, 0);
  if (error_) {
    root_ = insert(root_, v);
    np    = inserted_;
    fixRoot();
    error_ = true;
  }
  return np->value_;
}

template <typename K, typename V, typename C, typename A, typename E>
typename rbtree<K, V, C, A, E>::node_reference rbtree<K, V, C, A, E>::find(const key_type& k) {
  error_ = false;
  return *search(k);
}

template <typename K, typename V, typename C, typename A, typename E>
typename rbtree<K, V, C, A, E>::node_reference rbtree<K, V, C, A, E>::bound(const key_type& k) {
  node_pointer curr = root_;
  node_pointer prev = root_;
  while (curr != &nil_) {
    prev = curr;
    if (comp_(extract_key_(curr->value_), k))
      curr = curr->right_;
    else if (comp_(k, extract_key_(curr->value_)))
      curr = curr->left_;
    else
      return *curr;
  }
  return *prev;
}

// Interface End

}  // namespace ft

#endif  // rbtree_HPP