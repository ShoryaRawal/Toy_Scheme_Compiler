#include <iostream>

#include "lexer.hpp"
#include "syntax/parser.hpp"
#include "core/core_printer.hpp"
#include "core/lowerer.hpp"
#include "core/core_validator.hpp"


int main(){
	const std::string source = R"(
		(define max
			(lambda (a b)
				(if (> a 
					a
					b)))

		(max 10 20)
	)";

	tscm::Lexer lexer (source);
	const auto tokens = lexer.tokenize();
	
	tscm::Parser parser(tokens);
	//const auto program = parser.parse_program();

	const auto syntax_program = parser.parse_program();

	tscm::Lowerer lowerer;
	const auto core_program = lowerer.lower_program(syntax_program);

	tscm::CoreValidator validator;
	const auto errors = validator.validate(core_program);
	if(!errors.empty()){
		std::cout << "Validation Failed" << "\n";
		for (const auto & error : errors) std::cout << "error: " << error.message << "\n";
		return 1;
	}

	tscm::CorePrinter printer(std::cout);
	printer.print_program(core_program);

	return 0;
}
