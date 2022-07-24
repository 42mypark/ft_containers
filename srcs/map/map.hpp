#include <memory>

#include "pair.hpp"
#include "reverse_iterator.tcc"

namespace ft {

template <class Key, class T, class Compare = std::less<Key>,
          class Allocator = std::allocator<ft::pair<const Key, T> > >
class map {
 public:
  typedef Key                                    key_type;
  typedef T                                      mapped_type;
  typedef std::pair<const Key, T>                value_type;
  typedef std::size_t                            size_type;
  typedef std::ptrdiff_t                         difference_type;
  typedef Compare                                key_compare;
  typedef Allocator                              allocator_type;
  typedef value_type&                            reference;
  typedef const value_type&                      const_reference;
  typedef typename allocator_type::pointer       pointer;
  typedef typename allocator_type::const_pointer const_pointer;
  // typedef ft::tree_iterator<value_type>          iterator;
  // typedef ft::tree_const_iterator<value_type>    const_iterator;
  // typedef ft::reverse_iterator<iterator>         reverse_iterator;
  // typedef ft::reverse_iterator<const_iterator>   const_reverse_iterator;
};

}  // namespace ft

#include <map>

std::map<int, int> m;
