#include "support/panic.hpp"

#include <cstdlib>
#include <iostream>

namespace tscm {
	[[noreturn]]
	void panic(const std::string & message) {
		std::cerr << "Internal Compiler Error: " << message << "\n";
		std::abort();
	}
}
