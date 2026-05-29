#pragma once

#include <variant>
#include <utility>

#include "support/error.hpp"

namespace tscm{
	template<typename T> class Result{
		public: 
			Result(const T & value) : storage_(value) {}
			Result(T && value) : storage_(std::move(value)) {}
			Result(const CompilerError & error) : storage_(error) {}
			Result(CompilerError && error) : storage_(std::move(error)) {}

			bool has_value() const { return std::holds_alternative<T>(storage_); }

			explicit operator boot() const { return has_value(); }

			const T & value() const { return std::get<T>(storage_); }
			const CompilerError & error() const { return std::get<CompilerError>(storage_); }

			T & value() { return std::get<T>(storage_); }

		private:
			std::variant<T, CompilerError> storage_;
	};
}
