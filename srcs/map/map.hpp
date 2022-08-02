#ifndef MAP_hpp
#define MAP_hpp

#include <memory>

#include "lexicographical_compare.hpp"
#include "pair.hpp"
#include "rbtree.hpp"
#include "rbtree_const_iterator.hpp"
#include "rbtree_iterator.hpp"
#include "reverse_iterator.hpp"

namespace ft {

template <typename Key, typename T, typename Compare = std::less<Key>,
          typename Allocator = std::allocator<ft::pair<const Key, T> > >
class map {
 public:
  struct extractor;

 public:
  typedef Key                                                                  key_type;
  typedef T                                                                    mapped_type;
  typedef ft::pair<const Key, T>                                               value_type;
  typedef std::size_t                                                          size_type;
  typedef std::ptrdiff_t                                                       difference_type;
  typedef Compare                                                              key_compare;
  typedef Allocator                                                            allocator_type;
  typedef value_type&                                                          reference;
  typedef const value_type&                                                    const_reference;
  typedef typename allocator_type::pointer                                     pointer;
  typedef typename allocator_type::const_pointer                               const_pointer;
  typedef rbtree<key_type, value_type, key_compare, allocator_type, extractor> tree_type;
  typedef ft::rbtree_iterator<value_type>                                      iterator;
  typedef ft::rbtree_const_iterator<value_type>                                const_iterator;
  typedef ft::reverse_iterator<iterator>                                       reverse_iterator;
  typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

 public:
  struct extractor {
    const key_type& operator()(value_type& v) const { return v.first; }
    const key_type& operator()(const value_type& v) const { return v.first; }
  };

  struct value_compare {
    friend class map;

   protected:
    key_compare comp;
    value_compare(key_compare c) : comp(c) {}

   public:
    bool operator()(const value_type& v1, const value_type& v2) { return comp(v1.first, v2.first); }
  };

 protected:
  tree_type      tree_;
  size_type      size_;
  allocator_type alloc_;
  key_compare    comp_;
  value_compare  vc_;

 public:
  // Destructor & Constructor
  ~map() {}
  map() : size_(0), vc_(comp_) /*1*/ {}
  explicit map(const Compare& comp, const Allocator& alloc = Allocator())
      : size_(0), alloc_(alloc), comp_(comp), vc_(comp_) /*2*/ {}
  template <class InputIt>
  map(InputIt first, InputIt last, const Compare& comp = Compare(),
      const Allocator& alloc = Allocator())
      : size_(0), alloc_(alloc), comp_(comp), vc_(comp_) /*3*/ {
    insert(first, last);
  }
  map(const map& other) : size_(0), vc_(comp_) /*4*/ { insert(other.begin(), other.end()); }

  // Member Function
  map& operator=(const map& other) {
    clear();
    insert(other.begin(), other.end());
    return *this;
  }
  allocator_type get_allocator() const { return alloc_; }  // ?

  // Iterator
  iterator               begin() { return iterator(tree_.leftMost()); }
  iterator               end() { return iterator(tree_.nil()); }
  const_iterator         begin() const { return const_iterator(tree_.leftMost()); }
  const_iterator         end() const { return const_iterator(tree_.nil()); }
  reverse_iterator       rbegin() { return reverse_iterator(tree_.nil()); }
  reverse_iterator       rend() { return reverse_iterator(tree_.leftMost()); }
  const_reverse_iterator rbegin() const { return const_reverse_iterator(tree_.nil()); }
  const_reverse_iterator rend() const { return const_reverse_iterator(tree_.leftMost()); }

  // Capacity
  bool      empty() const { return size_ == 0; }
  size_type size() const { return size_; }
  size_type max_size() const { return tree_.max_size(); }

  // Element Access
  mapped_type& at(const key_type& key) {
    mapped_type& t = tree_.search_value(key).second;
    if (tree_.error())
      throw std::out_of_range("ft::map.at() : out of range");
    return t;
  }
  mapped_type& operator[](const key_type& key) { return tree_.search_value(key).second; }

  // Modifier
  void clear() {
    tree_.~rbtree();
    size_ = 0;
  }
  ft::pair<iterator, bool> insert(const value_type& value) /*1*/ {
    iterator it = tree_.insert(value);
    if (!tree_.error())
      ++size_;
    return ft::make_pair(it, !tree_.error());
  }
  iterator insert(iterator hint, const value_type& value) /*2*/ {
    iterator it = tree_.insert(value, hint.base());
    if (!tree_.error())
      ++size_;
    return it;
  }
  template <class InputIt>
  void insert(InputIt first, InputIt last) /*3*/ {
    for (; first != last; ++first) {
      tree_.insert(*first);
      if (!tree_.error())
        ++size_;
    }
  }
  void erase(iterator pos) /*1*/ {
    tree_.remove(pos->first);
    --size_;
  }
  void erase(iterator first, iterator last) /*2*/ {
    for (; first != last;) {  // ? range
      tree_.remove((first++)->first);
      --size_;
    }
  }
  size_type erase(const key_type& key) /*3*/ {
    tree_.remove(key);
    --size_;
    return !tree_.error();
  }
  void swap(map& other) {
    map tmp = other;
    other.clear();
    other.insert(begin(), end());
    clear();
    insert(tmp.begin(), tmp.end());
  }

  // Lookup
  iterator       find(const key_type& key) /*1*/ { return iterator(tree_.find(key)); }
  const_iterator find(const key_type& key) const /*2*/ { return const_iterator(tree_.find(key)); }

  size_type count(const key_type& key) {
    tree_.find(key);
    return !tree_.error();
  }

  iterator upper_bound(const key_type& key) /*1*/ {
    iterator it = tree_.bound(key);
    if (key < it->first)
      return it;
    else
      return ++it;
  }
  const_iterator upper_bound(const key_type& key) const /*2*/ {
    iterator it = tree_.bound(key);
    if (key < it->first)
      return it;
    else
      return ++it;
  }
  iterator lower_bound(const key_type& key) /*1*/ {
    iterator it = tree_.bound(key);
    if (it->first >= key)
      return it;
    else
      return ++it;
  }
  const_iterator lower_bound(const key_type& key) const /*2*/ {
    iterator it = tree_.bound(key);
    if (it->first >= key)
      return it;
    else
      return ++it;
  }
  ft::pair<iterator, iterator> equal_range(const key_type& key) /*1*/ {
    return ft::make_pair(lower_bound(key), upper_bound(key));
  }
  ft::pair<const_iterator, const_iterator> equal_range(const Key& key) const /*2*/ {
    return ft::make_pair(lower_bound(key), upper_bound(key));
  }
  // Observer
  key_compare   key_comp() const { return comp_; }
  value_compare value_comp() const { return vc_; }
};  // class map

// Non Member Function

template <class Key, class T, class Compare, class Alloc>
bool operator==(const ft::map<Key, T, Compare, Alloc>& lhs,
                const ft::map<Key, T, Compare, Alloc>& rhs) {
  if (lhs.size() != rhs.size())
    return false;
  typename ft::map<Key, T, Compare, Alloc>::iterator lit = lhs.begin();
  typename ft::map<Key, T, Compare, Alloc>::iterator rit = rhs.begin();
  for (; lit != lhs.end(); ++lit, ++rit) {
    if (lhs.value_comp()(*lit, *rit) != 0 || lhs.value_comp()(*rit, *lit) != 0)
      return false;
  }
  return true;
}

template <class Key, class T, class Compare, class Alloc>
bool operator!=(const ft::map<Key, T, Compare, Alloc>& lhs,
                const ft::map<Key, T, Compare, Alloc>& rhs) {
  return !(lhs == rhs);
}

template <class Key, class T, class Compare, class Alloc>
bool operator<(const ft::map<Key, T, Compare, Alloc>& lhs,
               const ft::map<Key, T, Compare, Alloc>& rhs) {
  return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template <class Key, class T, class Compare, class Alloc>
bool operator<=(const ft::map<Key, T, Compare, Alloc>& lhs,
                const ft::map<Key, T, Compare, Alloc>& rhs) {
  return !(rhs < lhs);
}

template <class Key, class T, class Compare, class Alloc>
bool operator>(const ft::map<Key, T, Compare, Alloc>& lhs,
               const ft::map<Key, T, Compare, Alloc>& rhs) {
  return rhs < lhs;
}

template <class Key, class T, class Compare, class Alloc>
bool operator>=(const ft::map<Key, T, Compare, Alloc>& lhs,
                const ft::map<Key, T, Compare, Alloc>& rhs) {
  return !(lhs < rhs);
}

template <class Key, class T, class Compare, class Alloc>
void swap(ft::map<Key, T, Compare, Alloc>& lhs, ft::map<Key, T, Compare, Alloc>& rhs) {
  lhs.swap(rhs);
}
}  // namespace ft

#endif  // MAP_hpp