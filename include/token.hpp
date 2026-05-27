#pragma once

#include <cstdint>
#include <string>

namespace tscm {
	enum class TokenKind {
		LeftParen,
		RightParen,
		Integer,
		Symbol,
		Quote,
		EndOfFile,
		Invalid
	};

	struct Token {
		TokenKind kind;
		std::string lexeme;

		Token(TokenKind token_kind, std::string token_lexeme)
			: kind(token_kind),
			lexeme(std::move(token_lexeme)) {}
	};

	std::string token_kind_to_string(TokenKind kind);
}
