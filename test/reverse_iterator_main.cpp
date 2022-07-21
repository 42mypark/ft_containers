#include <cassert>
#include <complex>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <vector>

#include "macro.hpp"
#include "reverse_iterator.tcc"

int main() {
  TITLE("reverse_iterator");
  {
    SUBTITLE("CONSTRUCTOR");
    LABEL("std", "ft");

    int                          a[] = {1, 2, 3};
    ft::reverse_iterator<int *>  i;
    ft::reverse_iterator<int *>  ft_ai(a);
    std::reverse_iterator<int *> std_ai(a);
    ROW("constructor", *(--std_ai), *(--ft_ai));

    std::reverse_iterator<int *> std_ai2(std_ai);
    ft::reverse_iterator<int *>  ft_ai2(std_ai);
    ft::reverse_iterator<int *>  ft_ai3(ft_ai);
    ROW("copy cnstr", *std_ai2, *ft_ai2);
    ROW("copy cnstr", *std_ai2, *ft_ai3);
  }

  {
    SUBTITLE("MEMBER FUNCTION");
    LABEL("std", "ft");

    int                          a[] = {1, 2, 3};
    std::reverse_iterator<int *> std_ai(a);
    --std_ai;
    std::reverse_iterator<int *> std_ai_cpa = std_ai;
    ft::reverse_iterator<int *>  ft_ai_cpa = std_ai;
    ft::reverse_iterator<int *>  ft_ai_cpa2 = ft_ai_cpa;
    ROW("op=", *std_ai_cpa, *ft_ai_cpa);
    ROW("op=", *std_ai_cpa, *ft_ai_cpa2);

    std::vector<std::complex<double>> vc{{1, 2}, {3, 4}, {5, 6}, {7, 8}};
    std::reverse_iterator<std::vector<std::complex<double>>::iterator> std_r{vc.rbegin() + 1};
    ft::reverse_iterator<std::vector<std::complex<double>>::iterator>  ft_r{vc.rbegin() + 1};
    ROW("op->", std_r->real(), ft_r->real());
    ROW("op->", std_r->imag(), ft_r->imag());

    ROW("op[0]", std_r[0], ft_r[0]);
    ROW("op[1]", std_r[1], ft_r[1]);
    ROW("op[2]", std_r[2], ft_r[2]);
    ROW("op[-1]", std_r[-1], ft_r[-1]);
    std::cout << "~ out of range ~" << std::endl;
    ROW("op[3]", std_r[3], ft_r[3]);
    ROW("op[-2]", std_r[-2], ft_r[-2]);
    std::cout << "~ end ~" << std::endl;

    std::vector<int>                                  v{0, 1, 2, 3, 4};
    std::reverse_iterator<std::vector<int>::iterator> rv = v.rbegin();
    ft::reverse_iterator<std::vector<int>::iterator>  fv = v.rbegin();
    ROW("op++", *(++rv), *(++fv));
    ROW("op--", *(--rv), *(--fv));
    ROW("op+", *(rv + 3), *(fv + 3));
    rv += 3;
    fv += 3;
    ROW("op+=", rv[0], fv[0]);
    rv -= 3;
    fv -= 3;
    ROW("op-=", rv[0], fv[0]);
  }

  {
    SUBTITLE("NON MEMBER FUNCTION");
    LABEL("std", "ft");
    int a[]{0, 1, 2, 3};
    //             ↑  └───── x, y
    //             └──────── z

    std::reverse_iterator<int *> x{std::rbegin(a)}, y{std::rbegin(a)}, z{std::rbegin(a) + 1};
    ft::reverse_iterator<int *>  fx{std::rbegin(a)}, fy{std::rbegin(a)}, fz{std::rbegin(a) + 1};

    std::cout << std::boolalpha;
    ROW("op==", (x == y), (fx == fy));
    ROW("op!=", (x != y), (fx != fy));
    ROW("op< ", (x < y), (fx < fy));
    ROW("op<=", (x <= y), (fx <= fy));
    ROW("op==", (x == z), (fx == fz));
    ROW("op!=", (x != z), (fx != fz));
    ROW("op< ", (x < z), (fx < fz));
    ROW("op<=", (x <= z), (fx <= fz));

    std::vector<int>                                  v{0, 1, 2, 3};
    std::reverse_iterator<std::vector<int>::iterator> ri1 = v.rbegin();
    ft::reverse_iterator<std::vector<int>::iterator>  fi1 = v.rbegin();
    std::reverse_iterator<std::vector<int>::iterator> ri2{2 + ri1};
    ft::reverse_iterator<std::vector<int>::iterator>  fi2{2 + fi1};
    ROW("op+ ", *ri2, *fi2);

    std::reverse_iterator<std::vector<int>::iterator> ri3 = v.rbegin(), ri4 = v.rend();
    ft::reverse_iterator<std::vector<int>::iterator>  fi3 = v.rbegin(), fi4 = v.rend();
    ROW("op- ", (ri4 - ri3), (fi4 - fi3));
    ROW("op- ", (ri3 - ri4), (fi3 - fi4));
  }
}
