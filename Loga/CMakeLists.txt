# CMakeList.txt : CMake project for Loga, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (Loga "main.cpp"  "Token.h" "TokenType.h"  "Scanner.h" "Scanner.cpp" "Errors.h" "Errors.cpp" "Expression.h" "BinaryNode.h" "GroupingNode.h" "LiteralNode.h" "UnaryNode.h" "ExpressionVisitor.h" "BinaryNode.cpp" "LiteralNode.cpp"  "UnaryNode.cpp"  "AstPrinter.h" "AstPrinter.cpp" "GroupingNode.cpp" "Parser.h" "Parser.cpp" "ParseError.h" "Interpreter.cpp" "Statement.h" "ExpressionStatement.h" "PrintStatement.h" "StatementVisitor.h" "ExpressionStatement.cpp" "PrintStatement.cpp" "VariableStatement.h" "VariableStatement.cpp" "VariableNode.h" "VariableNode.cpp" "Environment.h" "AssignNode.h" "AssignNode.cpp" "BlockStatement.h" "BlockStatement.cpp" "IfStatement.h" "IfStatement.cpp" "LogicalNode.h" "LogicalNode.cpp" "WhileStatement.h" "WhileStatement.cpp" "CallNode.h" "CallNode.cpp" "LogaCallable.h" "NativeFunctions.h" "FunctionStatement.h" "FunctionStatement.cpp" "LogaFunction.h" "LogaFunction.cpp" "ReturnStatement.h" "ReturnStatement.cpp" "ReturnValue.h" "Resolver.h" "Resolver.cpp" "FunctionType.h"  "ClassStatement.cpp" "LogaClass.h"  "Value.h" "LogaInstance.h" "LogaInstance.cpp" "GetNode.h" "GetNode.cpp" "SetNode.h" "SetNode.cpp" "ThisNode.h" "ThisNode.cpp" "ClassType.h")

if (CMAKE_VERSION VERSION_GREATER 3.14)
  set_property(TARGET Loga PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
