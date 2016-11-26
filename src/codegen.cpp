#include <string>
#include <iostream>
#include <sstream>
#include "ast-utilities.cpp"

//PrintOneTM
const char *printOneTM = 
  "0: LDC  0,1(0)"
  "1: OUT  0,0,0"
  "2: HALT 0,0,0";

//PrintOneAST
const char printOneAST = ""
  ;

void registerRo(line,code,r1,r2,r3,comment = "") {
  registerStr = r1","r2","r3;
  cout << (line,code,registerStr,comment) <<}

void registerRm(line,code,r1,difference,r2,comment) {
  registerStr2 = r1","difference"("r2")";
  cout << (line,code,registerStr2,comment); }

//This is our print procedure
generatePrint(line, program) {
  for r in range(0,3);
    //generate code to prepare for code of left subtree
    //generateCode(tree.leftChild());
    //generate code to prepare for code of right subtree
    //generateCode(tree.rightChild());
    registerRm(line,"LDC","0","1","0","Adds one to the register");
    line += 1;
    registerRo(line,"OUT","0","0","0","Prints 1");
    line += 1;
    registerRo(line,"HALT","0","0","0","Halts the TM code"); }}
    //generate code to implement tree's behavior   

