// Loga.cpp : Defines the entry point for the application.
//


#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <chrono>
#include "Errors.h"
#include "Scanner.h"
#include "Resolver.h"
#include "Parser.h"
#include "Interpreter.h"

void run(std::string source,Interpreter * interpreter) {
    Scanner* scanner = new Scanner(source);
    std::vector<Token> tokens = scanner->scanTokens();

    // For now, just print the tokens.
    //for (Token token : tokens) {
    //    std::cout << token.toString() << std::endl;
    //}

    Parser parser (tokens);
    std::vector<Statement*> statements = parser.parse();

    // Stop if there was a syntax error.
    if (hadError) return;
	//AstPrinter astPrinter;

    Resolver* resolver = new Resolver(interpreter);
    resolver->resolve(statements);

    if (hadError) return;

    interpreter->interpret(statements);


    //std::cout << astPrinter.print(*expression);
    delete scanner;
}



void runFile(std::string path,Interpreter * interpreter) {
    std::ifstream file(path, std::ios::in | std::ios::binary);
    if (file) {
        std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        file.close();
        run(content,interpreter);
    }
    else {
        std::cerr << "Error opening file!" << std::endl;
        std::exit(65);
    }
    if (hadError)
        std::exit(65);
    if (hadRuntimeError)
        std::exit(70);



}

void runPrompt(Interpreter * interpreter) {

    for (;;) {
        std::cout << "> ";
        std::string line = "";
        std::getline(std::cin, line);
        if (line.empty())
            break;
        run(line,interpreter);
        hadError = false;

    }
}


int main(int argc, char* argv[])
{
    auto start = std::chrono::high_resolution_clock::now();

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
    Interpreter* interpreter = new Interpreter();

    if (argc > 2) {
        std::cout << "Usage: loga [script]";
        std::exit(64);
    }
    else if (argc == 2) {
        runFile(argv[0],interpreter);
    }
    else {
        runPrompt(interpreter);
    }
    //runFile("C:/Users/maher/dev/Loga/training/fibo.loga", interpreter);

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    std::cout << "Elapsed time: " << elapsed.count() << " seconds\n";
	return 0;
}

