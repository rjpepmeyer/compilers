#include <string>
#include <iostream>
#include <sstream>

using namespace std;

//PrintOneTM
const char printOneTM[] = "0: LDC  0,1(0)\n1: OUT  0,0,0\n2: HALT 0,0,0";

//PrintOneAST
const char printOneAST = 1;

//Initialize values
std::string code, comment;
int r1, r2, r3, line;

void registerRo(string line, string code, int r1, int r2, int r3, string comment) {

    cout << line << "," << code << "," << r1 << "," << r2 << "," << r3 << "," << comment;
};
/*
class registerRm {
public:
  registerStr2 = r1+","+difference+"("+r2+")";
  void print() {
    cout<<line<<","<<code<<","<<registerStr2<<","<<comment
  }
};

//This is our print procedure
int hardCodeLine = 0;
void generatePrint(registerRm, registerRo) {
    registerRm(line,"LDC","0","1","0"," #Adds one to the register");
    line += 1;
    registerRo(line,"OUT",0,0,0," #Prints 1");
    line += 1;
    registerRo(line,"HALT",0,0,0," #Ends the TM code");
}
*/
