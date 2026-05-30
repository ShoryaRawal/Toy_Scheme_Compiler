# Introduction
This project is a simple compiler for a scheme-like toy language for educational purposes.

# Current Filestructure

```
.
├── include
│   ├── core
│   │   ├── core_error.hpp
│   │   ├── core_expr.hpp
│   │   ├── core_printer.hpp
│   │   ├── core_program.hpp
│   │   ├── core_validator.hpp
│   │   └── lowerer.hpp
│   ├── runtime
│   │   ├── environment.hpp
│   │   ├── evaluator.hpp
│   │   ├── value_kind.hpp
│   │   └── value.hpp
│   ├── support
│   │   ├── asserts.hpp
│   │   ├── error.hpp
│   │   ├── panic.hpp
│   │   └── result.hpp
│   ├── syntax
│   │   ├── parser.hpp
│   │   ├── s_expr.hpp
│   │   ├── syntax_printer.hpp
│   │   └── syntax_program.hpp
│   ├── lexer.hpp
│   └── token.hpp
├── src
│   ├── core
│   │   ├── core_printer.cpp
│   │   ├── core_validator.cpp
│   │   └── lowerer.cpp
│   ├── lexer
│   │   └── lexer.cpp
│   ├── runtime
│   │   ├── environment.cpp
│   │   ├── evaluator.cpp
│   │   └── value.cpp
│   ├── support
│   │   ├── error.cpp
│   │   └── panic.cpp
│   ├── syntax
│   │   ├── parser.cpp
│   │   └── syntax_printer.cpp
│   └── main.cpp
├── CMakeLists.txt
├── README.md
└── update_readme.sh

12 directories, 35 files
```
