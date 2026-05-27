#pragma once

#include <string>
#include <vector>

#include "token.hpp"

namespace tscm {
	class Lexer {
		public:
			explicit Lexer(std::string source);
			std::vector<Token> tokenize(); // Performs lexical analysis
		
		private:
			std::string source_;
			std::size_t current_;

		private:
			bool is_at_end() const;

			char peek() const;
			char advance();

			void skip_whitespace();

			Token lex_number();
			Token lex_symbol();

			static bool is_symbol_initial(char c);
			static bool is_symbol_subsequent(char c);
	};
}
