#pragma once

#include <ostream>
#include "core/core_program.hpp"

namespace tscm {
	class CorePrinter{
		public:
			explicit CorePrinter(std::ostream & output);
			void print_program(const CoreProgram & program);

		private:
			void print_expression(const CoreExprPtr & expr, int indent = 0);

		private:
			std::ostream & output_;
	};
}
