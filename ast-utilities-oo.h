#include <string>

// Base node
class Node {
	//abstract class prototype
};

class program_Node : public Node {
	public identifier_Node   identifier;
	public Node              body;
	public def_Node[]        definitions;
    public formal_Node[]     formal;
};

class formal_Node : public Node: {
  public identifier_Node     identifier;
  public type_Node           type;
};

class def_Node : public Node {
	public type_Node         type;
};

class body_Node : public Node {
	public statement_Node[]  statements;
};

class statement_Node : public Node {
	public print_Node        print;
	public return_Node       returnVal;
};

class print_Node : public Node {
	public expr_Node_Type    exprOne;
};

class return_Node : public print_Node {
	//nothing new
};

class if_Node : public print_Node {
	public expr_Node_Type    exprTwo;
	public expr_Node_Type    exprThree;
};

class not_Node : public print_Node {
	//nothing new
}; 

class function_Call_Node : public Node {
    public identifier_Node   identifier;
	public expr_Node_Type[]  expresions;
};

class negate_Node : public print_Node {
	//nothing new
};

class block_Node : public print_Node {
	//nothing new
};

class binary_Expr_Node : public print_Node {
	public expr_Node_Type    exprTwo;
	public operator_Node     op;
};

class expr_Node_Type : public Node {
	public Node              expression;
};

// Simple nodes
class identifier_Node : public Node {std::string   value;};
class type_Node : public Node       {tokenType     value;};
class number_Node : public Node     {unsigned long value;};
class boolean_Node : public Node    {bool          value;};
class operator_Node : public Node   {char          value;};



class if_Node : public Node {
  leftChild      then_Node : public Node;// then expression node
  rightChild     else_Node : public Node;// else expression node
};

class then_Node : public Node {
    leftChild    expr_Node : public Node;//expr with boolean result
    rightChild   expr_Node : public Node;//expr to perform if L-child is true
};

class else-ast {
    leftChild    expr_Node : public Node;//expr with boolean result
    rightChild   expr_Node : public Node;//expr to perform if L-child is false
};