#include "syntax/parser.hpp"
#include <memory>
#include <iostream>

namespace tscm{
	Parser::Parser(const std::vector<Token> & tokens)
		: tokens_(tokens), current_(0) {}
	
	//-----REDUNDANT CODE----------
	//SExprPtr Parser::parse() { 
	//	return parse_expression(); 
	//}
	//-----REMOVE AFTER UPDATE-----
	
	SyntaxProgram Parser::parse_program(){
		SyntaxProgram program;

		while(!is_at_end())
			program.expressions.push_back(parse_expression());
		
		return program;
	}


	bool Parser::is_at_end() const {
		return peek().kind == TokenKind::EndOfFile;
	}

	const Token & Parser::peek() const {
		return tokens_[current_];
	}

	const Token & Parser::advance() {
		if(!is_at_end()) ++current_;
		return tokens_[current_ - 1];
	}

	bool Parser::check(TokenKind kind) const {
		if(is_at_end()) return false;
		return peek().kind == kind;
	}

	bool Parser::match(TokenKind kind){
		if (check(kind)){
			advance();
			return true;
		}

		return false;
	}

	SExprPtr Parser::parse_expression(){
		if(match(TokenKind::Integer)) {
			const Token & token = tokens_[current_ - 1];
		
			return std::make_shared<SExpr>(
				IntegerExpr{ std::stoll(token.lexeme) }
			);
		}


		if(match(TokenKind::Symbol)) {
			const Token & token = tokens_[current_ - 1];

			return std::make_shared<SExpr>(
				SymbolExpr{ token.lexeme }
			);
		}

		if(match(TokenKind::Quote)) return parse_quote();
		if(match(TokenKind::LeftParen)) return parse_list();

		return nullptr;
	}

	SExprPtr Parser::parse_list(){
		ListExpr list;

		while(!check(TokenKind::RightParen) && !is_at_end())
			list.elements.push_back(parse_expression());

		match(TokenKind::RightParen);
		return std::make_shared<SExpr>(std::move(list));
	}

	SExprPtr Parser::parse_quote() {
		SExprPtr expr = parse_expression();
		return std::make_shared<SExpr>(QuoteExpr{ expr });
	}
}
