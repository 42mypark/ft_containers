#ifndef stack_HPP
#define stack_HPP

#include "vector.hpp"

namespace ft {

template <typename T, typename Cont = ft::vector<T> >
class stack {
  // Types
 public:
  typedef Cont                                  container_type;
  typedef typename Cont::value_type             value_type;
  typedef typename Cont::size_type              size_type;
  typedef typename Cont::reference              reference;
  typedef typename Cont::const_reference        const_reference;
  typedef typename Cont::iterator               iterator;
  typedef typename Cont::const_iterator         const_iterator;
  typedef typename Cont::reverse_iterator       reverse_iterator;
  typedef typename Cont::const_reverse_iterator const_reverse_iterator;

  // Member Variable
 protected:
  Cont c;

  // Destructor
 public:
  ~stack();

  // Constructor
 public:
  explicit stack(const Cont& cont = Cont());
  stack(const stack<T, Cont>& ms);

  // Interface
 public:
  stack<T, Cont>& operator=(const stack<T, Cont>& ms);
  void            pop();
  void            push(const value_type& value);
  reference       top();
  const_reference top() const;
  bool            empty() const;
  size_type       size() const;

  // friend Functions
  template <typename T1, class C1>
  friend bool operator==(const stack<T1, C1>& lhs, const stack<T1, C1>& rhs);

  template <typename T1, class C1>
  friend bool operator<(const stack<T1, C1>& lhs, const stack<T1, C1>& rhs);
};

template <typename T, typename Cont>
stack<T, Cont>::~stack() {}

template <typename T, typename Cont>
stack<T, Cont>::stack(const Cont& ct) : c(ct) {}

template <typename T, typename Cont>
stack<T, Cont>::stack(const stack<T, Cont>& ms) : c(ms.c) {}

template <typename T, typename Cont>
stack<T, Cont>& stack<T, Cont>::operator=(const stack<T, Cont>& ms) {
  this->c = ms.c;
  return *this;
}

template <typename T, typename Cont>
void stack<T, Cont>::pop() {
  c.pop_back();
}

template <typename T, typename Cont>
void stack<T, Cont>::push(const stack<T, Cont>::value_type& value) {
  c.push_back(value);
}

template <typename T, typename Cont>
typename stack<T, Cont>::reference stack<T, Cont>::top() {
  return *(c.rbegin());
}

template <typename T, typename Cont>
typename stack<T, Cont>::const_reference stack<T, Cont>::top() const {
  return *(c.rbegin());
}

template <typename T, typename Cont>
bool stack<T, Cont>::empty() const {
  return c.empty();
}

template <typename T, typename Cont>
typename stack<T, Cont>::size_type stack<T, Cont>::size() const {
  return c.size();
}

template <typename T, typename Cont>
bool operator==(const stack<T, Cont>& a, const stack<T, Cont>& b) {
  return a.c == b.c;
}

template <typename T, typename Cont>
bool operator!=(const stack<T, Cont>& a, const stack<T, Cont>& b) {
  return !(a == b);
}

template <typename T, typename Cont>
bool operator<(const stack<T, Cont>& a, const stack<T, Cont>& b) {
  return a.c < b.c;
}

template <typename T, typename Cont>
bool operator<=(const stack<T, Cont>& a, const stack<T, Cont>& b) {
  return !(b < a);
}

template <typename T, typename Cont>
bool operator>(const stack<T, Cont>& a, const stack<T, Cont>& b) {
  return b < a;
}

template <typename T, typename Cont>
bool operator>=(const stack<T, Cont>& a, const stack<T, Cont>& b) {
  return !(a < b);
}

}  // namespace ft

#endif  // stack_HPP