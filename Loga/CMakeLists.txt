# CMakeList.txt : CMake project for Loga, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (Loga "Loga.cpp" "Loga.h" "Token.h" "TokenType.h"  "Scanner.h" "Scanner.cpp" "Errors.h" "Errors.cpp" "Expression.h" "BinaryNode.h" "GroupingNode.h" "LiteralNode.h" "UnaryNode.h" "ExpressionVisitor.h" "BinaryNode.cpp" "LiteralNode.cpp"  "UnaryNode.cpp"  "AstPrinter.h" "AstPrinter.cpp" "GroupingNode.cpp" "Parser.h" "Parser.cpp" "ParseError.h" "Interpreter.cpp" "Statement.h" "ExpressionStatement.h" "PrintStatement.h" "StatementVisitor.h" "ExpressionStatement.cpp" "PrintStatement.cpp" "VariableStatement.h" "VariableStatement.cpp" "VariableNode.h" "VariableNode.cpp" "Environment.h" "AssignNode.h" "AssignNode.cpp" "BlockStatement.h" "BlockStatement.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.14)
  set_property(TARGET Loga PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
