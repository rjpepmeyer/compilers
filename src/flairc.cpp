#include <fstream>
#include <iostream>
#include <string>
#include "compiler.hpp"
#include "scanner-utilities.cpp"
#include "token-utilities.cpp"
#include "scanner.cpp"
#include "parser.cpp"
#include "codegen.hpp"

using namespace std;

int main(int argc, char *argv[]) {
  // Main Variables
  Node * ast;
  tokenList * tokens;
  bool debug = false;
  int line = 0;

  // Main Code
  if(argc > 2) {
    cout << "Usage: <./flairc> <fileName>\n";
    return 1; }
  else {
    if((string(argv[1]) == "print-one.flr")||
       (string(argv[1]) == "print-one")) {
      // Populate Tokens
      tokens = scanner(argv[1]);
      // Populate AST
      if (parser(tokens, debug, &ast)){
        // Walk through AST and send the nodes for "print 1" to codegen
        ofstream tmFile("print-one.tm");
        registerRm(line," LDC    ",0,1,0," #Adds one to the register\n");
        line += 1;
        registerRo(line," OUT    ",0,0,0," #Prints 1\n");
        line += 1;
        registerRo(line," HALT   ",0,0,0," #Ends the TM code\n");
        return 0; }
      else {
        return 3; }
    } else {
      //Break program on anything that is not print-one
      cout << "Whoops, you entered a file other than print-one...\n";
      return 2; }}}
    
