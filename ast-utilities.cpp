#include <string>

// Simple nodes
struct identifier_ast {std::string   value;};
struct type_ast       {tokenType     value;};
struct number_ast     {unsigned long value;};
struct boolean_ast    {bool          value;};
struct operator_ast   {char          value;};

struct formal_ast  {
  identifier_ast identifier;
  type_ast       type;
};

