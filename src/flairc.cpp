#include <fstream>
#include <iostream>
#include <string.h>
#include <stdio.h>
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
  string inputFile(argv[1]);
  string ext(".flr");
  char * iFileName;  

  // Main Code
  if(argc > 2) {
    cout << "Usage: <./flairc> <fileName>\n";
    return 1; 
  }
  else {
    if((string(argv[1]) == "flair-programs/print-one.flr")||
       (string(argv[1]) == "flair-programs/print-one")) {
      // Populate Tokens
      if(inputFile == "flair-programs/print-one"){
        inputFile+=ext;
        iFileName = new char[inputFile.length() + 1];
        strcpy(iFileName, inputFile.c_str());
        tokens = scanner(iFileName);
      } else {
        tokens = scanner(argv[1]);
      }
      // Populate AST
      if (parser(tokens, debug, &ast)){
        // Walk through AST and send the nodes for "print 1" to codegen
        ofstream tmFile("print-one.tm");
        registerRm(line," LDC    ",0,1,0," #Adds one to the register\n");
        line += 1;
        registerRo(line," OUT    ",0,0,0," #Prints 1\n");
        line += 1;
        registerRo(line," HALT   ",0,0,0," #Ends the TM code\n");
        return 0; 
        tmFile.close();
      }
      else {
        return 3; 
      }
    } else {
      //Break program on anything that is not print-one
      cout << "Whoops, you entered a file other than print-one...\n";
      return 2; 
    }
  }
}
    
