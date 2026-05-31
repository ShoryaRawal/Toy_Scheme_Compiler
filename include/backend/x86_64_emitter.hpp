#pragma once

#include <cstddef>
#include <string>

#include "backend/assembly_program.hpp"
#include "core/core_program.hpp"

namespace tscm{
	struct RegisterResult{ std::string reg; };
	
	class X86_64Emitter{
		public:
			AssemblyProgram emit( const CoreProgram & program );

		private:
			RegisterResult emit_expression(const CoreExprPtr & expr, AssemblyProgram & program);
			RegisterResult emit_call(const CoreCallExpr & call, AssemblyProgram & program);

			std::string allocate_register();

		private:
			std::size_t next_register_ = 0;
	};
}
