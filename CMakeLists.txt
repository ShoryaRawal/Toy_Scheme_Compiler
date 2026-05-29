cmake_minimum_required(VERSION 3.16)
project(Toy_Scheme_Compiler)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(
	scheme_compiler
	src/main.cpp
	src/lexer/lexer.cpp
	src/syntax/parser.cpp
	src/syntax/syntax_printer.cpp
	src/core/core_printer.cpp
	src/core/lowerer.cpp
	src/core/core_validator.cpp
	src/support/error.cpp
	src/support/panic.cpp
	src/runtime/value.cpp
	src/runtime/environment.cpp
	src/runtime/evaluator.cpp
)

target_include_directories(
	scheme_compiler
	PRIVATE
	include
)
