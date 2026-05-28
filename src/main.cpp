#include <iostream>
#include <memory>
#include <vector>

#include "lexer.hpp"
#include "syntax/s_expr.hpp"
#include "syntax/parser.hpp"

int main(){
	const std::string source = R"(
		(define square
			(lambda (x)
				(* x x)))

		(square 5)
	)";

	tscm::Lexer lexer (source);

	const std::vector<tscm::Token> tokens = lexer.tokenize();
	for (const auto & token : tokens) {
		std::cout
			<< tscm::token_kind_to_string(token.kind)
			<< " : "
			<< token.lexeme
			<< '\n';
	}

	return 0;
}
