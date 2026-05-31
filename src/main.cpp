#include <iostream>
#include <fstream>
#include <sstream>


#include "lexer.hpp"
#include "syntax/parser.hpp"
#include "core/core_printer.hpp"
#include "core/lowerer.hpp"
#include "core/core_validator.hpp"
#include "runtime/evaluator.hpp"
#include "runtime/value.hpp"


int main(){
	const std::string source_path = "../examples/test.scm";
	std::ifstream inputFile(source_path);

	if(!inputFile.is_open()){
		std::cerr << "File not Found" << "\n";
		return 1;
	}

	std::stringstream buffer;
	buffer << inputFile.rdbuf();

	std::string source = buffer.str();

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

	tscm::Evaluator evaluator;
	tscm::Value result = evaluator.evaluate_program(core_program);

	std::cout << "\n\n\n RESULT: " << result.as_integer() << "\n";

	return 0;
}
