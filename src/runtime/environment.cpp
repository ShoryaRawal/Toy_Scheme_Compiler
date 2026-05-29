#include "runtime/environment.hpp"
#include <stdexcept>

namespace tscm{
	void Environment::define(const std::string & name, Value value){ 
		bindings_[name] = value;
	}

	Value Environment::lookup(const std::string & name) const {
		auto it = bindings_.find(name);

		if (it == bindings_.end()) 
			throw std::runtime_error("Undefined Variable: " + name);
		return it->second;
	}
}
