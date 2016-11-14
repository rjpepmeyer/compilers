#include <string>
#include "parser-utilities.cpp"
#include "ast-utilities.cpp"

bool parser(tokenList * input, bool debug, Node ** ast) {
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
  SemanticStack semStack;
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
        if (A.type == number || A.type == booleanvalue || A.type == typent || 
            A.type == identifier) {
          B = currentToken;
          if (debug) {
           cout << "\nTERMINAL VALUE ENCOUNTERED\n\n";
           print(B);
           cout << '\n';
          }
        }
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
          break;
        case 9:
          parserStack.push(make(nonemptyformals));
          parserStack.push(make(",", comma));
          break;
        case 10:
          parserStack.push(make(makeformal));
          parserStack.push(make(typent));
          parserStack.push(make(":",separator));
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
          parserStack.push(make(makebinexp));
          parserStack.push(make(exprprime));
          parserStack.push(make(simpleexpr));
          parserStack.push(make(makeoperator));
          parserStack.push(make("<",lessthan));
          break;
        case 19:
          parserStack.push(make(makebinexp));
          parserStack.push(make(exprprime));
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
          parserStack.push(make(makebinexp));
          parserStack.push(make(simpleexprprime));
          parserStack.push(make(term));
          parserStack.push(make(makeoperator));
          parserStack.push(make("or",keyword));
          break;
        case 23:
          parserStack.push(make(makebinexp));
          parserStack.push(make(simpleexprprime));
          parserStack.push(make(term));
          parserStack.push(make(makeoperator));
          parserStack.push(make("+",op));
          break;
        case 24:
          parserStack.push(make(makebinexp));
          parserStack.push(make(simpleexprprime));
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
          parserStack.push(make(makebinexp));
          parserStack.push(make(termprime));
          parserStack.push(make(factor));
          parserStack.push(make(makeoperator));
          parserStack.push(make("and",keyword));
          break;
        case 28:
          parserStack.push(make(makebinexp));
          parserStack.push(make(termprime));
          parserStack.push(make(factor));
          parserStack.push(make(makeoperator));
          parserStack.push(make("*",op));
          break;
        case 29:
          parserStack.push(make(makebinexp));
          parserStack.push(make(termprime));
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
      Node * node1;
      Node * node2;
      Node * node3;
      Node * node4;

      if (debug) {
        cout << "BEFORE SEMANTIC ACTION\n\n";
        semStack.peek()->print(0);
        cout << '\n';
      }
      switch(A.type) {
        case makeprogram:
          node4 = semStack.pop();
          node3 = semStack.pop();
          node2 = semStack.pop();
          node1 = semStack.pop();
          node1 = new ProgramNode(node1, node2, node3, node4);
          semStack.push(node1);
          *ast = node1;
          break;
        case makedef:
          node4 = semStack.pop();
          node3 = semStack.pop();
          node2 = semStack.pop();
          node1 = semStack.pop();
          node1 = new DefNode(node1, node2, node3, node4);
          semStack.push(node1);
          break;
        case makedefs:
          if (semStack.peek()->getType() == n_def) {
            node1 = new DefList(static_cast<DefNode*>(semStack.pop()));
            while(semStack.peek()->getType() == n_def) {
              node2 = semStack.pop();
              static_cast<DefList*>(node1)->add(static_cast<DefNode*>(node2));
            }
          }
          else {
            node1 = new DefList(NULL);
          }
          semStack.push(node1);
          break;
        case makeformal:
          node2 = semStack.pop();
          node1 = semStack.pop();
          node1 = new FormalParamNode(static_cast<IdentifierNode*>(node1),
              static_cast<TypeNode*>(node2));
          semStack.push(node1);
          break;
        case makeformals:
          if (semStack.peek()->getType() == n_formal) {
            node1 = new FormalList(static_cast<FormalParamNode*>(semStack.pop()));
            while(semStack.peek()->getType() == n_formal) {
              node2 = semStack.pop();
              static_cast<FormalList*>(node1)->
                add(static_cast<FormalParamNode*>(node2));
            }
          }
          else {
            node1 = new FormalList(NULL);
          }
          semStack.push(node1);
          break;
        case makebody:
          node1 = semStack.pop();
          node2 = new BodyNode(node1);
          semStack.push(node2);
          break;
        case makestatements:
          if (isStatement(semStack.peek()->getType())) {
            node1 = new StatementList(static_cast<StatementNode*>(semStack.pop()));
            while(isStatement(semStack.peek()->getType())) {
              node2 = semStack.pop();
              static_cast<StatementList*>(node1)->
                add(static_cast<StatementNode*>(node2));
            }
          }
          else {
            node1 = new StatementList(NULL);
          }
          semStack.push(node1);
          break;
        case makereturn:
          node1 = semStack.pop();
          node2 = new ReturnStmtNode(node1);
          semStack.push(node2);
          break;
        case makeexprs:
          if (isExpression(semStack.peek()->getType())) {
            node1 = new ExpressionList
              (static_cast<ExpressionNode*>(semStack.pop()));
            while(isExpression(semStack.peek()->getType())) {
              node2 = semStack.pop();
              static_cast<ExpressionList*>(node1)->
                add(static_cast<ExpressionNode*>(node2));
            }
          }
          else {
            node1 = new ExpressionList(NULL);
          }
          semStack.push(node1);
          break;
        case makefncall:
          node2 = semStack.pop();
          node1 = semStack.pop();
          node1 = new FunctionCallNode(static_cast<IdentifierNode*>(node1),
              static_cast<ExpressionList*>(node2));
          semStack.push(node1);
          break;
        case makeif:
          node3 = semStack.pop();
          node2 = semStack.pop();
          node1 = semStack.pop();
          node1 = new IfExprNode(static_cast<ExpressionNode*>(node1),
              static_cast<ExpressionNode*>(node2), 
              static_cast<ExpressionNode*>(node3));
          semStack.push(node1);
          break;
        case makenumber:
          node1 = new NumberNode(B.value);
          semStack.push(node1);
          break;
        case makeidentifier:
          node1 = new IdentifierNode(B.value);
          semStack.push(node1);
          break;
        case maketype:
          node1 = new TypeNode(B.type);
          semStack.push(node1);
        default:
          break;
      }
      if (debug) {
        cout << "APPLYING SEMANTIC ACTION\n\n";
        semStack.peek()->print(0);
        cout << '\n';
      }
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
