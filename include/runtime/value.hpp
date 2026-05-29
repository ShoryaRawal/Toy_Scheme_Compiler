#pragma once 
#include <cstdint>

namespace tscm {
	class Value{
		public: 
			Value();
			explicit Value(std::int64_t value);
			std::int64_t as_integer() const;

		private:
			std::int64_t value_;
	};
}
