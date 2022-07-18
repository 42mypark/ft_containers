#define TITLE(S)                                               \
  std::cout << std::setfill('*') << std::setw(100) << '\n'     \
            << std::setfill(' ') << std::setw(50) << S << '\n' \
            << std::setfill('*') << std::setw(100) << '\n'     \
            << std::setfill(' ') << std::endl;

#define LABEL(X, Y)                                                            \
  std::cout << std::setw(15) << "LIB" << std::setw(3) << "**" << std::setw(10) \
            << X << std::setw(10) << "*" << std::setw(10) << Y                 \
            << std::setw(10) << "*" << std::setw(4) << "O/X" << std::endl;

#define ROW(CATEGORY, X, Y)                                                \
  std::cout << std::setw(15) << CATEGORY << std::setw(3) << "||"           \
            << std::setw(10) << X << std::setw(10) << "|" << std::setw(10) \
            << Y << std::setw(10) << "|" << std::setw(3)                   \
            << (X == Y ? "O" : "X") << std::endl;                          \
  assert(X == Y);
