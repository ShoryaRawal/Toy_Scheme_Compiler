#pragma once

#include <memory>
#include <vector>

#include "token.hpp"
#include "syntax/s_expr.hpp"

namespace tscm{
	class Parser{
		public:
			explicit Parser(const std::vector<Token> & tokens);
			SExprPtr parse();

		private:
			const std::vector<Token> & tokens_;
			std::size_t current_;

		private:
			bool is_at_end() const;

			const Token & peek() const;
			const Token & advance();

			bool check(TokenKind kind) const;
			bool match(TokenKind kind);

			SExprPtr parse_expression();
			SExprPtr parse_list();
			SExprPtr parse_quote();
	};
}
