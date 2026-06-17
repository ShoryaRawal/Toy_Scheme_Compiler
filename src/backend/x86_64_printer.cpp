#include "backend/x86_64_printer.hpp"

namespace tscm{
	X86_64Printer::X86_64Printer(std::ostream & output) : output_(output){}

	void X86_64Printer::print(const AssemblyProgram & program){
		output_ << "global _start\n\n";
		output_ << "section .text\n\n";
		output_ << "_start:\n";

		output_ << "\tpush rbp\n";
		output_ << "\tmov rbp, rsp\n";
		output_ << "\tsub rbp, 128\n";
	
		for(const auto & instruction : program.instructions){
			if(!instruction.opcode.empty() && instruction.opcode.back() == ':'){
				output_ << instruction.opcode << "\n";
				continue;
			}
			output_ << "\t" << instruction.opcode;
			
			for(std::size_t i = 0; i < instruction.operands.size(); ++i){
				output_ << " " << instruction.operands[i];
				if(i + 1 < instruction.operands.size())
					output_ << ", ";
			}
			output_ << "\n";
		}

		output_ << "\tmov rsp, rbp\n";
		output_ << "\tpop rbp\n\n";

		output_ << "\tmov rdi, rax\n";
		output_ << "\tmov rax, 60\n";
		output_ << "\tsyscall\n";
	}
}
