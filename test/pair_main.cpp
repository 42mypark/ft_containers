#include <iostream>
#include <utility>

#include "macro.hpp"
#include "pair.hpp"

template <typename T>
void print_pair(const std::string& tag, T p) {
  std::cout << tag << ": " << p.first << ", " << p.second << std::endl;
}

int main() {
  TITLE("pair");
  {
    SUBTITLE("CONSTRUCTOR-1");
    std::pair<int, int> sp;
    ft::pair<int, int>  fp;

    print_pair("std", sp);
    print_pair("ft ", fp);
  }

  {
    SUBTITLE("CONSTRUCTOR-2");
    std::pair<int, int> sp(1, 2);
    ft::pair<int, int>  fp(1, 2);

    print_pair("std", sp);
    print_pair("ft ", fp);
  }

  {
    SUBTITLE("CONSTRUCTOR-3");
    std::pair<int, int> sp(1, 2);
    ft::pair<int, int>  fp(1, 2);

    std::pair<int, int> sp1(sp);
    ft::pair<int, int>  fp1(fp);

    print_pair("std", sp1);
    print_pair("ft ", fp1);
  }

  {
    SUBTITLE("CONSTRUCTOR-4");
    std::pair<int, int> sp(1, 65);
    ft::pair<int, int>  fp(1, 65);

    std::pair<int, char> sp1(sp);
    ft::pair<int, char>  fp1(fp);

    print_pair("std", sp1);
    print_pair("ft ", fp1);
  }

  {
    SUBTITLE("operator=(cpa)");
    std::pair<int, int> sp(1, 65);
    ft::pair<int, int>  fp(1, 65);

    std::pair<int, int> sp1;
    ft::pair<int, int>  fp1;

    sp1 = sp;
    fp1 = fp;

    print_pair("std", sp1);
    print_pair("ft ", fp1);
  }

  {
    SUBTITLE("ft::make_pair");
    std::pair<int, int> sp;
    ft::pair<int, int>  fp;

    sp = std::make_pair(1, 2);
    fp = ft::make_pair(1, 2);

    print_pair("std", sp);
    print_pair("ft ", fp);
  }

  {
    SUBTITLE("operator==(eq)");
    std::pair<int, int> sp(1, 65);
    ft::pair<int, int>  fp(1, 65);
    std::pair<int, int> sp1(sp);
    ft::pair<int, int>  fp1(fp);
    std::pair<int, int> sp2(1, 64);
    ft::pair<int, int>  fp2(1, 64);

    LABEL("std", "ft");
    ROW("equal", (sp == sp1), (fp == fp1));
    ROW("equal", (sp == sp2), (fp == fp2));
  }

  {
    SUBTITLE("operator!=(not eq)");
    std::pair<int, int> sp(1, 65);
    ft::pair<int, int>  fp(1, 65);
    std::pair<int, int> sp1(sp);
    ft::pair<int, int>  fp1(fp);
    std::pair<int, int> sp2(1, 64);
    ft::pair<int, int>  fp2(1, 64);

    LABEL("std", "ft");
    ROW("not equal", (sp != sp1), (fp != fp1));
    ROW("not equal", (sp != sp2), (fp != fp2));
  }

  {
    SUBTITLE("operator<(l)");
    std::pair<int, int> sp(1, 65);
    ft::pair<int, int>  fp(1, 65);
    std::pair<int, int> sp1(2, 64);
    ft::pair<int, int>  fp1(2, 64);
    std::pair<int, int> sp2(1, 64);
    ft::pair<int, int>  fp2(1, 64);
    std::pair<int, int> sp3(sp);
    ft::pair<int, int>  fp3(fp);

    LABEL("std", "ft");
    ROW("less", (sp < sp1), (fp < fp1));
    ROW("less", (sp < sp2), (fp < fp2));
    ROW("less", (sp < sp3), (fp < fp3));
  }

  {
    SUBTITLE("operator<=(le)");
    std::pair<int, int> sp(1, 65);
    ft::pair<int, int>  fp(1, 65);
    std::pair<int, int> sp1(2, 64);
    ft::pair<int, int>  fp1(2, 64);
    std::pair<int, int> sp2(1, 64);
    ft::pair<int, int>  fp2(1, 64);
    std::pair<int, int> sp3(sp);
    ft::pair<int, int>  fp3(fp);

    LABEL("std", "ft");
    ROW("less equal", (sp <= sp1), (fp <= fp1));
    ROW("less equal", (sp <= sp2), (fp <= fp2));
    ROW("less equal", (sp <= sp3), (fp <= fp3));
  }

  {
    SUBTITLE("operator>(g)");
    std::pair<int, int> sp(1, 65);
    ft::pair<int, int>  fp(1, 65);
    std::pair<int, int> sp1(2, 64);
    ft::pair<int, int>  fp1(2, 64);
    std::pair<int, int> sp2(1, 64);
    ft::pair<int, int>  fp2(1, 64);
    std::pair<int, int> sp3(sp);
    ft::pair<int, int>  fp3(fp);

    LABEL("std", "ft");
    ROW("grater", (sp > sp1), (fp > fp1));
    ROW("grater", (sp > sp2), (fp > fp2));
    ROW("grater", (sp > sp3), (fp > fp3));
  }

  {
    SUBTITLE("operator>=(ge)");
    std::pair<int, int> sp(1, 65);
    ft::pair<int, int>  fp(1, 65);
    std::pair<int, int> sp1(2, 64);
    ft::pair<int, int>  fp1(2, 64);
    std::pair<int, int> sp2(1, 64);
    ft::pair<int, int>  fp2(1, 64);
    std::pair<int, int> sp3(sp);
    ft::pair<int, int>  fp3(fp);

    LABEL("std", "ft");
    ROW("grater equal", (sp >= sp1), (fp >= fp1));
    ROW("grater equal", (sp >= sp2), (fp >= fp2));
    ROW("grater equal", (sp >= sp3), (fp >= fp3));
  }
}
