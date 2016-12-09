#include <string>
#include <iostream>
#include <sstream>
#include "tacClass.cpp"
#include "ast-utilities.hpp"
#include "codegen.hpp"

/* Index
   print Functions     Line 424
   makeTAC Functions   Line 534
*/

class TypeNode : public Node {
  protected:
    Node_Type   nt   = n_type;
    std::string name = "Type";
    std::string value;
  public:
    Node_Type getType() {return nt;}
    TypeNode() {
      value = "";
    }
    TypeNode(std::string val) {
      value = val;
    }
    void print(int d) {
      pad(d);
      cout << name << ": " << value << '\n';
    }
};

class BinaryOpNode : public Node {
  protected:
    std::string  name = "Binary Operator";
    Node_Type    nt   = n_operator; 
    std::string  value;
  public:
    Node_Type getType() {return nt;}
    BinaryOpNode(std::string val) {
      value = val;
    }
    BinaryOpNode() {}
    void print(int d) {
      pad(d);
      cout << name << ": " << value << '\n';
    }
    string getValue(){return value;}
};

class ProgramNode : public Node {
  protected:
    std::string     name = "Program";
    Node_Type       nt   = n_program;
    Node * value;
    Node * formals;
    Node * defs;
    Node * body;
  public:
    Node_Type getType() {return nt;}
    void setValue  (Node *i) {value   = i;};
    void setFormals(Node *i) {formals = i;};
    void setDefs   (Node *i) {defs    = i;};
    void setBody   (Node *i) {body    = i;};
    ProgramNode(Node * v, Node * f, Node * d, Node * b){
      setValue(v);
      setFormals(f);
      setDefs(d);
      setBody(b);
    }
    void print(int);
    void makeTAC(TACs**,int*);
};

class FormalParamNode : public Node {
  protected:
    std::string      name = "Formal Parameter";
    Node_Type        nt   = n_formal;
    Node * value;
    Node * type;
  public:
    Node_Type getType() {return nt;}
    void setValue(Node *i) {value = i;}
    void setType (Node *t) {type  = t;}
    FormalParamNode(Node * i, Node * t) {
      setValue(i);
      setType(t);
    }
    void print(int d);
};

class FormalList : public Node {
  protected:
    std::string      name = "Formal parameters";
    Node_Type        nt   = n_formals;
    FormalParamNode *value;
    FormalList      *next;
  public:
    Node_Type getType() {return nt;}
    FormalList(FormalParamNode *f, FormalList *n) {
      value = f;
      next  = n;
    }
    FormalList(FormalParamNode *f) {
      value = f;
      next  = NULL;
    }
    void add(FormalParamNode * f) {
      next  = new FormalList(value, next);
      value = f; 
    }
    void print(int d) {
      if (value != NULL) value->print(d);
      if (next != NULL)  next->print(d);
    }
};

class DefNode : public Node {
  protected:
    std::string      name = "Function definition";
    Node_Type        nt   = n_def;
    Node * value;
    Node * formals;
    Node * type;
    Node * body;
  public:
    Node_Type getType() {return nt;}
    void setValue  (Node *v) {value = v;};
    void setFormals(Node *f) {formals = f;};
    void setType   (Node *t) {type = t;};
    void setBody   (Node *b) {body = b;};
    DefNode(Node *v, Node *f, Node *t, Node *b) {
      setValue(v);
      setFormals(f);
      setType(t);
      setBody(b);
    }
    void print(int);
};

class DefList : public Node {
  protected:
    std::string  name = "Function definitions";
    Node_Type    nt   = n_defs;
    Node    *value;
    DefList *next;
  public:
    Node_Type getType() {return nt;}
    DefList(Node *v, DefList *n) {
      value = v;
      next = n;
    }
    DefList(Node *d) {
      value = d;
      next  = NULL;
    }
    void add(DefNode *d) {
      next  = new DefList(value, next);
      value = d; 
}
    void print(int d) {
      if (value != NULL) {(*value).print(d);}
      if (next  != NULL) { (*next).print(d);}
    }
};

class BodyNode : public Node {
  protected:
    std::string    name = "Body";
    Node_Type      nt   = n_body;
    Node *value;
  public:
    Node_Type getType() {return nt;}
    BodyNode(Node *s) {
      value = s;
    }
    void print(int);
    void makeTAC(TACs**,int*);
};

class StatementNode : public Node {
  protected:
    std::string      name;
    Node_Type        nt;
    ExpressionNode * value;
  public:
    Node_Type getType() {return nt;}
    void setValue(ExpressionNode *e) {value = e;}
    virtual void print(int) =0;
};

class PrintStmtNode : public StatementNode {
  protected:
    std::string     name = "Print statement";
    Node_Type       nt   = n_print;
    Node *value;
  public:
    Node_Type getType() {return nt;}
    void setValue(Node *e) {value = e;}
    PrintStmtNode (Node *e) {setValue(e);}
    void print(int);
};

class ReturnStmtNode : public StatementNode {
  protected:
    std::string     name = "Return statement";
    Node_Type       nt   = n_return;
    Node *value;
  public:
    Node_Type getType() {return nt;}
    void setValue(Node *e) {value = e;}
    ReturnStmtNode (Node *e) {setValue(e);}
    void print(int);
    void makeTAC(TACs**,int*);
};

class StatementList : public Node {
  protected:
    std::string    name = "Statement list";
    Node_Type      nt   = n_statements;
    StatementNode *value;
    StatementList *next;
  public:
    Node_Type getType() {return nt;}
    StatementList(StatementNode *v, StatementList *n) {
      value = v;
      next  = n;
    }
    StatementList(StatementNode *s) {
        value = s;
        next  = NULL;
    }
    void add(StatementNode *s) {
      next = new StatementList(value, next);
      value = s;
    }
    void print(int d) {
      if (value != NULL) {(*value).print(d);}
      if (next  != NULL) { (*next).print(d);}
    }
    void makeTAC(TACs**,int*);
};

class ExpressionNode : public Node {
  protected:
    std::string name;
    Node_Type   nt;
  public:
    Node_Type getType() {return nt;}
    virtual void print(int)=0;
};

class IdentifierNode : public ExpressionNode {
  protected:
    std::string name = "Identifier";
    Node_Type   nt   = n_identifier;
    std::string value;
  public:
    Node_Type getType() {return nt;}
    IdentifierNode() {
      value = "";
    }
    IdentifierNode(std::string val) {
      value = val;
    }
    void print(int d) {
      pad(d);
      cout << name <<  ": " << value << '\n';
    }
};

class NumberNode : public ExpressionNode {
  protected:
    std::string  name = "Number";
    Node_Type    nt   = n_number;
    unsigned int value;
  public:
    Node_Type getType() {return nt;}
    NumberNode(std::string val) {
      istringstream(val) >> value;
    }
    void print(int d) {
      pad(d);
      cout << name << ": " << value << '\n';
    }
    void makeTAC(TACs**,int*);
    string getValue(){
      stringstream ss;
      ss << value;
      return ss.str();
    }
};

class BooleanNode : public ExpressionNode {
  protected:
    std::string name = "Boolean";
    Node_Type   nt   = n_boolean; 
    bool        value;
  public:
    Node_Type getType() {return nt;}
    BooleanNode(std::string val) {
      if (val.front() == 't') {
        value = true;
      }
      else {
        value = false;
      }
    }
    void print(int d) {
      pad(d);
      cout << name << ": ";
      if (value) cout << "true"; else cout << "false";
      cout << '\n';
    }
    void makeTAC(TACs**,int*);
};

class IfExprNode : public ExpressionNode {
  protected:
    std::string     name = "If statement";
    Node_Type       nt   = n_if;
    ExpressionNode *test;
    ExpressionNode *thenClause;
    ExpressionNode *elseClause;
  public:
    Node_Type getType() {return nt;}
    void setTest(ExpressionNode *e) {test = e;}
    void setThen(ExpressionNode *e) {thenClause = e;}
    void setElse(ExpressionNode *e) {elseClause = e;}
    IfExprNode (ExpressionNode *t, ExpressionNode *th, ExpressionNode *e) {
      setTest(t);
      setThen(th);
      setElse(e);
    }
    void print(int);
};

class NotExprNode : public ExpressionNode {
  protected:
    std::string     name = "Not expression";
    Node_Type       nt   = n_not;
    ExpressionNode *value;
  public:
    Node_Type getType() {return nt;}
    void setValue(ExpressionNode *e) {value = e;}
    NotExprNode (ExpressionNode *e) {setValue(e);}
    void print(int);
};

class FunctionCallNode : public ExpressionNode {
  protected:
    std::string     name = "Function call";
    Node_Type       nt   = n_fncall;
    IdentifierNode *functionName;
    ExpressionList *functionBody;
  public:
    Node_Type getType() {return nt;}
    void setName(IdentifierNode *i) {functionName = i;}
    void setBody(ExpressionList *e) {functionBody = e;}
    FunctionCallNode(IdentifierNode *i, ExpressionList *e) {
      setName(i);
      setBody(e);
    }
    void print(int);
};

class NegateExprNode : public ExpressionNode {
  protected:
    std::string     name = "Negation expression";
    Node_Type       nt   = n_negate;
    ExpressionNode *value;
  public:
    Node_Type getType() {return nt;}
    void setValue(ExpressionNode *e) {value = e;}
    NegateExprNode(ExpressionNode *e) {setValue(e);}
    void print(int);
};

class BlockExprNode : public ExpressionNode {
  protected:
    std::string     name = "Block";
    Node_Type       nt   = n_block;
    ExpressionNode *value;
  public:
    Node_Type getType() {return nt;}
    void setValue(ExpressionNode *e) {value = e;}
    BlockExprNode(ExpressionNode *e) {setValue(e);}
    void print(int);
};

class BinaryExprNode : public ExpressionNode {
  protected:
    std::string     name = "Binary expression";
    Node_Type       nt   = n_binexp;
    ExpressionNode *left;
    BinaryOpNode   *op;
    ExpressionNode *right;
  public:
    Node_Type getType() {return nt;}
    void setLeft (ExpressionNode *e) {left  = e;}
    void setOp   (BinaryOpNode *o)   {op    = o;}
    void setRight(ExpressionNode *e) {right = e;}
    BinaryExprNode(ExpressionNode *l, BinaryOpNode *o, ExpressionNode *r) {
      setLeft(l);
      setOp(o);
      setRight(r);
    }
    BinaryOpNode * getOp() {return op;}
    void print(int);
    void makeTAC(TACs**,int*);
};

class ExpressionList : public Node {
  protected:
    std::string     name = "Expression list";
    Node_Type       nt   = n_exprs;
    ExpressionNode *value;
    ExpressionList *next;
  public:
    Node_Type getType() {return nt;}
    ExpressionList(ExpressionNode *v, ExpressionList *n) {
      value = v;
      next  = n;
    }
    ExpressionList(ExpressionNode *e) {
      value = e;
      next  = NULL;
    }
    void add(ExpressionNode *e) {
      next  = new ExpressionList(value, next);
      value = e;
    }
    void print(int d) {
      if (value != NULL) {(*value).print(d);}
      if (next  != NULL) { (*next).print(d);}
    }
};

/**************************************
Print functions that have to be defined
down here to avoid forward declarations
**************************************/

void BinaryExprNode::print(int d) {
  pad(d);
  cout << name << '\n';
  pad(d+1);
  cout << "Left\n";
  left->print(d+2);
  op->print(d+1);
  pad(d+1);
  cout << "Right\n";
  right->print(d+2);
}

void BlockExprNode::print(int d) {
  pad(d);
  cout << name << '\n';
  (*value).print(d+1);
}

void NegateExprNode::print(int d) {
  pad(d);
  cout << name << '\n';
  (*value).print(d+1);
}

void FunctionCallNode::print(int d) {
  pad(d);
  cout << name << '\n';
  pad(d+1);
  cout << "Function name\n";
  functionName->print(d+2);
  pad(d+1);
  cout << "Function arguments\n";
  (*functionBody).print(d+2);
}

void NotExprNode::print(int d) {
  pad(d);
  cout << name << '\n';
  (*value).print(d+1);
}

void IfExprNode::print(int d) {
  pad(d);
  cout << name << '\n';
  pad(d+1); cout << "Test\n";
  (*test).print(d+2);
  pad(d+1); cout << "Then clause\n";
  (*thenClause).print(d+2);
  pad(d+1); cout << "Else clause\n";
  (*elseClause).print(d+2);
}

void ReturnStmtNode::print(int d) {
  pad(d);
  cout << name << '\n';
  (*value).print(d+1);
}

void PrintStmtNode::print(int d) {
  pad(d);
  cout << name << '\n';
  (*value).print(d+1);
}

void BodyNode::print(int d) {
  pad(d);
  cout << name << '\n';
  value->print(d+1);
}

void DefNode::print(int d) {
  pad(d);
  cout << name << '\n';
  pad(d+1); cout << "Function name\n";
  value->print(d+2);
  pad(d+1); cout << "Function parameters\n";
  if (formals != NULL) {formals->print(d+2);}
  pad(d+1); cout << "Function type\n";
  type->print(d+2);
  pad(d+1); cout << "Function body\n";
  body->print(d+2);
}

void ProgramNode::print(int d) {
  pad(d);
  cout << name << '\n';
  pad(d+1); cout << "Program parameters\n";
  if (formals != NULL) formals->print(d+2);
  pad(d+1); cout << "Program function definitions\n";
  if (defs != NULL) defs->print(d+2);
  pad(d+1); cout << "Program body\n";
  if (body != NULL) body->print(d+2);
}


void FormalParamNode::print(int d) {
  pad(d);
  cout << name << '\n';
  pad(d+1); cout << "Parameter identifier\n";
  if (value != NULL) value->print(d+2);
  pad(d+1); cout << "Parameter type\n";
  if (type != NULL)  type->print(d+2);
}


/**************************************
    makeTAC functions  
 *************************************/

void ProgramNode::makeTAC(TACs **t, int *count) {
  cout << "*3AC for program...\n";
  if (body != NULL) body->makeTAC(t,count);
}

void BodyNode::makeTAC(TACs **t, int *count) {
  cout << "*3AC for body...\n";
  if (value != NULL) value->makeTAC(t,count);
}

void StatementList::makeTAC(TACs **t, int *count) {
  cout << "*3AC for statement list...\n";
  if (value != NULL) value->makeTAC(t,count);
  // LATER -- support for multiple statements
}

void ReturnStmtNode::makeTAC(TACs **t, int *count) {
  cout << "*3AC for return statement...\n";
  if (value != NULL) value->makeTAC(t,count);
}

void BinaryExprNode::makeTAC(TACs **t, int *count) {
  TAC myTAC;
  int left_addr, right_addr;
  // Make TAC of left and store result's dmem address
  left->makeTAC(t,count);
  left_addr  = (*count)-1;
  // Make TAC of right and store result's dmem address
  right->makeTAC(t,count);
  right_addr = (*count)-1;
  // Recall the results from memory
  cout << "*3AC for binary expression...\n";
  if (op->getValue() == "+") {myTAC.setOp(t_add);}
  if (op->getValue() == "*") {myTAC.setOp(t_mul);}
  if (op->getValue() == "-") {myTAC.setOp(t_sub);}
  if (op->getValue() == "\\") {myTAC.setOp(t_div);}
  myTAC.set1(left_addr);
  myTAC.set2(right_addr);
  myTAC.setRes(*count);
  (*count)++;
  (**t).add(myTAC);
}

void NumberNode::makeTAC(TACs **t, int *count) {
  cout << "*3AC for number node...\n";
  TAC myTAC;
  myTAC.setOp(t_ass);
  myTAC.set1(value);
  myTAC.set2(0);
  myTAC.setRes(*count);
  (*count)++;
  if (*t == NULL) {
    *t = new TACs(myTAC, NULL);
  }
  else {
    (**t).add(myTAC);
  }
}

void BooleanNode::makeTAC(TACs **t, int *count) {
//  cout << "3AC for boolean node...\n";
  TAC myTAC;
  myTAC.setOp(t_ass);
  if (value){
    myTAC.set1(1);
  } else {
    myTAC.set1(0);
  }
  myTAC.set2(0);
  myTAC.setRes(0);
  if (*t == NULL) {
    *t = new TACs(myTAC, NULL);
  }
  else {
    (**t).add(myTAC);
  }
}
/**************************************
    Nodes that aren't part of syntax  
 *************************************/

class InvalidNode : public Node {
  protected:
    std::string name = "Invalid Node";
    Node_Type nt = n_invalid;
  public:
    InvalidNode() {/*Nothing*/};
    Node_Type getType() {return nt;}
    void print(int d) {pad(d); cout << "INVALID NODE\n";}
};

class StopNode : public Node {
  protected:
    std::string name = "Stop Node";
    Node_Type nt = n_stop;
  public:
    StopNode() {/*Nothing*/};
    Node_Type getType() {return nt;}
    void print(int d) {pad(d); cout << "STOP NODE\n";}
};

