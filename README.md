# brace-expansion
A brace expansion challenge project in C++

## Local dev setup
#### Dependencies
1. Bazel (tested on 4.0.0)
2. A C++ compiler

### Commands
```
bazel build //src/main:brace  : Build the program
bazel test //tests            : Run all tests
```

### Example Usage
```
echo "{A,B}{C,D}" | bazel-bin/src/main/brace
```

## About the tool
This program is designed to reproduce the brace expansion functionality of bash.

#### How it works
The program implements a recursive descent parser with three mutually recursive functions that operate on the grammar rules.  
The grammar rules follow the example input given, and more complex examples tested on bash.
