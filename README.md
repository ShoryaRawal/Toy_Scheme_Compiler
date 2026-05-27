# Introduction
This project is a simple compiler for a scheme-like toy language for educational purposes.

# Filestructure
```
├── include/
│   ├── token.hpp
│   ├── lexer.hpp
│   ├── parser.hpp
│   ├── ast.hpp
│   ├── value.hpp
│   ├── environment.hpp
│   ├── evaluator.hpp
│   ├── bytecode.hpp
│   ├── vm.hpp
│   └── repl.hpp
│
├── src/
│   ├── main.cpp
│   │
│   ├── lexer/
│   │   └── lexer.cpp
│   │
│   ├── parser/
│   │   └── parser.cpp
│   │
│   ├── ast/
│   │   └── ast.cpp
│   │
│   ├── runtime/
│   │   ├── value.cpp
│   │   ├── environment.cpp
│   │   └── evaluator.cpp
│   │
│   ├── vm/
│   │   ├── bytecode.cpp
│   │   ├── compiler.cpp
│   │   └── vm.cpp
│   │
│   └── repl/
│       └── repl.cpp

```
