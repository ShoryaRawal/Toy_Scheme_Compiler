#include "core/lowerer.hpp"
#include <stdexcept>

namespace tscm {
	CoreProgram Lowerer::lower_program(const SyntaxProgram & program){
		CoreProgram core_program;
		for (const auto & expr : program.expressions) {
			core_program.expressions.push_back(lower_expression(expr));
		}
		return core_program;
	}

	CoreExprPtr Lowerer::lower_expression(const SExprPtr & expr){
		return std::visit(
			[&](const auto & node) -> CoreExprPtr{
				using T = std::decay_t<decltype(node)>;
				if constexpr (std::is_same_v<T, IntegerExpr>){
					return std::make_shared<CoreExpr>(tscm::IntegerExpr{ node.value });
				} else if constexpr (std::is_same_v<T, SymbolExpr>){
					return std::make_shared<CoreExpr>(VariableExpr{ node.name });
				} else if constexpr (std::is_same_v<T, QuoteExpr>){
					return std::make_shared<CoreExpr>(tscm::QuoteExpr{ node.expression });
				} else if constexpr (std::is_same_v<T, ListExpr>){
					return lower_list(node);
				} else { return nullptr; }
			},
			expr -> value
		);
	}

	CoreExprPtr Lowerer::lower_list(const listExpr & list){
		if (list.elements.empty()) {
			throw std::runtime_error("ERROR: List is empty.");
		}

		const auto & head = list.elements[0];

		if (const auto * symbol = std::get_if<SymbolExpr>(&head -> value)) {
			if (symbol->name == "define") return lower_define(list);
			if (symbol->name == "if") return lower_if(list);
			if (symbol->name == "lambda") return lower_lambda(list);
		}
		return lower_call(list);
	}

	CoreExprPtr Lowerer::lower_define(const ListExpr & list) {
		const auto & symbol = std::get_if<SymbolExpr>(list.elements[1] -> value);
		return std::make_shared<CoreExpr>(
			DefineExpr{ symbol.name, lower_expression(list.elements[2]) }
		);
	}

	CoreExprPtr Lowerer::lower_if(const ListExpr & list){
		return std::make_shared<CoreExpr>(
			IfExpr{
				lower_expression(list.elements[1]),
				lower_expression(list.elements[2]),
				lower_expression(list.elements[3])
			}
		);
	}

	CoreExprPtr Lowerer::lower_lambda(const ListExpr & list){
		LambdaExpr lambda;

		const auto & params = std::get<ListExpr>(list.elements[1] -> value);
		for (const auto & param : params.elements){
			const auto & symbol = std::get<SymbolExpr>(param -> value);
			lambda.parameters.push_back(symbol.name);
		}

		for (std::size_t i = 2; i < list.elements.size(); ++i){
			lambda.body.push_back(lower_expression(list.elements[i]));
		}

		return std::make_shared<CoreExpr>(std::move(lambda));
	}

	CoreExprPtr Lowerer::lower_call(const ListExpr & list){
		CallExpr call;
		call.callee = lower_expression(list.elements[0]);

		for (std::size_t i = 1; i < list.elements.size(); ++i){
			call.arguments.push_back(lower_expression(list.elements[i]));
		}

		return std::make_shared<CoreExpr>(std::move(call));
	}
}
