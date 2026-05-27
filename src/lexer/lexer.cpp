#include "lexer.hpp"

#include <iostream>
#include <cctype>
#include <utility>

namespace tscm {
	namespace {
		constexpr char kNullCharacter = '\0';
	} //namespace
	
	std::string token_kind_to_string(TokenKind kind){
		switch(kind){
			case TokenKind::LeftParen: return "LeftParen";
			case TokenKind::RightParen: return "RightParen";
			case TokenKind::Integer: return "Integer";
			case TokenKind::Symbol: return "Symbol";
			case TokenKind::Quote: return "Quote";
			case TokenKind::EndOfFile: return "EndOfFile";
			case TokenKind::Invalid: return "Invalid";
		}
		return "Unknown";
	}

	Lexer::Lexer(std::string source)
		: source_(std::move(source)), current_(0) {}

	std::vector<Token> Lexer::tokenize() {
		std::vector<Token> tokens;

		while(!is_at_end()){
			skip_whitespace();

			if (is_at_end()) break;
			const char c = peek();
			switch(c){
				case '(':
					advance();
					tokens.emplace_back(TokenKind::LeftParen, "(");
					break;
				case ')':
					advance();
					tokens.emplace_back(TokenKind::RightParen, "(");
					break;
				case '\'':
					advance();
					tokens.emplace_back(TokenKind::Quote, "'");
					break;
				default:
					if(std::isdigit(static_cast<unsigned char>(c))){
						tokens.push_back(lex_number());
					} else if (is_symbol_initial(c)){
						tokens.push_back(lex_symbol());
					} else {
						advance();
						tokens.emplace_back(TokenKind::Invalid, std::string(1, c));
					}
					break;
			}
		}

		tokens.emplace_back(TokenKind::EndOfFile, "");
		return tokens;
	}

	bool Lexer::is_at_end() const {
		return current_ >= source_.size();
	}

	char Lexer::peek() const {
		if (is_at_end()){
			return kNullCharacter;
		}

		return source_[current_];
	}

	char Lexer::advance() {
		const char c = peek();
		if (!is_at_end()){
			++current_;
		}
		return c;
	}

	void Lexer::skip_whitespace() {
		while(!is_at_end()){
			const char c = peek();
			if(!std::isspace(static_cast<unsigned char>(c))){
				break;
			}
			advance();
		}
	}

	Token Lexer::lex_number() {
		const std::size_t start = current_;

		while(!is_at_end() && std::isdigit(static_cast<unsigned char>(peek()))) {
			advance();
		}
		return Token(TokenKind::Integer, source_.substr(start, current_ - start));
	}

	Token Lexer::lex_symbol() {
		const std::size_t start = current_;
		while(!is_at_end() && is_symbol_subsequent(peek())) {
			advance();
		}
		return Token(TokenKind::Symbol, source_.substr(start, current_ - start));
	}

	bool Lexer::is_symbol_initial(char c){
		return std::isalpha(static_cast<unsigned char>(c)) ||
			c == '+' ||
			c == '-' ||
			c == '*' ||
			c == '/' ||
			c == '<' ||
			c == '>' ||
			c == '=' ||
			c == '?' ||
			c == '!';
	}

	 bool Lexer::is_symbol_subsequent(char c){
		return is_symbol_initial(c) ||
			std::isdigit(static_cast<unsigned char>(c));
	 }
} 
