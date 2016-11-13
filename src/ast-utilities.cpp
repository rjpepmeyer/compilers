#include <string>
#include <iostream>
#include <sstream>
#include "ast-utilities.hpp"

class TypeNode : public Node {
  protected:
    Node_Type   nt   = n_type;
    std::string name = "Type";
    std::string value;
  public:
    TypeNode() {
      value = "";
    }
    TypeNode(tokenType val) {
      if (val == booleanvalue) {
        value = "boolean";
      }
      else if (val == number) {
        value = "number";
      }
    }
    void print(int d) {
      pad(d);
      cout << name << ": " << value << '\n';
    }
};

class BinaryOpNode : public Node {
  protected:
    std::string name = "Binary Operator";
    Node_Type   nt   = n_operator; 
    char        value;
  public:
    BinaryOpNode(char val) {
      value = val;
    }
    BinaryOpNode() {}
    void print(int d) {
      pad(d);
      cout << name << ": " << value << '\n';
    }
};

class ProgramNode : public Node {
  protected:
    std::string     name = "Program";
    Node_Type       nt   = n_program;
    IdentifierNode *value;
    FormalList     *formals;
    DefList        *defs;
    BodyNode       *body;
  public:
    void setValue(IdentifierNode *i) {value = i;};
    void setFormals(FormalList *i) {formals = i;};
    void setDefs(DefList *i) {defs = i;};
    void setBody(BodyNode *i) {body = i;};
    ProgramNode(IdentifierNode *v, FormalList *f, DefList *d, BodyNode *b){
      setValue(v);
      setFormals(f);
      setDefs(d);
      setBody(b);
    }
    void print(int);
};

class FormalParamNode : public Node {
  protected:
    std::string      name = "Formal Parameter";
    Node_Type        nt   = n_formal;
    IdentifierNode * value;
    TypeNode         type;
  public:
    void setValue(IdentifierNode * i) {value = i;}
    void setType(TypeNode t) {type = t;}
    FormalParamNode(IdentifierNode * i, TypeNode t) {
      setValue(i);
      setType(t);
    }
    void print(int d);
};

class FormalList : public Node {
  protected:
    std::string      name = "List of formal parameters";
    Node_Type        nt   = n_formals;
    FormalParamNode *value;
    FormalList      *next;
  public:
    FormalList(FormalParamNode *f) {
      value = f;
    }
    void addFormal(FormalParamNode f) {
      if (next == NULL) {
        next = new FormalList(&f);
      }
      else {
        (*next).addFormal(f);
      }
    }
    void print(int d) {
      if (value != NULL) {(*value).print(d);}
      if (next != NULL) {(*next).print(d);}
    }
};

class DefNode : public Node {
  protected:
    std::string      name = "Definition";
    Node_Type        nt   = n_def;
    IdentifierNode * value;
    FormalList     * formals;
    TypeNode         type;
    BodyNode       * body;
  public:
    void setValue(IdentifierNode *v) {value = v;};
    void setFormals(FormalList *f) {formals = f;};
    void setType(TypeNode *t) {type = *t;};
    void setBody(BodyNode *b) {body = b;};
    DefNode(IdentifierNode *v, FormalList *f, TypeNode *t, BodyNode *b) {
      setValue(v);
      setFormals(f);
      setType(t);
      setBody(b);
    }
    void print(int);
};

class DefList : public Node {
  protected:
    std::string  name = "Definitions List";
    Node_Type    nt   = n_defs;
    DefNode     *value;
    DefList     *next;
  public:
    DefList(DefNode *d) {
      value = d;
    }
    void addDef(DefNode d) {
      if (next == NULL) {
        next = new DefList(&d);
      }
      else {
        (*next).addDef(d);
      }
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
    StatementList *value;
  public:
    BodyNode(StatementList *s) {
      value = s;
    }
    void print(int);
};

class StatementNode : public Node {
  protected:
    std::string      name;
    Node_Type        nt;
    ExpressionNode * value;
  public:
    void setValue(ExpressionNode *e) {value = e;}
    virtual void print(int) =0;
};

class PrintStmtNode : public StatementNode {
  protected:
    std::string     name = "Print Statement";
    Node_Type       nt   = n_print;
    ExpressionNode *value;
  public:
    void setValue(ExpressionNode *e) {value = e;}
    PrintStmtNode (ExpressionNode *e) {setValue(e);}
    void print(int);
};

class ReturnStmtNode : public StatementNode {
  protected:
    std::string     name = "Return Statement";
    Node_Type       nt   = n_return;
    ExpressionNode *value;
  public:
    void setValue(ExpressionNode *e) {value = e;}
    ReturnStmtNode (ExpressionNode *e) {setValue(e);}
    void print(int);
};

class StatementList : public Node {
  protected:
    std::string    name = "Statement List";
    Node_Type      nt   = n_statements;
    StatementNode *value;
    StatementList *next;
  public:
    StatementList(StatementNode *s) {value = s;}
    void addStatement(StatementNode *s) {
      if (next == NULL) {
        next = new StatementList(s);
      }
      else {
        (*next).addStatement(s);
      }
    }
    void print(int d) {
      if (value != NULL) {(*value).print(d);}
      if (next  != NULL) { (*next).print(d);}
    }
};

class ExpressionNode : public Node {
  protected:
    std::string name;
    Node_Type   nt;
  public:
    virtual void print(int)=0;
};

class IdentifierNode : public ExpressionNode {
  protected:
    std::string name = "Identifier";
    Node_Type   nt   = n_identifier;
    std::string value;
  public:
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
    NumberNode(std::string val) {
      istringstream(val) >> value;
    }
    void print(int d) {
      pad(d);
      cout << name << ": " << value << '\n';
    }
};

class BooleanNode : public ExpressionNode {
  protected:
    std::string name = "Boolean";
    Node_Type   nt   = n_boolean; 
    bool        value;
  public:
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
};

class IfExprNode : public ExpressionNode {
  protected:
    std::string     name = "If Expression";
    Node_Type       nt   = n_if;
    ExpressionNode *test;
    ExpressionNode *thenClause;
    ExpressionNode *elseClause;
  public:
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
    std::string     name = "Not Expression";
    Node_Type       nt   = n_not;
    ExpressionNode *value;
  public:
    void setValue(ExpressionNode *e) {value = e;}
    NotExprNode (ExpressionNode *e) {setValue(e);}
    void print(int);
};

class FunctionCallNode : public ExpressionNode {
  protected:
    std::string     name = "Function Call";
    Node_Type       nt   = n_fncall;
    IdentifierNode *functionName;
    ExpressionList *functionBody;
  public:
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
    std::string     name = "Negate Expression";
    Node_Type       nt   = n_negate;
    ExpressionNode *value;
  public:
    void setValue(ExpressionNode *e) {value = e;}
    NegateExprNode(ExpressionNode *e) {setValue(e);}
    void print(int);
};

class BlockExprNode : public ExpressionNode {
  protected:
    std::string     name = "Block Expression";
    Node_Type       nt   = n_block;
    ExpressionNode *value;
  public:
    void setValue(ExpressionNode *e) {value = e;}
    BlockExprNode(ExpressionNode *e) {setValue(e);}
    void print(int);
};

class BinaryExprNode : public ExpressionNode {
  protected:
    std::string     name = "Binary Expression";
    Node_Type       nt   = n_binexp;
    ExpressionNode *left;
    BinaryOpNode    op;
    ExpressionNode *right;
  public:
    void setLeft (ExpressionNode *e) {left  = e;}
    void setOp   (BinaryOpNode *o)   {op    = *o;}
    void setRight(ExpressionNode *e) {right = e;}
    BinaryExprNode(ExpressionNode *l, BinaryOpNode *o, ExpressionNode *r) {
      setLeft(l);
      setOp(o);
      setRight(r);
    }
    void print(int);
};

class ExpressionList : public Node {
  protected:
    std::string     name = "Expression List";
    Node_Type       nt   = n_exprs;
    ExpressionNode *value;
    ExpressionList *next;
  public:
    ExpressionList(ExpressionNode *e) {
      value = e;
    }
    void addExpression(ExpressionNode *e) {
      if (next == NULL) {
        next = new ExpressionList(e);
      }
      else {
        (*next).addExpression(e);
      }
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
  (*left ).print(d+1);
  op.print(d+1);
  (*right).print(d+1);
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
  functionName->print(d+1);
  (*functionBody).print(d+1);
}

void NotExprNode::print(int d) {
  pad(d);
  cout << name << '\n';
  (*value).print(d+1);
}

void IfExprNode::print(int d) {
  pad(d);
  cout << name << '\n';
  (*test).print(d+1);
  (*thenClause).print(d+1);
  (*elseClause).print(d+1);
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
  (*value).print(d+1);
}

void DefNode::print(int d) {
  pad(d);
  cout << name << '\n';
  value->print(d+1);
  if (formals != NULL) {(*formals).print(d+1);}
  type.print(d+1);
  (*body).print(d+1);
}

void ProgramNode::print(int d) {
  pad(d);
  cout << name << '\n';
  if (formals != NULL) {(*formals).print(d+1);}
  if (defs != NULL) {(*defs).print(d+1);}
  (*body).print(d+1);
}


void FormalParamNode::print(int d) {
  pad(d);
  cout << name << '\n';
  value->print(d+1);
  type.print(d+1);
}
/**************************************
            Semantic stack
**************************************/

enum SType {sprogram, sformal, sdef, sbody, sstatement, sprint, sreturn, sif,
  snot, sfncall, snegate, sblock, sbinexp, sexpr, sidentifier, stype,
  soperator, snumber, sboolean, sformals, sdefs, sstatements, sexprs};

class SemanticStack {
  protected:
    SemanticNode * item;
  public:
    SemanticStack() {item = NULL;}
    void push(Node * i);
    Node * pop();
    Node * peek();
};

class SemanticNode {
  protected:
    Node           * value;
    SemanticNode   * next;
  public:
    SemanticNode(Node * n, SemanticNode * p) {
      value = n;
      next  = p;
    }
    Node * getValue() {
      return value;
    }
    SemanticNode * getNext() {
      return next;
    }
};

void SemanticStack::push(Node * i) {
  item = new SemanticNode(i, item);
}

Node * SemanticStack::pop() {
  Node * n;
  n = (*item).getValue();
  // TODO: fix memory leak
  item = (*item).getNext();
  return n;
}
