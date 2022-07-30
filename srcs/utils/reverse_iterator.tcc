#include <iterator>

#include "iterator_traits.tcc"

namespace ft {

template <typename Iter>
class reverse_iterator {
 protected:
  Iter current_;

 public:
  // Types
  typedef Iter                                              iterator_type;
  typedef typename iterator_traits<Iter>::iterator_category iterator_category;
  typedef typename iterator_traits<Iter>::value_type        value_type;
  typedef typename iterator_traits<Iter>::difference_type   difference_type;
  typedef typename iterator_traits<Iter>::pointer           pointer;
  typedef typename iterator_traits<Iter>::reference         reference;

  // Constructor
  ~reverse_iterator() {}
  reverse_iterator() {}
  explicit reverse_iterator(iterator_type it) : current_(it) {}
  template <typename U>
  reverse_iterator(const reverse_iterator<U>& other) : current_(other.base()) {}
  template <typename U>
  reverse_iterator(const std::reverse_iterator<U>& other) : current_(other.base()) {}

  // Member function
  iterator_type base() const { return current_; }

  // Member operator
  template <typename U>
  reverse_iterator& operator=(const reverse_iterator<U>& other) {
    current_ = other.base();
    return (*this);
  }
  template <typename U>
  reverse_iterator& operator=(const std::reverse_iterator<U>& other) {
    current_ = other.base();
    return (*this);
  }

  reference operator*() const {
    Iter tmp = current_;
    return *(--tmp);
  }
  pointer operator->() const {
    Iter tmp = current_;
    return to_pointer(--tmp);
  }

  reference operator[](difference_type n) const { return *(*this + n); }

  reverse_iterator& operator++() {
    --current_;
    return *this;
  }

  reverse_iterator operator++(int) {
    reverse_iterator tmp = *this;
    --current_;
    return tmp;
  }

  reverse_iterator& operator--() {
    ++current_;
    return *this;
  }

  reverse_iterator operator--(int) {
    reverse_iterator tmp = *this;
    ++current_;
    return tmp;
  }

  reverse_iterator operator+(difference_type n) const { return reverse_iterator(current_ - n); }

  reverse_iterator operator-(difference_type n) const { return reverse_iterator(current_ + n); }

  reverse_iterator& operator+=(difference_type n) {
    current_ -= n;
    return *this;
  }

  reverse_iterator& operator-=(difference_type n) {
    current_ += n;
    return *this;
  }

 private:
  template <typename T>
  static T* to_pointer(T* p) {
    return p;
  }
  template <typename T>
  static pointer to_pointer(T t) {
    return t.operator->();
  }
};  // class reverse_iterator

// Non-member operators

template <typename Iter1, typename Iter2>
bool operator==(const reverse_iterator<Iter1>& lhs, const reverse_iterator<Iter2>& rhs) {
  return lhs.base() == rhs.base();
}

template <typename Iter1, typename Iter2>
bool operator!=(const reverse_iterator<Iter1>& lhs, const reverse_iterator<Iter2>& rhs) {
  return lhs.base() != rhs.base();
}

template <typename Iter1, typename Iter2>
bool operator>(const reverse_iterator<Iter1>& lhs, const reverse_iterator<Iter2>& rhs) {
  return lhs.base() < rhs.base();
}

template <typename Iter1, typename Iter2>
bool operator>=(const reverse_iterator<Iter1>& lhs, const reverse_iterator<Iter2>& rhs) {
  return lhs.base() <= rhs.base();
}

template <typename Iter1, typename Iter2>
bool operator<(const reverse_iterator<Iter1>& lhs, const reverse_iterator<Iter2>& rhs) {
  return lhs.base() > rhs.base();
}

template <typename Iter1, typename Iter2>
bool operator<=(const reverse_iterator<Iter1>& lhs, const reverse_iterator<Iter2>& rhs) {
  return lhs.base() >= rhs.base();
}

template <typename Iter>
reverse_iterator<Iter> operator+(typename reverse_iterator<Iter>::difference_type n,
                                 const reverse_iterator<Iter>&                    it) {
  return reverse_iterator<Iter>(it.base() - n);
}

template <typename Iter>
typename reverse_iterator<Iter>::difference_type operator-(const reverse_iterator<Iter>& lhs,
                                                           const reverse_iterator<Iter>& rhs) {
  return rhs.base() - lhs.base();  //?
}

}  // namespace ft
