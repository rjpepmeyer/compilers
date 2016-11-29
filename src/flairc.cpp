#include "codegen.hpp"

int main() {
    line = 0;
    registerRm(line," LDC    ",0,1,0," #Adds one to the register\n");
    line += 1;
    registerRo(line," OUT    ",0,0,0," #Prints 1\n");
    line += 1;
    registerRo(line," HALT   ",0,0,0," #Ends the TM code\n");
    return 0; }
