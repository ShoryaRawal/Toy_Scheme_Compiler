#include "backend/toolchain.hpp"

#include <cstdlib>
#include <stdexcept>

namespace tscm{
	void Toolchain::assemble_and_link(
		const std::string & asm_file,
		const std::string & obj_file,
		const std::string & exe_file
	){
		const std::string nasm_command = "nasm -f elf64 " + asm_file + " -o " + obj_file;
		if(std::system(nasm_command.c_str()) != 0) 
			throw std::runtime_error("nasm failed"); 


		const std::string ld_command = "ld " + obj_file + " -o " + exe_file;
		if(std::system(ld_command.c_str()) != 0)
			throw std::runtime_error("ld failed");
	}
}
