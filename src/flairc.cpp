#include <iostream>
#include <string>
#include "compiler.hpp"
#include "scanner-utilities.cpp"
#include "token-utilities.cpp"
#include "scanner.cpp"
#include "parser.cpp"

using namespace std;

string inputFile;
string outputFile;
string alteredFile;

int main(int argc, char *argv[]) {

  inputFile = string(argv[1]);
  size_t extension = inputFile.find_last_of(".");
  alteredFile = inputFile.substr(0, extension);
  outputFile = alteredFile+".tm";
  cin >> outputFile;  
  
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
