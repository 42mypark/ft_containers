#include <cassert>
#include <iomanip>
#include <iostream>
#include <type_traits>

#include "is_integral.hpp"
#include "macro.hpp"

class classA {
  int a;
  int b;
};

struct structA {
  int a;
  int b;
};

int main() {
  TITLE("is_integral");
  LABEL("std", "ft");
  ROW("bool", std::is_integral<bool>::value, ft::is_integral<bool>::value);
  ROW("char", std::is_integral<char>::value, ft::is_integral<char>::value);
  ROW("signed char", std::is_integral<signed char>::value, ft::is_integral<signed char>::value);
  ROW("unsigned char", std::is_integral<unsigned char>::value,
      ft::is_integral<unsigned char>::value);
  ROW("char16_t", std::is_integral<char16_t>::value, ft::is_integral<char16_t>::value);
  ROW("char32_t", std::is_integral<char32_t>::value, ft::is_integral<char32_t>::value);
  ROW("int", std::is_integral<int>::value, ft::is_integral<int>::value);
  ROW("unsigned int", std::is_integral<unsigned int>::value, ft::is_integral<unsigned int>::value);
  ROW("long", std::is_integral<long>::value, ft::is_integral<long>::value);
  ROW("unsigned long", std::is_integral<unsigned long>::value,
      ft::is_integral<unsigned long>::value);
  ROW("long long", std::is_integral<long long>::value, ft::is_integral<long long>::value);
  ROW("u long long", std::is_integral<unsigned long long>::value,
      ft::is_integral<unsigned long long>::value);
  ROW("class", std::is_integral<classA>::value, ft::is_integral<classA>::value);
  ROW("struct", std::is_integral<structA>::value, ft::is_integral<structA>::value);
}
