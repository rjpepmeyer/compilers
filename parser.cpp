#include <string>

unsigned int table(tokenType row, token col) {
  switch (row) {
    case program:
      if (col.value == "program") return 1;
      else return 0;
    case definitions:
      if (col.value == "function") return 3;
      else if (col.value = "begin") return 2;
      else return 0;
    case def:
      if (col.value == "function") return 4;
      else return 0;
    case formals:
      if (col.value == ")") return 5;
      if (col.type == identifier) return 6;
      else return 0;
    case nonemptyformals:
      if (col.value == ")" || col.type == identifier) return 7;
    case nonemptyformalsprime:
      if (col.value == ")") return 8;
      else if (col.value == "," return 9;
      else return 0;
    case formal:
      if (col.type == identifier) return 10;
      else return 0;
    case body:
      if (col.value == "begin") return 11;
      else return 0;
    case statementlist:
      if (col.value == "return") return 13;
      else (col.value == "print") return 12;
      else return 0;
    case typent:
      if (col.type == integer) return 14;
      else if (col.type == boolean) return 15;
      else return 0;
    case expr:
      if (col.value == "if" || col.value == "not" || 
      col.type == identifier || col.type == number ||
      col.type == boolean || col.value == "-" || 
      col.value = "(") return 17;
      else return 0;
    case exprprime:
      //TODO
      else return 0;
    case simpleexpr:
      if (col.value == "if" || col.value == "not" || 
      col.type == identifier || col.type == number ||
      col.type == boolean || col.value == "-" || 
      col.value = "(") return 21;
      else return 0;
    case simpleexprprime:
      //TODO
      else return 0;
    case term:
      if (col.value == "if" || col.value == "not" || 
      col.type == identifier || col.type == number ||
      col.type == boolean || col.value == "-" || 
      col.value = "(") return 26;
      else return 0;
    case termprime:
      //TODO
      else return 0;
    case factor:
      if (col.value == "if") return 30;
      if (col.value == "not") return 31;
      if (col.type == identifier) return 32;
      if (col.type == literal) return 33;
      if (col.value == "-") return 34;
      if (col.value == "(") return 35;
      else return 0;
    case factorprime:
      //TODO
      else return 0;
    case actuals:
      //TODO
      else return 0;
    default:
      return 0;
}

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
