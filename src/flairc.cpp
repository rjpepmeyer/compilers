#include <iostream>
#include <string>
#include "compiler.hpp"
#include "scanner-utilities.cpp"
#include "token-utilities.cpp"
#include "scanner.cpp"
#include "parser.cpp"

using namespace std;

int main(int argc, char *argv[]) {
  // Determine if debugging
  bool debug;
  debug = (argc >= 3);
  // Run scanner on input file
  tokenList * streamOfTokens = scanner(argv[1]);

  Node * ast;
  if (parser(streamOfTokens,debug,&ast)) {
    codeGen(ast);
  }
  else {
    cout << "Invalid flair program" << '\n';
  } 
}
