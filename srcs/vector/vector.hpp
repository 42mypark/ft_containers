#include <cstddef>
#include <limits>
#include <memory>
#include <stdexcept>

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
  typedef pointer                                iterator;  // ?
  typedef const_pointer                          const_iterator;
  typedef ft::reverse_iterator<iterator>         reverse_iterator;
  typedef ft::reverse_iterator<const_iterator>   const_reverse_iterator;

 protected:
  pointer        begin_;
  pointer        end_;
  pointer        capacity_;
  allocator_type alloc_;  // ?

 private:
  void expand(size_type new_cap) {
    pointer tmp = alloc_.allocate(new_cap);
    for (iterator it = begin_; it != end_; ++it) {
      tmp[it - begin_] = *it;
    }
    alloc_.deallocate(begin_, capacity_ - begin_);
    size_type old_end = end_ - begin_;
    begin_ = tmp;
    end_ = begin_ + old_end;
    capacity_ = begin_ + new_cap;
  }

 public:
  // Destructor & Constructor
  ~vector() { alloc_.deallocate(begin_, capacity_ - begin_); }
  vector() {  // 1
    begin_ = alloc_.allocate(0);
    end_ = begin_;
    capacity_ = begin_;
  }
  explicit vector(const allocator_type& alloc) : alloc_(alloc) {  // 2
    begin_ = alloc_.allocate(0);
    end_ = begin_;
    capacity_ = begin_;
  }
  explicit vector(size_type count, const T& value = T(),  // 3
                  const allocator_type& alloc = allocator_type())
      : alloc_(alloc) {
    begin_ = alloc_.allocate(count);
    for (end_ = begin_; end_ - begin_ < count; ++end_) {
      *end_ = value;
    }
    capacity_ = begin_ + count;
  }
  template <typename InputIt>
  vector(InputIt first, InputIt last, const allocator_type& alloc = allocator_type())
      : begin_(NULL), end_(NULL), capacity_(NULL), alloc_(alloc) {  // 5
    assign(first, last);
  }

  vector(const vector& other) : begin_(NULL), end_(NULL), capacity_(NULL) {  // 6
    assign(other.begin(), other.end());
  }
  vector(const vector& other, const allocator_type& alloc)
      : begin_(NULL), end_(NULL), capacity_(NULL), alloc_(alloc) {  // 7
    assign(other.begin(), other.end());
  }

  // Member function
  allocator_type get_allocator() const { return alloc_; }
  // assignment
  vector& operator=(const vector& other) {
    if (this != &other)
      assign(other.begin(), other.end());
    return (*this);
  }
  void assign(size_type count, const T& value) {
    if (capacity_ - begin_ < count) {
      pointer tmp = alloc_.allocate(count);
      alloc_.deallocate(begin_, capacity_ - begin_);
      begin_ = tmp;
      capacity_ = begin_ + count;
    }
    end_ = begin_;
    for (int i = 0; i < count; ++i) {
      *end_ = value;
      ++end_;
    }
  }
  template <typename InputIt>
  void assign(InputIt first, InputIt last) {
    size_type count = last - first;
    if (capacity_ - begin_ < count) {
      pointer tmp = alloc_.allocate(count);
      alloc_.deallocate(begin_, capacity_ - begin_);
      begin_ = tmp;
      capacity_ = begin_ + count;
    }
    end_ = begin_;
    for (; first != last; ++first) {
      *end_ = *first;
      ++end_;
    }
  }

  // Element access memeber function
  reference at(size_type pos) {
    if (pos >= size())
      throw std::out_of_range("ft::vector.at() : out of range");
    return *(begin_ + pos);
  }
  const_reference at(size_type pos) const {
    if (pos >= size())
      throw std::out_of_range("ft::vector.at() : out of range");
    return *(begin_ + pos);
  }
  reference       operator[](size_type pos) { return *(begin_ + pos); }
  const_reference operator[](size_type pos) const { return *(begin_ + pos); }
  reference       front() { return *begin_; }
  const_reference front() const { return *begin_; }
  reference       back() { return *(end_ - 1); }
  const_reference back() const { return *(end_ - 1); }
  T*              data() { return begin_; }
  const T*        data() const { return begin_; }

  // Iterator
  iterator               begin() { return begin_; }
  const_iterator         begin() const { return begin_; }
  iterator               end() { return end_; }
  const_iterator         end() const { return end_; }
  reverse_iterator       rbegin() { return static_cast<reverse_iterator>(end_); }
  const_reverse_iterator rbegin() const { return static_cast<const_reverse_iterator>(end_); }
  reverse_iterator       rend() { return static_cast<reverse_iterator>(begin_); }
  const_reverse_iterator rend() const { return static_cast<const_reverse_iterator>(begin_); }

  // Capacity
  bool      empty() const { return end_ == begin_; }
  size_type size() const { return end_ - begin_; }
  size_type max_size() const { return std::numeric_limits<difference_type>::max(); }
  size_type capacity() const { return capacity_ - begin_; }

  void reserve(size_type new_cap) {
    if (capacity_ - begin_ >= new_cap)
      return;
    pointer tmp = alloc_.allocate(new_cap);
    for (iterator it = begin_; it != end_; ++it) {
      tmp[it - begin_] = *it;
    }
    alloc_.deallocate(begin_, capacity_ - begin_);
    end_ = tmp + (end_ - begin_);
    begin_ = tmp;
    capacity_ = begin_ + new_cap;
  }

  // Modifiers
  void clear() { end_ = begin_; }

  // insert
  iterator insert(iterator pos, const T& value) {
    int index = pos - begin_;
    if (end_ == capacity_) {
      size_type old_cap = capacity_ - begin_;
      size_type needed = 1;
      size_type new_cap = old_cap * 2 > needed ? old_cap * 2 : needed;
      expand(new_cap);
    }
    pos = begin_ + index;
    for (iterator it = end_ - 1; it != pos - 1; --it) {
      *(it + 1) = *it;
    }
    ++end_;
    *pos = value;
    return pos;
  }
  void insert(iterator pos, size_type count, const T& value) {
    if (count == 0)
      return;
    int index = pos - begin_;
    if (end_ + count > capacity_) {
      size_type old_cap = capacity_ - begin_;
      size_type needed = capacity_ - begin_ + count;
      size_type new_cap = old_cap * 2 > needed ? old_cap * 2 : needed;
      expand(new_cap);
    }
    pos = begin_ + index;
    for (iterator it = end_ - 1; it != pos - 1; --it) {
      *(it + count) = *it;
    }
    for (iterator it = pos; it != pos + count; ++it) {
      *it = value;
    }
    end_ += count;
  }
  template <class InputIt>
  void insert(iterator pos, InputIt first, InputIt last) {  // if last < first?
    size_type count = last - first;
    if (count == 0 || last < first)
      return;
    int index = pos - begin_;
    if (end_ + count > capacity_) {
      size_type old_cap = capacity_ - begin_;
      size_type needed = capacity_ - begin_ + count;
      size_type new_cap = old_cap * 2 > needed ? old_cap * 2 : needed;
      expand(new_cap);
    }
    pos = begin_ + index;
    for (iterator it = end_ - 1; it != pos - 1; --it) {
      *(it + count) = *it;
    }
    for (int i = 0; i < count; ++i) {
      *(pos + i) = *(first + i);
    }
    end_ += count;
  }

  // erase
  iterator erase(iterator pos) {
    for (iterator it = pos; it + 1 != end_; ++it) {
      *it = *(it + 1);
    }
    --end_;
    return pos;
  }
  iterator erase(iterator first, iterator last) {
    if (first >= last)
      return last;
    int i;
    for (i = 0; last + i != end_; ++i) {
      *(first + i) = *(last + i);
    }
    end_ = first + i;
    return first;
  }

  void push_back(const T& value) {
    if (end_ == capacity_) {
      size_type old_cap = capacity_ - begin_;
      size_type needed = 1;
      size_type new_cap = old_cap * 2 > needed ? old_cap * 2 : needed;
      expand(new_cap);
    }
    *end_ = value;
    ++end_;
  }
  void pop_back() { --end_; }

  void resize(size_type count, T value = T()) {
    size_type old_cap = capacity_ - begin_;
    if (count > old_cap) {
      size_type new_cap = old_cap * 2 > count ? old_cap * 2 : count;
      expand(new_cap);
    } else if (count < end_ - begin_) {
      end_ = begin_ + count;
    }
    for (int i = end_ - begin_; i < count; ++i) {
      *(begin_ + i) = value;
      ++end_;
    }
  }

  void swap(vector& other) {
    vector tmp(other);
    other.clear();
    other.insert(other.begin(), begin_, end_);
    clear();
    insert(begin_, tmp.begin(), tmp.end());
  }

  template <typename Cont>
  void print_cont(const std::string& tag, Cont c) {
    std::cout << tag << ": ";
    for (typename Cont::iterator it = c.begin(); it != c.end(); ++it) {
      std::cout << *it << ' ';
    }
    std::cout << std::endl;
  }
};

// template <typename T, typename Alloc>
// bool operator==(const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs)
// {
// 	for (ft::vector<T, Alloc>::iterator li = lhs.begin(), ri = rhs.begin();)
// }

}  // namespace ft
