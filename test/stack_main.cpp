#include <cstdlib>
#include <ctime>
#include <iostream>
#include <stack>

#include "macro.hpp"
#include "stack.hpp"

namespace {

void MyTest() {
  TITLE("stack");
  SUBTITLE("interface");
  {
    ft::stack<int>  fs;
    std::stack<int> s;
    LABEL("ft", "std");
    std::cout << "* initial state *" << '\n';
    ROW("size ", fs.size(), s.size());
    ROW("empty", fs.empty(), s.empty());
    fs.push(123);
    s.push(123);
    std::cout << "* after push '123' *" << '\n';
    ROW("top  ", fs.top(), s.top());
    ROW("size ", fs.size(), s.size());
    ROW("empty", fs.empty(), s.empty());
    fs.pop();
    s.pop();
    std::cout << "* after pop *" << '\n';
    ROW("size ", fs.size(), s.size());
    ROW("empty", fs.empty(), s.empty());
  }
  std::cout << std::endl;

  SUBTITLE("Compare Operator Test");
  {
    std::cout << "=equal=" << '\n';
    {
      ft::stack<int>  fs1, fs2;
      std::stack<int> s1, s2;
      LABEL("ft", "std");
      ROW("eq", (fs1 == fs2), (s1 == s2));
      s1.push(10);
      fs1.push(10);
      ROW("eq", (fs1 == fs2), (s1 == s2));
      s2.push(10);
      fs2.push(10);
      ROW("eq", (fs1 == fs2), (s1 == s2));
    }
    std::cout << std::endl;

    std::cout << "=not equal=" << '\n';
    {
      ft::stack<int>  fs1, fs2;
      std::stack<int> s1, s2;
      LABEL("ft", "std");
      ROW("nq", (fs1 != fs2), (s1 != s2));
      s1.push(10);
      fs1.push(10);
      ROW("nq", (fs1 != fs2), (s1 != s2));
      s2.push(10);
      fs2.push(10);
      ROW("nq", (fs1 != fs2), (s1 != s2));
    }
    std::cout << std::endl;

    std::cout << "=greater=" << '\n';
    {
      ft::stack<int>  fs1, fs2;
      std::stack<int> s1, s2;
      LABEL("ft", "std");
      ROW("g", (fs1 > fs2), (s1 > s2));
      s1.push(10);
      fs1.push(10);
      ROW("g", (fs1 > fs2), (s1 > s2));
      s2.push(10);
      fs2.push(10);
      ROW("g", (fs1 > fs2), (s1 > s2));
    }
    std::cout << std::endl;

    std::cout << "=greater equal=" << '\n';
    {
      ft::stack<int>  fs1, fs2;
      std::stack<int> s1, s2;
      LABEL("ft", "std");
      ROW("ge", (fs1 >= fs2), (s1 >= s2));
      s1.push(10);
      fs1.push(10);
      ROW("ge", (fs1 >= fs2), (s1 >= s2));
      s2.push(10);
      fs2.push(10);
      ROW("ge", (fs1 >= fs2), (s1 >= s2));
    }
    std::cout << std::endl;

    std::cout << "=less=" << '\n';
    {
      ft::stack<int>  fs1, fs2;
      std::stack<int> s1, s2;
      LABEL("ft", "std");
      ROW("l", (fs1 < fs2), (s1 < s2));
      s1.push(10);
      fs1.push(10);
      ROW("l", (fs1 < fs2), (s1 < s2));
      s2.push(10);
      fs2.push(10);
      ROW("l", (fs1 < fs2), (s1 < s2));
    }
    std::cout << std::endl;

    std::cout << "=less equal=" << '\n';
    {
      ft::stack<int>  fs1, fs2;
      std::stack<int> s1, s2;
      LABEL("ft", "std");
      ROW("le", (fs1 <= fs2), (s1 <= s2));
      s1.push(10);
      fs1.push(10);
      ROW("le", (fs1 <= fs2), (s1 <= s2));
      s2.push(10);
      fs2.push(10);
      ROW("le", (fs1 <= fs2), (s1 <= s2));
    }
    std::cout << std::endl;
  }
}

}  // namespace

int main() { MyTest(); }