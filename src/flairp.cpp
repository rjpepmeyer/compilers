#include <iostream>
#include <string>
#include "compiler.hpp"
#include "scanner-utilities.cpp"
#include "token-utilities.cpp"
#include "scanner.cpp"
#include "parser.cpp"

using namespace std;

int main(int argc, char *argv[]) {
  // Determine if debugging
  bool debug;
  debug = (argc >= 3);
  // Run scanner on input file
  tokenList * streamOfTokens = scanner(argv[1]);

  Node * ast;
  if (parser(streamOfTokens,debug,&ast)) {
    cout << "ABSTRACT SYNTAX TREE OF PROGRAM:\n\n";
    ast->print(0);
  }
  else {
    cout << "Invalid flair program" << '\n';
  } 

  /************************************
   *     Hard code print_one.flr      * 
   ***********************************/
  /*
  // Declarations
  ProgramNode    * program;
  IdentifierNode * program_name;
  BodyNode       * body;
  StatementList  * statement_list;
  PrintStmtNode  * return_statement;
  NumberNode     * return_value;

  // Build it
  return_value     = new NumberNode("1");
  return_statement = new PrintStmtNode(return_value);
  statement_list   = new StatementList(return_statement);
  body             = new BodyNode(statement_list);
  program_name     = new IdentifierNode("main");
  program          = new ProgramNode(program_name, NULL, NULL, body);
  program->print(0);
  */
  //TODO: Free memory from stream of tokens
  return 0;
}
