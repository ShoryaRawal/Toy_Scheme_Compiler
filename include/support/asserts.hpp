#pragma once

#include "support/panic.hpp"

#define TSCM_ASSERT(condition, message) \
	do {								\
		if(!(condition)){				\
			tscm::panic(message);		\
		}								\
	} while (false)						
