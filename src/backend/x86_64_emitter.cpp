#include "backend/x86_64_emitter.hpp"

#include <stdexcept>
#include <variant>

namespace tscm{
	namespace{
		constexpr const char * kRegisters[] = {"rax", "rbx", "rcx", "rdx"};
		constexpr std::size_t kRegisterCount = sizeof(kRegisters) / sizeof(kRegisters[0]);
	}

	AssemblyProgram X86_64Emitter::emit(const CoreProgram & program){
		AssemblyProgram assembly;
		next_register_ = 0;

		for (const auto & expr : program.expressions)
			emit_expression(expr, assembly);

		return assembly;
	}

	std::string X86_64Emitter::allocate_register() {
		if(next_register_ >= kRegisterCount) 
			throw std::runtime_error("temporary register pool exhausted");
		
		return kRegisters[next_register_++];
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

		if(callee -> name == "+")
			program.instructions.push_back({
				"add", { lhs.reg, rhs.reg }
			});

		else if(callee -> name == "-")
			program.instructions.push_back({
				"sub", { lhs.reg, rhs.reg }
			});

		else if(callee -> name == "*")
			program.instructions.push_back({
				"impl", { lhs.reg, rhs.reg }
			});
		else if(callee -> name == "/") throw std::runtime_error("division not implemented yet.");
		
		else throw std::runtime_error("Unsupported operator: " + callee -> name);

		return lhs;
	}

}
