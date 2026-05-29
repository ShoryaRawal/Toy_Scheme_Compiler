#include "runtime/value.hpp"

namespace tscm{
	Value::Value() : value_(0) {}
	Value::Value(std::int64_t value) : value_(value) {}
	
	std::int64_t Value::as_integer() const { return value_; }
}
