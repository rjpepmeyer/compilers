#include <string>
#include "parser-utilities.cpp"
#include "ast-utilities.cpp"

bool parser(tokenList * input, bool debug) {
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
  token A = parserStack.peek();
  token B = A; // last terminal
  while (A.type != eos) {
  //DEBUGGING
  if (debug) {
    cout << '\n' << "Top of stack " << toString(A.type) << " " << A.value 
    << '\n';
    cout << "Next token   " << toString(currentToken.type) << " " <<
    currentToken.value << '\n' << '\n';
  }
  
    if (isTerminal(A)) {
      if (parserStack.peek().type == currentToken.type ||
      parserStack.peek().value == currentToken.value) {
        //DEBUGGING
        if (debug) {
          cout << "POP AND ADVANCE" << '\n';
        }
        B = currentToken;
        parserStack.pop();
        stream.advance();
      } else {
        cout << "ERROR: encountered: " << 
        toString(currentToken.type) << currentToken.value << 
        '\n';
        cout << "But expected:       " << toString(A.type) << " " <<
        A.value << '\n';
        cout << " At line #" << currentToken.line << '\n';
        return false;
      }
    } else if (!isMake(A)) {
      A = parserStack.pop();
      //DEBUGGING
      if (debug) {
        cout << "IMPLEMENTING RULE " << table(A.type,currentToken) 
        << '\n';
      }
      switch (table(A.type,currentToken)) {
        case 1:
          parserStack.push(make(makeprogram));
          parserStack.push(make(".", punctuation));
          parserStack.push(make(body));
          parserStack.push(make(definitions));
          parserStack.push(make(";", terminator));
          parserStack.push(make(")", rightparen));
          parserStack.push(make(formals));
          parserStack.push(make("(", leftparen));
          parserStack.push(make(makeidentifier));
          parserStack.push(make(identifier));
          parserStack.push(make("program",keyword));
          break;
        case 2:
          parserStack.push(make(makedefs));
          break;
        case 3:
          parserStack.push(make(definitions));
          parserStack.push(make(def));
          break;
        case 4:
          parserStack.push(make(makedef));
          parserStack.push(make(";", terminator));
          parserStack.push(make(body));
          parserStack.push(make(typent));
          parserStack.push(make(":", separator));
          parserStack.push(make(")",rightparen));
          parserStack.push(make(formals));
          parserStack.push(make("(",leftparen));
          parserStack.push(make(makeidentifier));
          parserStack.push(make(identifier));
          parserStack.push(make("function",keyword));
          break;
        case 5:
          parserStack.push(make(makeformals));
          break;
        case 6:
          parserStack.push(make(nonemptyformals));
          break;
        case 7:
          parserStack.push(make(nonemptyformalsprime));
          parserStack.push(make(formal));
          break;
        case 8:
          parserStack.push(make(makeformals));
          break;
        case 9:
          parserStack.push(make(nonemptyformals));
          parserStack.push(make(",", comma));
          break;
        case 10:
          parserStack.push(make(makeformal));
          parserStack.push(make(typent));
          parserStack.push(make(":",separator));
          parserStack.push(make(makeidentifier));
          parserStack.push(make(identifier));
          break;
        case 11:
          parserStack.push(make(makebody));
          parserStack.push(make("end",keyword));
          parserStack.push(make(statementlist));
          parserStack.push(make("begin",keyword));
          break;
        case 12:
          parserStack.push(make(statementlist));
          parserStack.push(make(printstatement));
          break;
        case 13:
          parserStack.push(make(makestatements));
          parserStack.push(make(makereturn));
          parserStack.push(make(expr));
          parserStack.push(make("return",keyword));
          break;
        case 14:
          parserStack.push(make(maketype));
          parserStack.push(make("integer",type));
          break;
        case 15:
          parserStack.push(make(maketype));
          parserStack.push(make("boolean",type));
          break;
        case 16:
          parserStack.push(make(exprprime));
          parserStack.push(make(simpleexpr));
          break;
        case 17:
          break;
        case 18:
          parserStack.push(make(exprprime));
          parserStack.push(make(makebinexp));
          parserStack.push(make(simpleexpr));
          parserStack.push(make(makeoperator));
          parserStack.push(make("<",lessthan));
          break;
        case 19:
          parserStack.push(make(exprprime));
          parserStack.push(make(makebinexp));
          parserStack.push(make(simpleexpr));
          parserStack.push(make(makeoperator));
          parserStack.push(make("=",equals));
          break;
        case 20:
          parserStack.push(make(simpleexprprime));
          parserStack.push(make(term));
          break;
        case 21:
          break;
        case 22:
          parserStack.push(make(simpleexprprime));
          parserStack.push(make(makebinexp));
          parserStack.push(make(term));
          parserStack.push(make(makeoperator));
          parserStack.push(make("or",keyword));
          break;
        case 23:
          parserStack.push(make(simpleexprprime));
          parserStack.push(make(makebinexp));
          parserStack.push(make(term));
          parserStack.push(make(makeoperator));
          parserStack.push(make("+",op));
          break;
        case 24:
          parserStack.push(make(simpleexprprime));
          parserStack.push(make(makebinexp));
          parserStack.push(make(term));
          parserStack.push(make(makeoperator));
          parserStack.push(make("-",op));
          break;
        case 25:
          parserStack.push(make(termprime));
          parserStack.push(make(factor));
          break;
        case 26:
          break;
        case 27:
          parserStack.push(make(termprime));
          parserStack.push(make(makebinexp));
          parserStack.push(make(factor));
          parserStack.push(make(makeoperator));
          parserStack.push(make("and",keyword));
          break;
        case 28:
          parserStack.push(make(termprime));
          parserStack.push(make(makebinexp));
          parserStack.push(make(factor));
          parserStack.push(make(makeoperator));
          parserStack.push(make("*",op));
          break;
        case 29:
          parserStack.push(make(termprime));
          parserStack.push(make(makebinexp));
          parserStack.push(make(factor));
          parserStack.push(make(makeoperator));
          parserStack.push(make("/",op));
          break;
        case 30:
          parserStack.push(make(makeif));
          parserStack.push(make(expr));
          parserStack.push(make("else",keyword));
          parserStack.push(make(expr));
          parserStack.push(make("then",keyword));
          parserStack.push(make(expr));
          parserStack.push(make("if",keyword));
          break;
        case 31:
          parserStack.push(make(makenot));
          parserStack.push(make(factor));
          parserStack.push(make("not",keyword));
          break;
        case 32:
          parserStack.push(make(factorprime));
          parserStack.push(make(makeidentifier));
          parserStack.push(make(identifier));
          break;
        case 33:
          parserStack.push(make(literal));
          break;
        case 34:
          parserStack.push(make(makenegate));
          parserStack.push(make(factor));
          parserStack.push(make("-",op));
          break;
        case 35:
          parserStack.push(make(makeblock));
          parserStack.push(make(")",rightparen));
          parserStack.push(make(actuals));
          parserStack.push(make("(",leftparen));
          break;
        case 36:
          break;
        case 37:
          parserStack.push(make(makefncall));
          parserStack.push(make(")",rightparen));
          parserStack.push(make(actuals));
          parserStack.push(make("(",leftparen));
          parserStack.push(make(makestop));
          break;
        case 38:
          parserStack.push(make(makeexprs));
          break;
        case 39:
          parserStack.push(make(nonemptyactuals));
          break;
        case 40:
          parserStack.push(make(nonemptyactualsprime));
          parserStack.push(make(expr));
          break;
        case 41:
          parserStack.push(make(makeexprs));
          break;
        case 42:
          parserStack.push(make(nonemptyactuals));
          parserStack.push(make(",",comma));
          break;
        case 43:
          parserStack.push(make(makenumber));
          parserStack.push(make(number));
          break;
        case 44:
          parserStack.push(make(makeboolean));
          parserStack.push(make(booleanvalue));
          break;
        case 45:
          parserStack.push(make(makeprint));
          parserStack.push(make(";",terminator));
          parserStack.push(make(")",rightparen));
          parserStack.push(make(expr));
          parserStack.push(make("(",leftparen));
          parserStack.push(make("print",keyword));
          break;
        default: 
          cout << "ERROR at line #" << currentToken.line << " -- "
          << "unexpected " << toString(currentToken.type) << " " << 
          currentToken.value << '\n';
          return false; 
          break;
      }
    }
    else { // Semantic actions!
      parserStack.pop();  
    }
    //Advance stream
    A = parserStack.peek();
    currentToken = stream.item;
  }
  if (currentToken.type != eos) {
    cout << "ERROR at line #" << currentToken.line << " -- " <<
    "unexpected token " << toString(currentToken.type) << " " <<
    "at end of file." << '\n';
  }
  return (A.type == eos && currentToken.type == eos);
}
