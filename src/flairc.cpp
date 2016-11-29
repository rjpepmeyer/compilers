#include "codegen.hpp"
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

int main(int argc, char *argv[]) {
  string line;
  ifstream inputFile(argv[1]);
  if(inputFile) {
    while(1) {
      while(!inputFile.eof()) {
        getline(inputFile,line);
        if(line == "program main();") {
          cout << "It's working\n";
          return 0; }
        else {
          cout << "Nada\n";
          return 0; }}}}

  else {
    cout << "Please enter 'print-one.flr' for the file name!\n";
    return 0; }}
   
  
