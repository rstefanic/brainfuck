#include "../inc/interpreter.h"

namespace Interpreter {
    void Environment::Eval() {
        std::cout << "Evaluating...\n";
#if DEBUG
        debug_print_ast();
#endif
    }
    
#if DEBUG
    void Environment::debug_print_ast() {
        int loop_indent = 0;
        for(auto n: _ast) {
            if (n->instruction() == AST::LOOP) {
                handle_loop_print(n, ++loop_indent);
                loop_indent--;
            }
            else {
                std::cout << "INS: " << n->instruction() << " - VAL: " << n->value() << "\n";                 
            }
        }
    }
    
    void Environment::handle_loop_print(AST::Node* node, int loop_indent) {
        std::string indent_prefix = "";
        for (int i = 0; i < loop_indent; i++) {
            indent_prefix += "\t";
        }
        std::cout << indent_prefix << "Loop Start\n";
        for (auto n: node->subexpressions) {
            if (n->instruction() == AST::LOOP) {
                handle_loop_print(n, ++loop_indent);
                loop_indent--;
            }
            else  {
                std::cout << indent_prefix << "\t" << n->instruction() << " -- VAL: " << n->value() << "\n";
            }
        }
        
        std::cout << indent_prefix << "Loop End\n";
    }
#endif
}
