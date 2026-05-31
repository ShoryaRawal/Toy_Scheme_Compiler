#include "backend/x86_64_printer.hpp"

namespace tscm{
	X86_64Printer::X86_64Printer(std::ostream & output) : output_(output){}

	void X86_64Printer::print(const AssemblyProgram & program){
		output_ << "global _start\n\n";
		output_ << "section .text\n\n";
		output_ << "_start:\n";

		for(const auto & instruction : program.instructions){
			output_ << "	" << instruction.opcode;
			
			if(!instruction.operands.empty()){
				for(std::size_t i = 0; i < instruction.operands.size(); ++i){
					output_ << " " << instruction.operands[i];
					if(i + 1 < instruction.operands.size()) output_ << ", ";
				}
			}
			output_ << "\n";
		}
		output_ << "	mov rdi, rax\n\tmov rax, 60\n\tsyscall";
	}
}
