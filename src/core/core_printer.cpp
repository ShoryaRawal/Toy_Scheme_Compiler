#include "core/core_printer.hpp"
#include <type_traits>

namespace tscm{
	CorePrinter::CorePrinter(std::ostream & output) : output_(output) {}

	void CorePrinter::print_program(const CoreProgram & program) {
		for(const auto & expr : program.expressions){
			print_expression(expr);
		}
	}

	void CorePrinter::print_expression(const CoreExprPtr & expr, int indent){
		const std::string padding(indent, ' ');

		std::visit(
			[&] (const auto & node){
				using T = std::decay_t<decltype(node)>;

				if constexpr (std::is_same_v<T, CoreIntegerExpr>) 
					output_ << padding << "Integer(" << node.value << ")\n";
				else if constexpr (std::is_same_v<T, CoreVariableExpr>)
					output_ << padding << "Variable(" << node.name << ")\n";
				else if constexpr (std::is_same_v<T, CoreDefineExpr>) {
					output_ << padding << "Define(" << node.name << ")\n";
					print_expression(node.value, indent + 2);
				} else if constexpr (std::is_same_v<T, CoreLambdaExpr>){
					output_ << padding << "Lambda\n";
					for (const auto & param : node.parameters)
						output_ << padding << "  Param(" << param << ")\n";
					for (const auto & body : node.body)
						print_expression(body, indent + 2);
				} else if constexpr (std::is_same_v<T, CoreCallExpr>){
					output_ << padding << "Call\n";
					print_expression(node.callee, indent + 2);

					for(const auto& arg : node.arguments) print_expression(arg, indent + 2);

				} else if constexpr (std::is_same_v<T, CoreIfExpr>) {
					output_ << padding << "If\n";
					print_expression(node.condition, indent + 2);
					print_expression(node.then_branch, indent + 2);
					print_expression(node.else_branch, indent + 2);
				} else if constexpr (std::is_same_v<T, CoreQuoteExpr>) 
					output_ << padding << "Quote\n";
			},
			expr -> value
		);
	}
}
