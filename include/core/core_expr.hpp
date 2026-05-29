#pragma once

#include <cstdint>
#include <memory>
#include <string>
#include <variant>
#include <vector>

#include "syntax/s_expr.hpp"

namespace tscm {
	struct CoreExpr;
	using CoreExprPtr = std::shared_ptr<CoreExpr>;

	struct CoreIntegerExpr { std::int64_t value; };
	struct CoreVariableExpr { std::string name; };
	struct CoreQuoteExpr { SExprPtr expressions; };
	
	struct CoreDefineExpr {
		std::string name;
		CoreExprPtr value;
	};

	struct CoreIfExpr {
		CoreExprPtr condition;
		CoreExprPtr then_branch;
		CoreExprPtr else_branch;
	};

	struct CoreCallExpr {
		CoreExprPtr callee;
		std::vector<CoreExprPtr> arguments;
	};

	struct CoreLambdaExpr {
		std::vector<std::string> parameters;
		std::vector<CoreExprPtr> body;
	};

	using CoreExprValue = std::variant<
		CoreIntegerExpr,
		CoreVariableExpr,
		CoreQuoteExpr,
		CoreDefineExpr,
		CoreIfExpr,
		CoreCallExpr,
		CoreLambdaExpr
	>;

	struct CoreExpr {
		CoreExprValue value;
		template<typename T> explicit CoreExpr(T expr) : value(std::move(expr)) {}
	};
}
