#pragma once

#include <vector>
#include "syntax/s_expr.hpp"

namespace tscm{
	struct SyntaxProgram { std:: vector<SExprPtr> expressions; };
}
