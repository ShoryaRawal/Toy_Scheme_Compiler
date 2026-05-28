#include <iostream>
#include <memory>
#include <vector>

#include "lexer.hpp"
#include "syntax/parser.hpp"
#include "syntax/syntax_printer.hpp"


int main(){
	const std::string source = R"(
		(define square
			(lambda (x)
				(* x x)))
		'(1 2 3)

		(square 5)
	)";

	tscm::Lexer lexer (source);
	const auto tokens = lexer.tokenize();
	
	tscm::Parser parser(tokens);
	const auto program = parser.parse_program();

	tscm::SyntaxPrinter printer(std::cout);
	printer.print_program(program);

	return 0;
}
