#include "backend/x86_64_emitter.hpp"

#include <stdexcept>
#include <variant>

namespace tscm{
	AssemblyProgram X86_64Emitter::emit(const CoreProgram & program){
		AssemblyProgram assembly;
		free_registers_ = {"rdx", "rcx", "rbx", "rax"};

		for (const auto & expr : program.expressions)
			emit_expression(expr, assembly);

		return assembly;
	}

	std::string X86_64Emitter::allocate_register() {
		if(free_registers_.empty()) 
			throw std::runtime_error("x86_64 register pool exhausted");
		
		std::string reg = free_registers_.back();
		free_registers_.pop_back();

		return reg;
	}

	void X86_64Emitter::release_register(const std::string & reg){
		free_registers_.push_back(reg);
	}

	RegisterResult X86_64Emitter::emit_expression(const CoreExprPtr & expr, AssemblyProgram & program){
		return std::visit(
			[&] (const auto & node) -> RegisterResult{
				using T = std::decay_t<decltype(node)>;

				if constexpr (std::is_same_v<T, CoreIntegerExpr>){
					const std::string reg = allocate_register();
					program.instructions.push_back({
						"mov",
						{ reg, std::to_string(node.value) }
					});
					return { reg };
				} else if constexpr (std::is_same_v<T, CoreCallExpr>){
					return emit_call(node, program);
				} else throw std::runtime_error("x86_64 backend does not support this yet.");
			},
			expr -> value
		);
	}

	RegisterResult X86_64Emitter::emit_call(const CoreCallExpr & call, AssemblyProgram & program){
		if(call.arguments.size() != 2) 
			throw std::runtime_error("Backend currently supports binary operations only");

		const auto * callee = std::get_if<CoreVariableExpr>(& call.callee -> value);
		if(!callee) throw std::runtime_error("Callee must be a symbol");

		RegisterResult lhs = emit_expression(call.arguments[0], program);
		RegisterResult rhs = emit_expression(call.arguments[1], program);

		if(callee -> name == "+"){
			program.instructions.push_back({
				"add", { lhs.reg, rhs.reg }
			});

			release_register(rhs.reg);
			return lhs;
		}else if(callee -> name == "-"){
			program.instructions.push_back({
				"sub", { lhs.reg, rhs.reg }
			});
			
			release_register(rhs.reg);
			return lhs;
		}else if(callee -> name == "*"){
			program.instructions.push_back({
				"impl", { lhs.reg, rhs.reg }
			});
			release_register(rhs.reg);
			return lhs;
		}else if(callee -> name == "/") throw std::runtime_error("division not implemented yet.");
		else throw std::runtime_error("Unsupported operator: " + callee -> name);
	}

}
