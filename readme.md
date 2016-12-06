Flair Compiler
==============
    
For Translation of Programming Languages CS 4550
    
**Contributors:**
* Keane Haase
* Chad Gilmer
* Devin Nemec
* Ronald Pepmeyer
    
Implementation language: C++ (at minimum, std=0x for some string methods)
    
**Scanner**
    
*Instructions:*
        
Compiling: `make flairs`
    
Running: `./flairs file-name.flr`
    
Produces as output a list of tokens, including the type of the token and the line number where it occured.
    
**Verifying parser**
    
*Instructions:*
        
Compiling: `make flairv`
    
Running: `./flairv file-name.flr`
    
Produces as output whether the input file represents a valid flair program, syntactically.
    
**Tree-producing parser**
    
*Instructions:*
        
Compiling: `make flairp`
    
Running: `./flairp file-name.flr`
    
Produces as output an abstract syntax tree representing the input program.

**Code generator**

*Instructions:*

Compiling: `make flairc`

Running: `./flairc flair-programs/file-name.flr' | './flairc flair-programs/file-name`

Produces as output TM code from the input flair program.
