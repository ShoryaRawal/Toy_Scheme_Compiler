#pragma once

#include <string>

namespace tscm{
	class Toolchain{
		public:
			void assemble_and_link(
				const std::string & asm_file,
				const std::string & object_file,
				const std::string & executable_file
			);
	};
}
