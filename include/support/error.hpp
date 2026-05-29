#pragma once

#include <string>

namespace tscm {
	enum class ErrorKind{
		LexicalError,
		ParseError,
		LoweringError,
		ValidationError,
		RuntimeError,
		InternalCompilerError
	};

	struct CompilerError{
		ErrorKind kind;
		std::string message;
		CompilerError() = default;
		CompilerError(ErrorKind error_kind, std::string error_message)
			: kind(error_kind), message(std::move(error_message)) {}
	};
}
