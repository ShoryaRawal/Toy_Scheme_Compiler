#pragma once

#include <vector>
#include "syntax/s_expr.hpp"

namespace tscm{
	struct Program { std:: vector<SExprPtr> expressions; };
}
