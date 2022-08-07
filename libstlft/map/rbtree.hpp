#ifndef rbtree_HPP
#define rbtree_HPP

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
  node*          nil_;
  node_pointer   root_;
  node_pointer   inserted_;
  node_allocator alloc_;
  bool           error_;
  Compare        comp_;
  Extract        extract_;

  // Method
 private:
  bool         isRed(node_pointer n) { return n->color_ == RED; }
  bool         isLeft(node_pointer n) { return n->parent_->left_ == n; }
  bool         isRight(node_pointer n) { return n->parent_->right_ == n; }
  size_type    countHeight(node_pointer np);
  void         colorFlip(node_pointer n);
  node_pointer rotateLeft(node_pointer np);
  node_pointer rotateRight(node_pointer np);
  node_pointer fixUp(node_pointer np);
  void         fixRoot();
  node_pointer insert(node_pointer np, const value_type& p);
  node_pointer moveRedRight(node_pointer np);
  node_pointer moveRedLeft(node_pointer np);
  node_pointer leftMost(node_pointer np);
  node_pointer rightMost(node_pointer np);
  node_pointer removeMin(node_pointer np);
  node_pointer remove(node_pointer np, const key_type& k);
  void         removeTree(node_pointer np);
  node_pointer search(const key_type& k);

  // Desturctor
 public:
  ~rbtree();

  // Constructor
 private:
  rbtree(const rbtree& t) { static_cast<void>(t); }

 public:
  rbtree() : nil_(NULL), root_(NULL), inserted_(NULL), error_(false), comp_(), extract_() {
    nil_ = alloc_.allocate(1);
    alloc_.construct(nil_, node(BLACK));
    root_        = nil_;
    nil_->left_  = nil_;
    nil_->right_ = nil_;
  }

  // Interface
 private:
  rbtree& operator=(const rbtree& t);

 public:
  node_reference       insert(const value_type& v);
  node_reference       insert(const value_type& v, node_pointer hint);
  void                 remove(const key_type& k);
  value_type&          searchValue(const key_type& k);
  node_reference       find(const key_type& k);
  node_reference       nil() { return *nil_; }
  const_node_reference nil() const { return *nil_; }
  node_reference       leftMost() { return *(nil_->right_); }
  const_node_reference leftMost() const { return *(nil_->right_); }
  bool                 error() { return error_; }
  node_reference       bound(const key_type& k);
  size_type            max_size() const { return std::numeric_limits<difference_type>::max() / sizeof(node); }
  void                 swap(rbtree& other);
  void                 clear();
};  // class rbtree

// Desturctor
template <typename K, typename V, typename C, typename A, typename E>
rbtree<K, V, C, A, E>::~rbtree() {
  removeTree(root_);
  alloc_.deallocate(nil_, 1);
  root_     = NULL;
  inserted_ = NULL;
  error_    = false;
}

template <typename K, typename V, typename C, typename A, typename E>
void rbtree<K, V, C, A, E>::clear() {
  removeTree(root_);
  root_        = nil_;
  nil_->left_  = nil_;
  nil_->right_ = nil_;
  inserted_    = NULL;
  error_       = false;
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
  while (np->left_ != nil_) {
    np = np->left_;
    ++count;
  }
  return count;
}

template <typename K, typename V, typename C, typename A, typename E>
typename rbtree<K, V, C, A, E>::node_pointer rbtree<K, V, C, A, E>::leftMost(node_pointer np) {
  while (np->left_ != nil_)
    np = np->left_;
  return np;
}
template <typename K, typename V, typename C, typename A, typename E>
typename rbtree<K, V, C, A, E>::node_pointer rbtree<K, V, C, A, E>::rightMost(node_pointer np) {
  while (np->right_ != nil_)
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
  if (np->right_ != nil_)
    np->right_->parent_ = np;
  return nr;
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
  if (np->left_ != nil_)
    np->left_->parent_ = np;
  return nl;
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

template <typename K, typename V, typename C, typename A, typename E>
typename rbtree<K, V, C, A, E>::node_pointer rbtree<K, V, C, A, E>::insert(node_pointer np, const value_type& p) {
  if (np == nil_) {
    inserted_ = alloc_.allocate(1);
    alloc_.construct(inserted_, node(p, *nil_));
    return inserted_;
  }
  if (comp_(extract_(p), extract_(np->value_))) {
    np->left_          = insert(np->left_, p);
    np->left_->parent_ = np;
  } else if (comp_(extract_(np->value_), extract_(p))) {
    np->right_          = insert(np->right_, p);
    np->right_->parent_ = np;
  } else {
    inserted_ = np;
    error_    = true;
  }
  return fixUp(np);
}

template <typename K, typename V, typename C, typename A, typename E>
typename rbtree<K, V, C, A, E>::node_pointer rbtree<K, V, C, A, E>::removeMin(node_pointer np) {
  if (np->left_ == nil_) {
    alloc_.deallocate(np, 1);
    return nil_;
  }
  if (np->left_ != nil_ && !isRed(np->left_) && !isRed(np->left_->left_))
    np = moveRedLeft(np);
  np->left_ = removeMin(np->left_);
  return fixUp(np);
}

template <typename K, typename V, typename C, typename A, typename E>
typename rbtree<K, V, C, A, E>::node_pointer rbtree<K, V, C, A, E>::remove(node_pointer np, const key_type& k) {
  if (np == nil_) {
    error_ = true;
    return nil_;
  }

  if (comp_(k, extract_(np->value_))) {
    if (np->left_ != nil_ && !isRed(np->left_) && !isRed(np->left_->left_))
      np = moveRedLeft(np);
    np->left_ = remove(np->left_, k);
  } else {
    bool same;
    if (isRed(np->left_))
      np = rotateRight(np);
    same = !comp_(extract_(np->value_), k);
    if (same && np->right_ == nil_) {
      alloc_.deallocate(np, 1);
      return nil_;
    }
    if (np->right_ != nil_ && !isRed(np->right_) && !isRed(np->right_->right_))
      np = moveRedRight(np);
    same = !comp_(extract_(np->value_), k);
    if (same) {
      node_pointer min = leftMost(np->right_);
      np->swap(*min, *nil_);
      np         = min;
      np->right_ = removeMin(np->right_);
    } else
      np->right_ = remove(np->right_, k);
  }
  return fixUp(np);
}

template <typename K, typename V, typename C, typename A, typename E>
void rbtree<K, V, C, A, E>::removeTree(node_pointer np) {
  if (np == nil_)
    return;
  removeTree(np->left_);
  removeTree(np->right_);
  alloc_.deallocate(np, 1);
}

template <typename K, typename V, typename C, typename A, typename E>
typename rbtree<K, V, C, A, E>::node_pointer rbtree<K, V, C, A, E>::search(const key_type& k) {
  node_pointer curr = root_;
  while (curr != nil_) {
    if (comp_(extract_(curr->value_), k))
      curr = curr->right_;
    else if (comp_(k, extract_(curr->value_)))
      curr = curr->left_;
    else
      return curr;
  }
  error_ = true;
  return nil_;
}

template <typename K, typename V, typename C, typename A, typename E>
void rbtree<K, V, C, A, E>::fixRoot() {
  nil_->left_   = root_;
  nil_->right_  = leftMost(root_);
  root_->color_ = BLACK;
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
  while (curr != nil_) {
    prev = curr;
    if (comp_(extract_(curr->value_), k))
      curr = curr->right_;
    else if (comp_(k, extract_(curr->value_)))
      curr = curr->left_;
    else
      return *curr;
  }
  return *prev;
}

template <typename K, typename V, typename C, typename A, typename E>
void rbtree<K, V, C, A, E>::swap(rbtree& other) {
  node_pointer n = nil_;
  nil_           = other.nil_;
  other.nil_     = n;

  node_pointer r = root_;
  root_          = other.root_;
  other.root_    = r;

  fixRoot();
  other.fixRoot();

  node_pointer i  = inserted_;
  inserted_       = other.inserted_;
  other.inserted_ = i;

  node_allocator a = alloc_;
  alloc_           = other.alloc_;
  other.alloc_     = a;

  C c         = comp_;
  comp_       = other.comp_;
  other.comp_ = c;

  E e            = extract_;
  extract_       = other.extract_;
  other.extract_ = e;
}

// Interface End

}  // namespace ft

#endif  // rbtree_HPP