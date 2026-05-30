#pragma once

#include "backend/assembly_program.hpp"
#include <ostream>

namespace tscm{
	class X86Printer{
		public:
			explicit X86Printer( std::ostream & output );
			void print( const AssemblyProgram & program );

		private:
			std::ostream & output_;
	};
}
