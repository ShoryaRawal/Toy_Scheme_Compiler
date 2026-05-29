#pragma once

#include <vector>
#include "core/core_expr.hpp"

namespace tscm{
	struct CoreProgram { std::vector<CoreExprPtr> expressions; };
}
