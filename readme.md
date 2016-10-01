Flair Compiler
==============
    
For Translation of Programming Languages CS 4550
    
**Contributors:**
* Keane Haase
* Chad Gilmer
* Devin Nemec
* Ronald Pepmeyer
    
Implementation language: C++14
    
**Instructions**
    
1. Compile with `g++ -std=c++14 compiler.cpp -o flairs`
2. Run with `./flairs name-of-input-file.flr`
    
**Explanations**
This program takes as input a flair program and produces as 
output a list of tokens, each one starting with the line 
number, followed by the token type, and if applicable, the 
exact token. It processes the input character by character, 
separating sequences of characters based on white space and 
also self-deliminating tokens. There is a function 
isSelfDeliminator that returns if a character matches a 
single-character self deliminating token. The token 
type is returned by two functions titled getType (one for
 single character tokens and one for strings). It 
implements DFAs for the different token types using if/else 
structures (similar to a case structure, but supporting strings). 
    
The stream of tokens is returned from the scanner in the form of 
a linked list.
