#include <string>
#include <iostream>
#include <sstream>

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
//  for (const Node &ast : ast){ //method one
//  for (unsigned int i=0;i< sizeof(ast)/sizeof(ast[0]);i=i+1){ //method two
    //ast[0]->print(0);
    ast[0]->printTM();
    // Find the print node
    
    
    // Send info from print node to regRo and regRm
    

}

void registerRo(int line, string code, int r1, int r2, int r3, string comment) {
    cout << line << ":" << code << r1 << "," << r2 << "," << r3 << "," << comment;
}

void registerRm(int line, string code, int r1, int offset, int r2, string comment) {
    cout << line << ":" << code << r1 << "," << offset << "(" << r2 << ")" << comment;
};

