#pragma once

#include "runtime/environment.hpp"
#include "core/core_expr.hpp"
#include "core/core_program.hpp"

namespace tscm{
	class Evaluator{
		public:
			Value evaluate_program(const CoreProgram & program);

		private:
			Value evaluate_expression(const CoreExprPtr & expr);
			Value evaluate_call(const CoreCallExpr & call);

		private:
			Environment global_environment_;
	};
}
