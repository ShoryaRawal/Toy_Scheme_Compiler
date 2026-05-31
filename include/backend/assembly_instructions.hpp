#pragma once

#include <string>
#include <vector>

namespace tscm{
	struct AssemblyInstruction{
		std::string opcode;
		std::vector<std::string> operands;
	};
}
