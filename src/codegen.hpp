#include <string>
#include <iostream>
#include <sstream>

using namespace std;

/*
//PrintOneTM
const char printOneTM[] = "0: LDC  0,1(0)\n1: OUT  0,0,0\n2: HALT 0,0,0";

//PrintOneAST
const char printOneAST = 
   program main();
   begin
     return 1
   end.
*/

//Initialize values
string code, comment;
int r1, r2, r3, offset, line = 0;

void registerRo(int line, string code, int r1, int r2, int r3, string comment) {
    cout << line << ":" << code << r1 << "," << r2 << "," << r3 << "," << comment;
}

void registerRm(int line, string code, int r1, int offset, int r2, string comment) {
    cout << line << ":" << code << r1 << "," << offset << "(" << r2 << ")" << comment;
};

