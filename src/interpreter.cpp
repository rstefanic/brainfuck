#include "../inc/interpreter.h"

namespace Interpreter {
    void Environment::Eval() 
    {
#if DEBUG
        debug_print_ast();
#endif

        for(auto node: _ast) {
            evaluate_node(node);
        }
    }
    
    void Environment::evaluate_node(AST::Node* node) 
    {
        switch(node->instruction()) {
            case AST::INCREMENT_DATA_PTR:
                for(int i = 0; i < node->value(); i++) {
                    increment_data_ptr();
                }
                break;
            case AST::DECREMENT_DATA_PTR:
                for(int i = 0; i < node->value(); i++) {
                    decrement_data_ptr();
                }
                break;
            case AST::INCREMENT_BYTE:
                for(int i = 0; i < node->value(); i++) {
                    increment_byte();
                }
                break;
            case AST::DECREMENT_BYTE:
                for(int i = 0; i < node->value(); i++) {
                    decrement_byte();
                }
                break;
            case AST::OUTPUT_BYTE:
                output_byte();
                break;
            case AST::INPUT_BYTE:
                input_byte();
                break;
            case AST::LOOP:
                evaluate_loop(node->sub_nodes);
                break;
        }
    }
    
    void Environment::evaluate_loop(std::vector<AST::Node*> subexpression) 
    {
        if (jump_eq_zero()) {
            return;
        }
        
        for(auto node: subexpression) {
            evaluate_node(node);
        }
        
        if (jump_neq_zero()) {
            evaluate_loop(subexpression);
        }
    }
    
#if DEBUG
    void Environment::debug_print_ast() 
    {
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
    
    void Environment::handle_loop_print(AST::Node* node, int loop_indent) 
    {
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
