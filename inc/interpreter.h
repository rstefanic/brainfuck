#pragma once
#include <iostream>
#include <vector>

#include "ast.h"

#define DEBUG 0

namespace Interpreter {
    class Environment {
    public:
        Environment(std::vector<AST::Node*> ast) :
            _ast(ast) {};
        void Eval();

    private:
        std::vector<AST::Node*> _ast;
        char _tape[30000] = {0};
        char* _ptr = _tape;
        
#if DEBUG
        void debug_print_ast();
        void handle_loop_print(AST::Node* node, int loop_indent);
#endif
    };
}