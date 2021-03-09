#ifndef LIB_BRACE_EXPANDER_H
#define LIB_BRACE_EXPANDER_H

#include <string>
#include <vector>

class BraceExpandr {
  public:
    BraceExpandr(std::string s);
    std::string getExpandedStatement();
  private:
    std::string statement;
    int nextCharIndex;

    static bool isValid(char c);
    static bool isAlpha(char c);
    bool endOfExpr();
    char peek();
    char readNextChar();
    std::string readLetters();

    static void validateStatement(std::string s);
    
    static std::vector<std::string> combine(std::vector<std::string> left, std::vector<std::string> right);

    std::vector<std::string> parseComponentPart();
    std::vector<std::string> parseComponent();
    std::vector<std::string> parseExpression();
};

#endif
