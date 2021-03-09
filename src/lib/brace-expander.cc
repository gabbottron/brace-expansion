#include "brace-expander.h"
#include <iostream>
#include <string>
#include <vector>

BraceExpandr::BraceExpandr(std::string s) {
  // debug
  //std::cout << "In BraceExpandr Constructor..." << std::endl;
  //std::cout << "Statement is: " << statement << std::endl;
  
  validateStatement(s);

  statement = s;
  nextCharIndex = 0;
}

bool BraceExpandr::isValid(char c) {
  int ascii_val = int(c);

  return ( (ascii_val == 123) || (ascii_val == 125) || (ascii_val == 44) || (ascii_val > 64 && ascii_val < 91) || (ascii_val > 96 && ascii_val < 123) );  
}

bool BraceExpandr::isAlpha(char c) {
  int ascii_val = int(c);

  return ( (ascii_val > 64 && ascii_val < 91) || (ascii_val > 96 && ascii_val < 123) );  
}

bool BraceExpandr::endOfExpr() {
  return nextCharIndex == statement.length();
}

char BraceExpandr::peek() {
  if(nextCharIndex == statement.length()) {
    return '\0';
  }
  return statement[nextCharIndex];
}

char BraceExpandr::readNextChar() {
  return statement[nextCharIndex++];
}

std::string BraceExpandr::readLetters() {
  std::string str;
  
  if(!isAlpha(peek())) {
    return str;
  }

  while(!endOfExpr()) {
    char ch = readNextChar();
    if(isAlpha(ch)) {
      str.push_back(ch);
    } else {
      nextCharIndex--;
      break;
    }
  }

  return str;
}

void BraceExpandr::validateStatement(std::string s) {
  int level = 0;
  // ASCII codes for validation
  // 65-90 Uppercase
  // 97-122 Lowercase
  // 123 {
  // 125 }
  // 44  ,
  for(int i = 0; i < s.length(); i++) {
    // debug
    //std::cout << s[i] << std::endl;
    
    // is the current character valid to use?
    if(!isValid(s[i])) {
      throw std::runtime_error("Found invalid character at position " + std::to_string(i));
    }
    // are there any misplaced commas?
    if(s[i] == ',') {
      // commas should only appear within braces
      if(level < 1) {
        throw std::runtime_error(", at position " + std::to_string(i) + " must be inside {}, statement invalid!");
      }
      // commas cannot end a substatement
      if(i > (s.length() - 2)) {
        throw std::runtime_error(", at position " + std::to_string(i) + " invalidates statement!");
      }
      // an alpha character must follow a comma
      if(!isAlpha(s[i+1])) {
        throw std::runtime_error(", at position " + std::to_string(i) + " must be followed by [A-Za-z] only, statement invalid!");
      }
    }
    // going up a level
    if(s[i] == '{') {
      // is this level properly formed?
      if(i > (s.length() - 3)) {
        throw std::runtime_error("Statement cannot contain empty or unclosed braces, found problem at position " + std::to_string(i) + "!");
      }
      // is this substatement empty?
      if(s[i+1] == '}') {
        throw std::runtime_error("Braces starting at position " + std::to_string(i) + " cannot be empty, statement invalid!");
      }
      level++;
    }
    // going down a level
    if(s[i] == '}') {
      level--;
    }
    if(level < 0) {
      throw std::runtime_error("Statement cannot have a negative level, found problem at position " + std::to_string(i) + "!");
    }
  }
  // are braces properly matched?
  if(level != 0) {
    throw std::runtime_error("Statement has mismatched number of braces, they must be equal. Statement invalid!");
  }
}


std::vector<std::string> BraceExpandr::combine(std::vector<std::string> left, std::vector<std::string> right) {
  std::vector<std::string> result;

  for(int i = 0; i < left.size(); i++) {
    for(int k = 0; k < right.size(); k++) {
      result.push_back(left[i] + right[k]);
    }
  }

  return result;
}

std::vector<std::string> BraceExpandr::parseExpression() {
  std::vector<std::string> result;

  while(!endOfExpr()) {
    std::vector<std::string> items = parseComponent();

    for(int i = 0; i < items.size(); i++) {
      result.push_back(items[i]);
    }

    if(peek() == ',') {
      // Skip comma
      readNextChar();
    } else {
      break;
    }
  }

  return result;
}

std::vector<std::string> BraceExpandr::parseComponent() {
  std::vector<std::string> leftItems;

  while(!endOfExpr()) {
    // parseComponentPart will return a list of strings (rightItems)
    // that must be combined with the already-parsed leftItems
    std::vector<std::string> rightItems = parseComponentPart();
    if(rightItems.size() == 0) {
      // no more parts, return current result (leftItems)
      break;
    }

    if(leftItems.size() == 0) {
      leftItems = rightItems;
    } else {
      leftItems = combine(leftItems, rightItems);
    }
  }

  return leftItems;
}

std::vector<std::string> BraceExpandr::parseComponentPart() {
  std::vector<std::string> result;
  char nextChar = peek();
  
  if(nextChar == '{') {
    // Skip '{'
    readNextChar();

    // Recursively parse the inner expression
    result = parseExpression();

    // Skip '}'
    readNextChar();
  }
  else if (isAlpha(nextChar)) {
    std::string letters = readLetters();

    if(letters.length() == 0) {
      return result;
    }

    std::vector<std::string> items{letters};

    result = items;
  }

  return result;
}

std::string BraceExpandr::getExpandedStatement() {
  std::string final_result;
  
  std::vector<std::string> result = parseExpression();

  for(int i = 0; i < result.size(); i++) {
    final_result.append(result[i]);
    if(i != (result.size() - 1)) {
      final_result.append(" ");
    }
  }

  return final_result;
}
