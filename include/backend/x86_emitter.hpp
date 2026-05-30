#pragma once

#include "backend/assembly_program.hpp"
#include "core/core_program.hpp"

namespace tscm{
	class X86Emitter{
		public:
			AssemblyProgram emit( const CoreProgram & program );
	};
}
