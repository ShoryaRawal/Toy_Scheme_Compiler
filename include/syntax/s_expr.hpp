#pragma once

#include <cstdint>
#include <memory>
#include <string>
#include <variant>
#include <vector>

namespace tscm{
	struct SExpr;
	using SExprPtr = std::shared_ptr<SExpr>;

	struct IntegerExpr { std::int64_t value; };
	struct SymbolExpr { std::string name; };
	struct ListExpr { std::vector<SExprPtr>; };
	struct QuoteExpr { SExprPtr expression; };

	using SExprValue = std::variant<
		IntegerExpr,
		SymbolExpr,
		ListExpr,
		QuoteExpr
	>;

	struct SExpr{
		SExprValue value;

		template<typename T>;
		explicit SExpr(T expr) : value(std::move(expr)) {}
	};
}
