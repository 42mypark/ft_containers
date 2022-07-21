#include <cstddef>
#include <limits>
#include <memory>

#include "reverse_iterator.tcc"

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
  typedef pointer                                iterator;
  typedef const_pointer                          const_iterator;
  typedef ft::reverse_iterator<iterator>         reverse_iterator;
  typedef ft::reverse_iterator<const_iterator>   const_reverse_iterator;

 protected:
  pointer begin_;
  pointer end_;
  pointer capacity_;

 public:
  // Destructor & Constructor
  ~vector() {
    allocator_type alloc;
    alloc.deallocate(begin_, capacity_ - begin_);
  }
  vector() : begin_(NULL), end_(NULL), capacity_(NULL) {
  }
  explicit vector(const allocator_type& alloc) {
    begin_ = alloc.allocate(0);
    end_ = begin_;
    capacity_ = begin_;
  }
  explicit vector(size_type count, const T& value = T(),
                  const allocator_type& alloc = allocator_type()) {
    begin_ = alloc.allocate(count);
    for (end_ = begin_; end_ - begin_ < count; ++end_) {
      *end_ = value;
    }
    capacity_ = begin_ + count;
  }
  explicit vector(size_type count) {
    allocator_type alloc;
    begin_ = alloc.allocate(count);
    end_ = begin_;
    capacity_ = begin_ + count;
  }
  template <typename InputIt>
  vector(InputIt first, InputIt last, const allocator_type& alloc = allocator_type()) {
    begin_ = alloc.allocate(last - first);
    end_ = begin_;
    for (; first != last; ++first) {
      *end_ = *first;
      ++end_;
    }
    capacity_ = end_;
  }
  vector(const vector& other) {
    allocator_type alloc;
    begin_ = alloc.allocate(other.capacity());
    end_ = begin_;
    for (iterator it = other.begin(); it != other.end(); ++it) {
      *end_ = *it;
      ++end_;
    }
    capacity_ = end_;
  }
  vector(const vector& other, const allocator_type& alloc) {
    begin_ = alloc.allocate(other.capacity());
    end_ = begin_;
    for (iterator it = other.begin(); it != other.end(); ++it) {
      *end_ = *it;
      ++end_;
    }
    capacity_ = end_;
  }

  // Member function
  vector&        operator=(const vector& other);
  allocator_type get_allocator() const;
  void           assign(size_type count, const T& value);
  template <typename InputIt>
  void assign(InputIt first, InputIt last);

  // Element access memeber function
  reference       at(size_type pos);
  const_reference at(size_type pos) const;
  reference       operator[](size_type pos);
  const_reference operator[](size_type pos) const;
  reference       front();
  const_reference front() const;
  reference       back();
  const_reference back() const;
  T*              data();
  const T*        data() const;

  // Iterator
  iterator               begin();
  const_iterator         begin() const;
  iterator               end();
  const_iterator         end() const;
  reverse_iterator       rbegin();
  const_reverse_iterator rbegin() const;
  reverse_iterator       rend();
  const_reverse_iterator rend() const;

  // Capacity
  bool      empty() const;
  size_type size() const;
  size_type max_size() const {
    return std::numeric_limits<difference_type>::max();
  }
  void      reserve(size_type new_cap);
  size_type capacity() const;

  // Modifiers
  void     clear();
  iterator insert(iterator pos, const T& value);
  void     insert(iterator pos, size_type count, const T& value);
  template <class InputIt>
  void     insert(iterator pos, InputIt first, InputIt last);
  iterator erase(iterator pos);
  iterator erase(iterator first, iterator last);
  void     push_back(const T& value);
  void     pop_back();
  void     resize(size_type count);
  void     resize(size_type count, T value = T());
};

}  // namespace ft

#include <vector>

std::vector<int> v;
