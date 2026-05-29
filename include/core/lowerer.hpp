#pragma once

#include "core/core_expr.hpp"
#include "syntax/s_expr.hpp"
#include "syntax/syntax_program.hpp"

namespace tscm{
	class Lowerer{
		public:
			CoreProgram lower_program(const SyntaxProgram & program);
		private:
			CoreExprPtr lower_expression(const SExprPtr & expr);
			CoreExprPtr lower_list(const ListExpr & list);
			CoreExprPtr lower_define(const ListExpr & list);
			CoreExprPtr lower_if(const ListExpr & list);
			CoreExprPtr lower_call(const ListExpr & list);
			CoreExprPtr lower_lambda(const ListExpr & list);
	};
}
