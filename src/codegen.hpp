#include <string>
#include <iostream>
#include <sstream>

using namespace std;

/*
//PrintOneTM
const char printOneTM[] = "0: LDC  0,1(0)\n1: OUT  0,0,0\n2: HALT 0,0,0";

//PrintOneAST
const char printOneAST = 1;
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

/*
//This is our print procedure
int main() {
    registerRm(line," LDC    ",0,1,0," #Adds one to the register\n");
    line += 1;
    registerRo(line," OUT    ",0,0,0," #Prints 1\n");
    line += 1;
    registerRo(line," HALT   ",0,0,0," #Ends the TM code\n");
    return 0;
};
*/

