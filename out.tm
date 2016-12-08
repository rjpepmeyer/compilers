 0:  LDA 6,1(7) #Places the offset 1 into return address register 6
 1:  LDA 7,4(0) #Places the offset 4 into program counter
 2:  OUT 1,0,0  #Outputs the contects of register 1
 3: HALT 0,0,0  #Ends the program
 4:  LDC 1,0(0) #Places the offset 0 into register 1
 5:  LDA 7,0(6) #Loads the return address from reg 6 into the program counter
