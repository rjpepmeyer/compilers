#include <string>
#include "parser-utilities.cpp"

bool parser(tokenList * input) {
  tokenList stream = *input;        // Input stream!
  token currentToken = stream.item; // Current token!
  tokenStack parserStack;           // Parser stack!
  token eosToken = make("", eos, 0); 
  token startToken = make("", program, 0);
  // Step 1
  parserStack.push(eosToken); // Push end of stream symbol
  // Step 2
  parserStack.push(startToken); // Push start symbol
  // Step 3
  while (currentToken.type != eos) {
    //TODO: all the logic

    //Advance stream
    stream.advance();
    currentToken = stream.item;
  }
  return false; // Obviously wrong placeholder return
}
