#pragma once

#include <cstddef>
#include <string>
#include <vector>

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
			void release_register(const std::string & reg);

			std::string allocate_register();

		private:
			std::vector<std::string> free_registers_;
	};
}
