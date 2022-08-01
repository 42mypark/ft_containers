#include <cassert>
#include <iomanip>
#include <iostream>
#include <type_traits>
#include <typeinfo>

#include "enable_if.hpp"
#include "macro.hpp"

struct structA {
  int a;
  int b;
};

class classA {
  int a;
  int b;
};

int main() {
  TITLE("enable_if");
  LABEL("std", "ft");
  ROW("bool", typeid(std::enable_if<true, bool>::type).name(),
      typeid(ft::enable_if<true, bool>::type).name());
  ROW("struct", typeid(std::enable_if<true, structA>::type).name(),
      typeid(ft::enable_if<true, structA>::type).name());
  ROW("class", typeid(std::enable_if<true, classA>::type).name(),
      typeid(ft::enable_if<true, classA>::type).name());
}
