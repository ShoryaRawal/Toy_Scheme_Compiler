#include <iostream>
#include <memory>
#include <vector>

#include "lexer.hpp"
#include "token.hpp"
#include "syntax/parser.hpp"
#include "syntax/s_expr.hpp"

namespace {
	void print_s_expr(const tscm::SExprPtr & expr, int indent = 0) {
		const auto padding = std::string(indent, ' ');
		std::visit(
			[&](const auto & node) {
				using T = std::decay_t<decltype(node)>;
				if constexpr (std::is_same_v<T, tscm::IntegerExpr>) {
					std::cout
						<< padding
						<< "Integer: "
						<< node.value
						<< '\n';
				} else if constexpr (std::is_same_v<T, tscm::SymbolExpr>) {
					std::cout
						<< padding
						<< "Symbol: "
						<< node.name
						<< '\n';
				} else if constexpr (std::is_same_v<T, tscm::ListExpr>) {
					std::cout << padding << "List: \n";
					for (const auto & element : node.elements) {
						print_s_expr(element, indent + 2);
					}
				} else if constexpr (std::is_same_v<T, tscm::QuoteExpr>){
					std::cout << padding << "Quote: \n";
					print_s_expr(node.expression, indent + 2);
				}
			},
			expr -> value
		);
	}
}

int main(){
	const std::string source = R"(
		(define square
			(lambda (x)
				(* x x)))

		(square 5)
	)";

	tscm::Lexer lexer (source);
	const auto tokens = lexer.tokenize();
	
	tscm::Parser parser(tokens);
	const auto expr = parser.parse();

	print_s_expr(expr);

	return 0;
}
