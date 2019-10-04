#pragma once
#include <stdlib.h>

#include "ast.h"
#include "lexer.h"
#include <vector>

namespace Parser {
    std::vector<AST::Node*> parse(BF_TOKEN* tokens);
    AST::Node* parse_inc_data_ptr(BF_TOKEN** t_pos);
    AST::Node* parse_dec_data_ptr(BF_TOKEN** t_pos);
    AST::Node* parse_inc_byte(BF_TOKEN** t_pos);
    AST::Node* parse_dec_byte(BF_TOKEN** t_pos);
    AST::Node* parse_output_byte(BF_TOKEN** t_pos);
    AST::Node* parse_input_byte(BF_TOKEN** t_pos);
    AST::Node* parse_loop(BF_TOKEN** t_pos);
    std::string parse_error(std::string error_message);
}
