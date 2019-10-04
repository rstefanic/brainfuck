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
        char _state[30000] = {0};
        char* _ptr = _state;

        void evaluate_node(AST::Node* node);
        void increment_data_ptr() { _ptr++; }
        void decrement_data_ptr() { _ptr--; }
        void increment_byte() { (*_ptr)++; }
        void decrement_byte() { (*_ptr)--; }
        bool jump_eq_zero() { return *_ptr == 0; }
        bool jump_neq_zero() { return *_ptr != 0; }
        void output_byte() { std::cout << *_ptr; };
        void input_byte() { std::cin >> *_ptr; };
        void evaluate_loop(std::vector<AST::Node*> subexpression);
#if DEBUG
        void debug_print_ast();
        void handle_loop_print(AST::Node* node, int loop_indent);
#endif
    };
}