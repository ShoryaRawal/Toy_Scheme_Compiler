#pragma once

#include "backend/assembly_instructions.hpp"
#include <vector>

namespace tscm{
	struct AssemblyProgram{ std::vector<AssemblyInstruction> instructions; };
}
