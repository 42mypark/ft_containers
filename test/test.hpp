#ifndef test_HPP
#define test_HPP
template <class T>
class test {
 public:
  typedef T*       pointer;
  typedef const T* const_pointer;

 protected:
  const_pointer current_;

 public:
  ~test();
  test() : current_(0) {}
  test(const T& t) : current_(&t) {}
  test(const test& t) : current_(t.base()) {}
  test&         operator=(const test& t) { current_ = t.base(); }
  const_pointer base() const { return current_; }
  test          operator++(int) {
             test tmp = *current_;
             ++current_;
             return tmp;
  }
  const_pointer begin() {
    const_pointer tmp = current_;
    ++current_;
    return tmp;
  }
};

#endif  // test_HPP