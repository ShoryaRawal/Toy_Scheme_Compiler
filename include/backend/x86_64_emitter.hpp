#pragma once

#include <unordered_map>
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
			RegisterResult emit_define(const CoreDefineExpr & define, AssemblyProgram & program);
			RegisterResult emit_variable(const CoreVariableExpr & variable, AssemblyProgram & program);

			void release_register(const std::string & reg);

			std::string allocate_register();

		private:
			std::vector<std::string> free_registers_;
			std::unordered_map<std::string, int> stack_slots_;
			int next_stack_offset_ = -8;
	};
}
