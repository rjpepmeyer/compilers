#include <string>

// Base node
class Node {
	//abstract class prototype
	public:
		void print(int i){
			for(int x = i*3;i>0;i--){
				cout << " ";
			}
			cout << this.name << '\n';
		}
	protected:
		std::string       name = "Generic Node";
};

class program_Node : public Node {
	public:
		void print(){
			Node::print(0);
			identifier.print(1);
			for(int i=0;i<formals.length();i++){formals[i].print(1);}
			for(int i=0;i<definitions.length();i++){definitions[i].print(1);}
			body.print(1);
		}
	
	protected:
	    std::string       name = "Program";
		identifier_Node   identifier;
		formal_Node[]     formals;
		body_Node         body;
		
	private:
		def_Node[]        definitions;
};

class formal_Node : public Node: {
	public:
		void print(int i){
			Node::print(i);
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
			Node::print(i);
			identifier.print(i+1);
			for(int x=0;x<formals.length();x++){formals[x].print(i+1);}
			type.print(i+1);
			body.print(i+1);
		}
	protected:
	    std::string       name = "Definition";
	//  identifier_Node   identifier;
	//  formal_Node[]     formals;
		type_Node         type;
	//  body_Node         body;
};

class body_Node : public Node {
	public:
		void print(int i){
			Node::print(i);
			for(int x=0;x<statements.length();x++){statements[x].print(i+1);}
		}
	protected:
		std::string       name = "Body";
		statement_Node[]  statements;
};

class statement_Node : public Node {
	public:
		void print(int i){
			Node::print(i);
			print.print(i+1);
			returnVal.print(i+1);
		}
	protected:
		std::string       name = "Statement";
		print_Node        print;
		return_Node       returnVal;
};

class print_Node : public Node {
	public:
		
	protected:
		std::string       name = "Print";
		expr_Node_Type    exprOne;
};

class return_Node : public print_Node {
	protected:
		std::string       name = "Return";
	//  expr_Node_Type    exprOne
};

class if_Node : public print_Node {
	protected:
		std::string       name = "If";
	//  expr_Node_Type    exprOne
		expr_Node_Type    exprTwo;
		expr_Node_Type    exprThree;
};

class not_Node : public print_Node {
	public:
	protected:
		std::string       name = "Not";
	//  expr_Node_Type    exprOne
}; 

class function_Call_Node : public Node {
	protected:
		std::string       name = "Function Call";
		identifier_Node   identifier;
		expr_Node_Type[]  expresions;
};

class negate_Node : public print_Node {
	protected:
		std::string       name = "Negate";
	//  expr_Node_Type    exprOne
};

class block_Node : public print_Node {
	protected:
		std::string       name = "Block";
	//  expr_Node_Type    exprOne
};

class binary_Expr_Node : public print_Node {
	protected:
		std::string       name = "Binary Expression";
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