===============================================
    
For Translation of Programming Languages CS 4550
    
================================================

**Contributors:**
* Keane Haase
* Chad Gilmer
* Devin Nemec
* Ronald Pepmeyer
    
Implementation language: C++ (at minimum, std=0x for some string methods)
    
Basic Description of the Project: 

  It compiles flair programs to an abstract syntax tree, and a subset of those programs to TM assembly code.

Features Not Implemented:

  Function calls, if statement, command line arguments, outputing to file (as opposed to std output), boolean comparisons.
  Working features include returning the result of binary arithmetic expressions (e.g. 1 + 2 * 3).

List of Known Bugs:

  N/A

Optimizations Implemented:

  N/A

How to build our compiler:

  make clean 
  make flairc

How to run compiler:
 
   ./flairc test-programs/<input file>
