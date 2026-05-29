#include "core/core_validator.hpp"
#include <variant>

namespace tscm{
	std::vector<CoreError> CoreValidator::validate(const CoreProgram & program){
		errors_.clear();
		for (const auto & expr : program.expressions) validate_expression(expr);
		
		return errors_;
	}

	void CoreValidator::validate_expression(const CoreExprPtr & expr){
		if (!expr) {
			errors_.push_back({ "null core expression" });

			return;
		}

		std::visit(
			[&] (const auto & node) {
				using T = std::decay_t<decltype(node)>;

				if constexpr (std::is_same_v<T, CoreDefineExpr>) validate_expression(node.value);
				else if constexpr (std::is_same_v<T, CoreIfExpr>){
					validate_expression(node.condition);
					validate_expression(node.then_branch);
					validate_expression(node.else_branch);
				} else if constexpr (std::is_same_v<T, CoreCallExpr>){
					validate_expression(node.callee);
					for (const auto & arg : node.arguments)
						validate_expression(arg);
				} else if constexpr (std::is_same_v<T, CoreLambdaExpr>)
					for(const auto & body : node.body) validate_expression(body);

			},
			expr -> value
		);
	}
}
