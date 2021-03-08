#include <iostream>
#include "src/lib/brace-expander.h"

int main()
{
  std::string input;
  std::cin >> input;
  
  try {
    BraceExpandr be(input);
    
    std::cout << be.getExpandedStatement() << std::endl;
  } catch(std::exception& e) {
    return EXIT_FAILURE;
  }
  
  return EXIT_SUCCESS;
}
