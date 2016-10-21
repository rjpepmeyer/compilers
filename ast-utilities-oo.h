#include <string>

// Base node
class Node {
	//abstract class prototype
	public:
		void print(int i){
			for(int x = i*3;i>0;i--){
				cout << " ";
			}
			cout << this.name;
		}
	protected:
		std::string       name = "Generic Node";
};

class program_Node : public Node {
	public:
		void print(){
			Node::print(0);
			identifier.print(1);
			//TODO loop for formal node array
			//TODO loop for def node array
			body.print(1);
		}
	
	protected:
	    std::string       name = "Program";
		identifier_Node   identifier;
		formal_Node[]     formal;
		body_Node         body;
		
	private:
		def_Node[]        definitions;
};

class formal_Node : public Node: {
	public:
		void print(int i){
			Node::print(i+1);
			indentifier.print(i + 1);
			type.print(i + 1);
		}
		
	protected: 
		identifier_Node     identifier;
		type_Node           type;
};

class def_Node : public program_Node {
	public:
		void print(int i){
			for(int x = i*3;i>0;i--){
				cout << " ";
			}
			cout << "Definition";
			
			identifier.print(i+1);
			formals.print(i+1); //TODO adjust for array
			type.print(i+1);
			body.print(i+1);
		}
	protected:
	    c
	//  identifier_Node   identifier;
	//  formal_Node[]     formal;
		type_Node         type;
	//  body_Node         body;
};

class body_Node : public Node {
	public statement_Node[]  statements;
};

class statement_Node : public Node {
	protected:
		print_Node        print;
		return_Node       returnVal;
};

class print_Node : public Node {
	protected:
		expr_Node_Type    exprOne;
};

class return_Node : public print_Node {
	//rotected:
	//  expr_Node_Type    exprOne
};

class if_Node : public print_Node {
	protected:
	//  expr_Node_Type    exprOne
		expr_Node_Type    exprTwo;
		expr_Node_Type    exprThree;
};

class not_Node : public print_Node {
	//rotected:
	//  expr_Node_Type    exprOne
}; 

class function_Call_Node : public Node {
	protected:
		identifier_Node   identifier;
		expr_Node_Type[]  expresions;
};

class negate_Node : public print_Node {
	//rotected:
	//  expr_Node_Type    exprOne
};

class block_Node : public print_Node {
	//rotected:
	//  expr_Node_Type    exprOne
};

class binary_Expr_Node : public print_Node {
	protected:
	//  expr_Node_Type    exprOne
		expr_Node_Type    exprTwo;
		operator_Node     op;
};

class expr_Node_Type : public Node {
	protected: 
		Node              expression;
};

// Simple nodes
class identifier_Node : public Node {std::string   value;};
class type_Node : public Node       {tokenType     value;};
class number_Node : public Node     {unsigned long value;};
class boolean_Node : public Node    {bool          value;};
class operator_Node : public Node   {char          value;};