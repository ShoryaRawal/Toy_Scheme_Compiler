#pragma once

#include <string>
#include <unordered_map>

#include "runtime/value.hpp"

namespace tscm {
	class Environment {
		public:
			void define(const std::string & name, Value value);
			Value lookup(const std::string & name) const;
		
		private:
			std::unordered_map<std::string, Value> bindings_;
	};
}
