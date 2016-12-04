#include <string>
#include <iostream>
#include <sstream>
#include "ast-utilities.cpp"

using namespace std;

/*
//PrintOneAST
const char printOneAST = 
   program main();
   begin
     return 1
   end.
*/

void printOne(Node ** ast) {
  // Sort through an AST
  for (const Node &ast : ast){
    // Find the print node
    cout << "Node\n";
    
    // Send info from print node to regRo and regRm
    
  }
}

void registerRo(int line, string code, int r1, int r2, int r3, string comment) {
    cout << line << ":" << code << r1 << "," << r2 << "," << r3 << "," << comment;
}

void registerRm(int line, string code, int r1, int offset, int r2, string comment) {
    cout << line << ":" << code << r1 << "," << offset << "(" << r2 << ")" << comment;
};

