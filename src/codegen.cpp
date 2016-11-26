#include <string>
#include <iostream>
#include <sstream>
#include "ast-utilities.cpp"

//PrintOneTMOutput
const char *printOneTM = 
  "0: LDC  0,1(0)"
  "1: OUT  0,0,0"
  "2: HALT 0,0,0";

const char printOneAST = 
  " ";

void register(line,code,r1,r2,r3,comment = "") {
  registerStr = r1","r2","r3;
  cout << (line,code,registerStr,comment) <<}

void register2(line,code,r1,difference,r2,comment) {
  registerStr2 = r1","difference"("r2")";
  cout << (line,code,registerStr2,comment); }

generateCode("AST Tree") {
  if("AST Tree" != null) {
    //generate code to prepare for code of left subtree
    generateCode(tree.leftChild());
    register;
    register2;
    //generate code to prepare for code of right subtree
    generateCode(tree.rightChild());
    register;
    register2;
    //generate code to implement tree's behavior }}


