#include "backend/x86_64_emitter.hpp"

#include <stdexcept>
#include <variant>

namespace tscm{
	AssemblyProgram X86_64Emitter::emit(const CoreProgram & program){
		AssemblyProgram assembly;
		free_registers_ = {"rdx", "rcx", "rbx", "rax"};

		stack_slots_.clear();
		next_stack_offset_ = -8;
		/*RegisterResult last_result;
		for (const auto & expr : program.expressions)
			last_result = emit_expression(expr, assembly);
		*/

		RegisterResult last_result;
		bool have_result = false;

		for (const auto & expr : program.expressions){
			if(have_result && !last_result.reg.empty() && last_result.reg != "rax"){
				release_register(last_result.reg);
			}
			last_result = emit_expression(expr, assembly);
			have_result = true;
		}

		if(!program.expressions.empty())
			if(last_result.reg != "rax")
				assembly.instructions.push_back({
						"mov", { "rax", last_result.reg }
					});

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
				} else if constexpr (std::is_same_v<T, CoreDefineExpr>){
					return emit_define(node, program);
				} else if constexpr (std::is_same_v<T, CoreVariableExpr>){
					return emit_variable(node, program);
				} else throw std::runtime_error("x86_64 backend does not support this yet.");
			},
			expr -> value
		);
	}

	RegisterResult X86_64Emitter::emit_define(const CoreDefineExpr & define, AssemblyProgram & program){
		RegisterResult value = emit_expression(define.value, program);
		int offset = next_stack_offset_;
		next_stack_offset_ -= 8;

		stack_slots_[define.name] = offset;

		program.instructions.push_back({
			"mov",
			{ "[rbp" + std::to_string(offset) + "]", value.reg }
		});

		release_register(value.reg);

		return { "rax" };
	}

	RegisterResult X86_64Emitter::emit_variable(const CoreVariableExpr & variable, AssemblyProgram & program){
		auto it = stack_slots_.find(variable.name);
		if(it == stack_slots_.end())
			throw std::runtime_error("undefined variable: " + variable.name);

		std::string reg = allocate_register();
		int offset = it -> second;
		program.instructions.push_back({
			"mov",
			{ reg, "[rbp" + std::to_string(offset) + "]" }
		});

		return { reg };
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
				"imul", { lhs.reg, rhs.reg }
			});
			release_register(rhs.reg);
			return lhs;
		}else if(callee -> name == "/") throw std::runtime_error("division not implemented yet.");
		else throw std::runtime_error("Unsupported operator: " + callee -> name);
	}

}
