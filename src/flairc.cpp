#include "codegen.hpp"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char *argv[]) {
  if(argc > 2) {
    cout << "Usage: <./flairc> <fileName>\n";
    return 0; }
  else {
    if(string(argv[1]) == "print-one.flr") {
      //Logic for Project 5      
      ofstream tmFile("print-one.tm");
      registerRm(line," LDC    ",0,1,0," #Adds one to the register\n");
      line += 1;
      registerRo(line," OUT    ",0,0,0," #Prints 1\n");
      line += 1;
      registerRo(line," HALT   ",0,0,0," #Ends the TM code\n");
      return 0;        
      }
    else if(string(argv[1]) == "print-one") {
      //Same logic as above, but allows for the removal of .flr
      ofstream tmFile("print-one.tm");
      registerRm(line," LDC    ",0,1,0," #Adds one to the register\n");
      line += 1;
      registerRo(line," OUT    ",0,0,0," #Prints 1\n");
      line += 1;
      registerRo(line," HALT   ",0,0,0," #Ends the TM code\n");
      return 0;
      }
    else {
      //Break program on anything that is not print-one
      cout << "Whoops, you entered a file other than print-one...\n"; }}}
    
