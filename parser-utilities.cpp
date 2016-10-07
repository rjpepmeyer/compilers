#include <string>

unsigned int table(tokenType row, token col) {
  switch (row) {
    case program:
      if (col.value == "program") return 1;
      else return 0;
    case definitions:
      if (col.value == "function") return 3;
      else if (col.value == "begin") return 2;
      else return 0;
    case def:
      if (col.value == "function") return 4;
      else return 0;
    case formals:
      if (col.value == ")") return 5;
      else if (col.type == identifier) return 6;
      else return 0;
    case nonemptyformals:
      if (col.value == ")" || col.type == identifier) return 7;
    case nonemptyformalsprime:
      if (col.value == ")") return 8;
      else if (col.value == ",") return 9;
      else return 0;
    case formal:
      if (col.type == identifier) return 10;
      else return 0;
    case body:
      if (col.value == "begin") return 11;
      else return 0;
    case statementlist:
      if (col.value == "return") return 13;
      else if (col.value == "print") return 12;
      else return 0;
    case typent:
      if (col.type == type || col.value == "integer") return 14;
      else if (col.type == type || col.value == "boolean") return 15;
      else return 0;
    case expr:
      if (col.value == "if" || col.value == "not" || 
      col.type == identifier || col.value == "number" ||
      col.value == "boolean" || col.value == "-" || 
      col.value == "(") return 17;
      else return 0;
    case exprprime:
      if (col.value == "<") return 18;
      else if (col.value == "=") return 19;
      else return 0;
    case simpleexpr:
      if (col.value == "if" || col.value == "not" || 
      col.type == identifier || col.value == "number" ||
      col.value == "boolean" || col.value == "-" || 
      col.value == "(") return 21;
      else return 0;
    case simpleexprprime:
      if (col.value == "or") return 22;
      else if (col.value == "+") return 23;
      else if (col.value == "-") return 24;
      else return 0;
    case term:
      if (col.value == "if" || col.value == "not" || 
      col.type == identifier || col.value == "number" ||
      col.value == "boolean" || col.value == "-" || 
      col.value == "(") return 26;
      else return 0;
    case termprime:
      if (col.value == "and") return 27;
      else if (col.value ==  "*") return 28;
      else if (col.value == "/") return 29;
      else return 0;
    case factor:
      if (col.value == "if") return 30;
      else if (col.value == "not") return 31;
      else if (col.type == identifier) return 32;
      else if (col.type == type) return 33;
      else if (col.value == "-") return 34;
      else if (col.value == "(") return 35;
      else return 0;
    case factorprime:
      if (col.value == "end" || col.value == "then" || 
      col.value == "else" || col.value == "and" || col.value == "or" ||
      col.value == ")" || col.value == "<" || col.value == "=" ||
      col.value == "+" || col.value == "-" || col.value == "*" || 
      col.value == "/") return 36;
      else if (col.value == "(") return 37;
      else return 0;
    case actuals:
      if (col.value == ")") return 38;
      else  if (col.value == "if" || col.value == "not" || 
      col.value == "(" || col.value == "-" || col.type == identifier || 
      col.type == type) return 39;
      else return 0;
    default:
      return 0;
  }
}
