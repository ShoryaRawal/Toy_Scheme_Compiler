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

#include "backend/x86_64_emitter.hpp"
#include "backend/x86_64_printer.hpp"
#include "backend/toolchain.hpp"


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

	tscm::CorePrinter core_printer(std::cout);
	core_printer.print_program(core_program);

	tscm::X86_64Emitter emitter;
	tscm::AssemblyProgram assembly = emitter.emit(core_program);

	std::ofstream asm_file("output.asm");

	tscm::X86_64Printer printer(asm_file);
	printer.print(assembly);

	asm_file.close();

	tscm::Toolchain toolchain;
	toolchain.assemble_and_link("output.asm", "outout.o", "a.out");

	return 0;
}
