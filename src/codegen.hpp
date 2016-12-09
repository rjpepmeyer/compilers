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
    string off;
    string r2;
    string r3;
    stringstream ss;

    ast->makeTAC(&myTACs, &count);
    if (myTACs != NULL) {
      cout << " 0:  LDA 6,1(7) #Places the offset 1 into return address register 6\n" << 
              " 1:  LDA 7,5(0) #Places the offset 5 into program counter\n" <<
              " 3:  OUT 1,0,0  #Outputs the contects of register 1\n" <<
              " 4: HALT 0,0,0  #Ends the program\n";
      line = 5;
      //Move to function inside a loop to allow calling this switch on children
      switch (myTACs->getValue().getOp()) {      
        case t_ass :
          ss << myTACs->getValue().get1();
          off = ss.str();
          comment = " #Places the value " + off + " into register 2";
          registerRm(line," LDA",2,myTACs->getValue().get1(),0,comment);
          ss.str("");
          ss << count;
          off = ss.str();
          line++;
          comment = " #Stores the value of register 2 in dmem location " + off;
          registerRm(line,"  ST",2,count,0,comment);
          count++;
          comment = "\n";
          line++;
          break;
        case t_add :
/*
          ss << myTACs->getValue().get1();
	  off = ss.str();
          cout << myTACs->getValue().get1() << " offset value\n";
	  comment = " #places the value " + off + " into register 2";
	  registerRm(line," LDC",2,myTACs->getValue().get1(),0,comment);
	  line++;
          ss << myTACs->getValue().get2();
	  r2 = ss.str();
	  comment = " #Places the value " + r2 + " into register 3";
	  registerRm(line," LDC",3,myTACs->getValue().get2(),0,comment);
	  line++;
	  registerRo(line," ADD",1,2,3,comment);
	  line++;*/
          cout << "I haven't finished TM for t_add yet\n";
          break;
        case t_sub :
          cout << "I haven't implemented TM for t_sub yet\n";
          break;
        case t_mul :
          cout << "I haven't implemented TM for t_mul yet\n";
          break;
        case t_div :
          cout << "I haven't implemented TM for t_div yet\n";
          break;
        case t_neg :
          cout << "I haven't implemented TM for t_div yet\n";
          break;
        default:
          cout << "Codegen can't figure out the op type of the TAC\n";
        }
      comment = " #Loads the return address from reg 6 into the program counter";
      registerRm(line," LDA",7,0,6,comment);  
      count--; 
      cout << " 2:   LD 1," << count << "(0) #Loads the value stored in dmem " <<
              count << " to register 1\n";
    } else {
      cout << "Sad\n";
    }

}



