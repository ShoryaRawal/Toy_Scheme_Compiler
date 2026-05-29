#pragma once

#include <vector>

#include "core/core_error.hpp"
#include "core/core_program.hpp"

namespace tscm{
	class CoreValidator{
		public: 
			std::vector<CoreError> validate(const CoreProgram & program);

		private:
			void validate_expression(const CoreExprPtr & expr);
		private:
			std::vector<CoreError> errors_;

	};
}
