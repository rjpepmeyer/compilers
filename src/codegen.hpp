#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>

using namespace std;

void registerRo(int line, string code, int r1, int r2, int r3, string comment) {
    cout << setw(2) << line << ": " << code << " " << r1 << "," << r2 << "," << r3 << 
      comment << '\n';
}

void registerRm(int line, string code, int r1, int offset, int r2, string comment) {
    cout << setw(2) << line << ": " << code << " " << r1 << "," << offset << "(" 
      << r2 << ")" << comment << '\n';
}

void codeGen(Node * ast) {
    // Register 1 = return value's dmem location
    // Register 6 = return address register
    // Register 7 = program counter

    TACs *myTACs = NULL;
    int count = 0;
    int line  = 0;
    string comment = "";
    string r1;
    int r1i;
    string off;
    int offi;
    string r2;
    int r2i;
    string r3;
    int r3i;
    stringstream ss;

    cout << " 0:  LDA 6,1(7) #Places line 2 into return address register 6\n" << 
            " 1:  LDA 7,4(0) #Places line 4 into program counter\n" <<
            " 2:  OUT 1,0,0  #Outputs the contects of register 1\n" <<
            " 3: HALT 0,0,0  #Ends the program\n";
    line = 4;

    ast->makeTAC(&myTACs, &count);
    while (myTACs != NULL) {
        cout << "*" << myTACs->getValue().getOp() << myTACs->getValue().get1() << myTACs->getValue().get2() << myTACs->getValue().getRes() << '\n';
      switch (myTACs->getValue().getOp()) {      
        case t_ass :
          cout << "* Processing an assignment\n";
          offi = myTACs->getValue().get1();
          ss << offi;
          off = ss.str();
          comment = " #Places the value " + off + " into register 2";
          registerRm(line," LDA",2,offi,0,comment);
          ss.str("");
          offi = myTACs->getValue().getRes();
          ss << offi;
          off = ss.str();
          line++;
          comment = " #Stores the value of register 2 in dmem location " + off;
          registerRm(line,"  ST",2,offi,0,comment);
          ss.str("");
          comment = "\n";
          line++;
          break;
        case t_add :
          ss.str("");
          r1i = myTACs->getValue().get1();
          ss << offi;
          off = ss.str();
          offi = myTACs->getValue().get2();
          ss.str("");
          r2i = myTACs->getValue().getRes();
          comment = "";
          registerRm(line, "  LD",2,r1i,0,comment);
          ss.str("");
          line++;
          registerRm(line, "  LD",3,offi,0,comment);
          ss.str("");
          line++;
          registerRo(line, " ADD",2,2,3,comment);
          ss.str("");
          line++;
          registerRm(line, "  ST",2,r2i,0,comment);
          ss.str("");
          line++;
          break;
        case t_mul :
          ss.str("");
          r1i = myTACs->getValue().get1();
          ss << offi;
          off = ss.str();
          offi = myTACs->getValue().get2();
          ss.str("");
          r2i = myTACs->getValue().getRes();
          comment = "";
          registerRm(line, "  LD",2,r1i,0,comment);
          ss.str("");
          line++;
          registerRm(line, "  LD",3,offi,0,comment);
          ss.str("");
          line++;
          registerRo(line, " MUL",2,2,3,comment);
          ss.str("");
          line++;
          registerRm(line, "  ST",2,r2i,0,comment);
          ss.str("");
          line++;
          break;
        case t_div :
          ss.str("");
          r1i = myTACs->getValue().get1();
          ss << offi;
          off = ss.str();
          offi = myTACs->getValue().get2();
          ss.str("");
          r2i = myTACs->getValue().getRes();
          comment = "";
          registerRm(line, "  LD",2,r1i,0,comment);
          ss.str("");
          line++;
          registerRm(line, "  LD",3,offi,0,comment);
          ss.str("");
          line++;
          registerRo(line, " DIV",2,2,3,comment);
          ss.str("");
          line++;
          registerRm(line, "  ST",2,r2i,0,comment);
          ss.str("");
          line++;
          break;
        case t_sub :
          r1i = myTACs->getValue().get1();
          offi = myTACs->getValue().get2();
          r2i = myTACs->getValue().getRes();
          comment = "";
          registerRm(line, "  LD",2,r1i,0,comment);
          ss.str("");
          line++;
          registerRm(line, "  LD",3,offi,0,comment);
          ss.str("");
          line++;
          registerRo(line, " SUB",2,2,3,comment);
          ss.str("");
          line++;
          registerRm(line, "  ST",2,r2i,0,comment);
          ss.str("");
          line++;
          break;
        case t_neg :
          cout << "*Negation TM not written yet\n";
          break;
        default:
          cout << "*Codegen can't figure out the op type of the TAC\n";
        }
      if (myTACs->getNext() == NULL) break;
      myTACs->increment();
    }
  comment = " #Puts the last saved number into register 1";
  registerRm(line,"  LD",1,count-1,0,comment);
  line++;
  comment = " #Loads the return address from reg 6 into the program counter";
  registerRm(line," LDA",7,0,6,comment);  
}



