#ifndef LIB_BRACE_EXPANDER_H
#define LIB_BRACE_EXPANDER_H

#include <string>

class BraceExpandr {
  public:
    BraceExpandr(std::string s);
    std::string getExpandedStatement();
  private:
    std::string statement;
    static void validateStatement(std::string);
};

#endif
