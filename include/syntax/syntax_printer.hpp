#pragma once

#include <iostream>
#include "syntax/program.hpp"
#include "syntax/s_expr.hpp"

namespace tscm {
	class SyntaxPrinter{
		public:
			explicit SyntaxPrinter(std::ostream & output);

			void print_program(const Program & program);
			void print_expression(const SExprPtr & expr, int indent = 0);

		private:
			std::ostream & output_;
	};
}
