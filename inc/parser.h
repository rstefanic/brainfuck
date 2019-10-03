#include "ast.h"
#include "lexer.h"
#include <vector>

namespace Parser 
{
    bool parse(BF_TOKEN* tokens);
    AST::Expression* parse_inc_data_ptr(BF_TOKEN** t_pos);
    AST::Expression* parse_dec_data_ptr(BF_TOKEN** t_pos);
    AST::Expression* parse_inc_byte(BF_TOKEN** t_pos);
    AST::Expression* parse_dec_byte(BF_TOKEN** t_pos);
    AST::Expression* parse_output_byte(BF_TOKEN** t_pos);
    AST::Expression* parse_input_byte(BF_TOKEN** t_pos);
    AST::Expression* parse_loop(BF_TOKEN** t_pos);
}
