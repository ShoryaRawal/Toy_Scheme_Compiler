# Introduction
This project is a simple compiler for a scheme-like toy language for educational purposes.

# Current Filestructure

```
.
├── include
│   ├── core
│   │   ├── core_expr.hpp
│   │   ├── core_printer.hpp
│   │   ├── core_program.hpp
│   │   └── lowerer.hpp
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
│   │   └── lowerer.cpp
│   ├── lexer
│   │   └── lexer.cpp
│   ├── syntax
│   │   ├── parser.cpp
│   │   └── syntax_printer.cpp
│   └── main.cpp
├── CMakeLists.txt
├── README.md
└── update_readme.sh

8 directories, 19 files
```
