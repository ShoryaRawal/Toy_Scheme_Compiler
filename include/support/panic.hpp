#pragma once

#include <string>

namespace tscm {
	[[noreturn]]
	void panic(const std::string & message);
}
