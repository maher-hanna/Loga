// Loga.cpp : Defines the entry point for the application.
//


#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "Loga.h"
#include "Errors.h"
#include "Scanner.h"
#include "AstPrinter.h"
#include "Parser.h"

void run(std::string source) {
    Scanner* scanner = new Scanner(source);
    std::vector<Token> tokens = scanner->scanTokens();

    // For now, just print the tokens.
    for (Token token : tokens) {
        std::cout << token.toString() << std::endl;
    }

    Parser parser (tokens);
    ExpressionNode * expression = parser.parse();

    // Stop if there was a syntax error.
    if (hadError) return;
	AstPrinter astPrinter;

    std::cout << astPrinter.print(*expression);
    delete scanner;
}



void runFile(std::string path) {
    std::ifstream file(path, std::ios::in | std::ios::binary);
    if (file) {
        std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        file.close();
        run(content);
    }
    else {
        std::cerr << "Error opening file!" << std::endl;
        std::exit(65);
    }
    if (hadError)
        std::exit(65);


}

void runPrompt() {

    for (;;) {
        std::cout << "> ";
        std::string line = "";
        std::getline(std::cin, line);
        if (line.empty())
            break;
        run(line);
        hadError = false;

    }
}


int main(int argc, char* argv[])
{
    //AstPrinter astPrinter;

    //ExpressionNode* expression = new BinaryNode(
    //    new UnaryNode(
    //        Token(TokenType::MINUS, "-", "", 1),
    //        new LiteralNode("123.0")),
    //    Token(TokenType::STAR, "*", "", 1),
    //    new GroupingNode(
    //        new LiteralNode("45.67"))

    //);

    //std::cout << astPrinter.print(*expression);
    //delete expression;

    if (argc > 2) {
        std::cout << "Usage: jlox [script]";
        std::exit(64);
    }
    else if (argc == 2) {
        runFile(argv[0]);
    }
    else {
        runPrompt();
    }
	return 0;
}

