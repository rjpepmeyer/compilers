#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>

using namespace std;

void registerRo(int line, string code, int r1, int r2, int r3, string comment) {
    cout << line << ":" << code << r1 << "," << r2 << "," << r3 << "," << 
      comment << '\n';
}

void registerRm(int line, string code, int r1, int offset, int r2, string comment) {
    cout << setw(2) << line << ": " << code << " " << r1 << "," << offset << "(" 
      << r2 << ")" << comment << '\n';
}

void codeGen(Node * ast) {
    TACs *myTACs = NULL;
    int count = 0;
    int line  = 0;
    string comment = "";
    ast->makeTAC(&myTACs, &count);
    if (myTACs != NULL) {
      cout << " 0:  LDA 6,1(7) #Places the address 1 into register 6\n" << 
              " 1:  LDA 7,4(0) #Places the address 4 into register 7\n" <<
              " 2:  OUT 1,0,0  #Outputs the contects of register 1\n" <<
              " 3: HALT 0,0,0  #Ends the program\n";
      line = 4;
      if (myTACs->getValue().getOp() == t_ass) {
        //comment = "#Placing the number " + 
        //           string(myTACs->getValue().get1()) + "into register 1\n";
        registerRm(line," LDC",1,myTACs->getValue().get1(),0,comment);
        line++;
      }
      registerRm(line," LDA",7,0,6,comment);
    }
    else {
      cout << "Sad\n";
    }
}



