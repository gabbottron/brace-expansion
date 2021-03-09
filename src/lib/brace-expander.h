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

    // convenience functions
    static bool isValid(char c);
    static bool isAlpha(char c);
    bool endOfExpr();
    char peek();
    char readNextChar();
    std::string readLetters();

    // validates input statement, throws if invalid
    static void validateStatement(std::string s);
    
    // simple combine of two string lists
    static std::vector<std::string> combine(std::vector<std::string> left, std::vector<std::string> right);

    // functions for recursive descent parser
    std::vector<std::string> parseComponentPart();
    std::vector<std::string> parseComponent();
    std::vector<std::string> parseExpression();
};

#endif
