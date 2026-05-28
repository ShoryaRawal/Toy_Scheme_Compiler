#include "syntax/syntax_printer.hpp"
#include <type_traits>

namespace tscm {
	SyntaxPrinter::SyntaxPrinter(std::ostream & output) : output_(output) {}

	void SyntaxPrinter::print_program(const Program & program){
		for (const auto & expr : program.expressions) print_expression(expr);
	}

	void SyntaxPrinter::print_expression(const SExprPtr & expr, int indent){
		const std::string padding(indent, ' ');
		std::visit(
			[&](const auto & node) {
				using T = std::decay_t<decltype(node)>;
				if constexpr (std::is_same_v<T, IntegerExpr>){
					output_
						<< padding << "Integer: "
						<< node.value << "\n";
				} else if constexpr (std::is_same_v<T, SymbolExpr>){
					output_
						<< padding << "Symbol: "
						<< node.name << "\n";
				} else if constexpr (std::is_same_v<T, ListExpr>){
					output_ << padding << "List: \n";
					for (const auto & element : node.elements)
						print_expression(element, indent + 2);
				} else if constexpr (std::is_same_v<T, QuoteExpr>){
					output_ << padding << "Quote: \n";
					print_expression(node.expression, indent + 2);
				}

			},
			expr -> value
		);
	}
}
