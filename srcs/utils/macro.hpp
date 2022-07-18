#define TITLE(S)                                               \
  std::cout << std::setfill('*') << std::setw(50) << '\n'      \
            << std::setfill(' ') << std::setw(30) << S << '\n' \
            << std::setfill('*') << std::setw(50) << '\n'      \
            << std::setfill(' ') << std::endl;

#define LABEL(X, Y)                                                           \
  std::cout << std::setw(15) << "LIB" << std::setw(3) << "**" << std::setw(5) \
            << X << std::setw(5) << "*" << std::setw(5) << Y << std::setw(5)  \
            << "*" << std::setw(4) << "O/X" << std::endl;

#define ROW(CATEGORY, X, Y)                                                  \
  std::cout << std::setw(15) << CATEGORY << std::setw(3) << "||"             \
            << std::setw(5) << X << std::setw(5) << "|" << std::setw(5) << Y \
            << std::setw(5) << "|" << std::setw(3) << (X == Y ? "O" : "X")   \
            << std::endl;
