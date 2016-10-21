#include <string>

// Base node
class Node {
	//abstract class prototype
};

class program_Node : public Node {
	public identifier_Node   identifier;
    public formal_Node[]     formal;	
	public def_Node[]        definitions;
	public body_Node         body;
};

class formal_Node : public Node: {
  public identifier_Node     identifier;
  public type_Node           type;
};

class def_Node : public program_Node {
	//blic identifier_Node   identifier;
	//blic formal_Node[]     formal;
	public type_Node         type;
	//blic body_Node         body;
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
	//blic expr_Node_Type    exprOne
};

class if_Node : public print_Node {
	//blic expr_Node_Type    exprOne
	public expr_Node_Type    exprTwo;
	public expr_Node_Type    exprThree;
};

class not_Node : public print_Node {
	//blic expr_Node_Type    exprOne
}; 

class function_Call_Node : public Node {
    public identifier_Node   identifier;
	public expr_Node_Type[]  expresions;
};

class negate_Node : public print_Node {
	//blic expr_Node_Type    exprOne
};

class block_Node : public print_Node {
	//blic expr_Node_Type    exprOne
};

class binary_Expr_Node : public print_Node {
	//blic expr_Node_Type    exprOne
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