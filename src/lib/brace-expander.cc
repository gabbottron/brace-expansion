#include "brace-expander.h"
#include <iostream>
#include <string>

BraceExpandr::BraceExpandr(std::string s) {
  // debug
  //std::cout << "In BraceExpandr Constructor..." << std::endl;
  //std::cout << "Statement is: " << statement << std::endl;
  
  validateStatement(s);

  statement = s;
}

void BraceExpandr::validateStatement(std::string s) {
  int level = 0;
  // ASCII codes for validation
  // 65-90 Uppercase
  // 97-122 Lowercase
  // 123 {
  // 125 }
  // 44  ,
  int ascii_val;
  for(int i = 0; i < s.length(); i++) {
    // debug
    //std::cout << s[i] << std::endl;
    
    ascii_val = int(s[i]);
    // is the current character valid to use?
    if( !( (ascii_val == 123) || (ascii_val == 125) || (ascii_val == 44) || (ascii_val > 64 && ascii_val < 91) || (ascii_val > 96 && ascii_val < 123) ) ) {
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
      ascii_val = int(s[i+1]);
      if( !((ascii_val > 64 && ascii_val < 91) || (ascii_val > 96 && ascii_val < 123)) ) {
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

std::string BraceExpandr::getExpandedStatement() {
  return statement;
}
