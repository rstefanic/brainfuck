#include "../inc/parser.h"

namespace Parser {
    bool parse(BF_TOKEN* tokens) {
        
        std::vector<AST::Expression*> expressions;
        
        for (BF_TOKEN** token = &tokens; **token != INVALID_TOKEN;) {
            switch(**token) {
                case RIGHT_ANGLE_TOKEN:
                    expressions.push_back(parse_inc_data_ptr(token));
                    break;
                case LEFT_ANGLE_TOKEN:
                    expressions.push_back(parse_dec_data_ptr(token));
                    break;
                case PLUS_TOKEN:
                    expressions.push_back(parse_inc_byte(token));
                    break;
                case MINUS_TOKEN:
                    expressions.push_back(parse_dec_byte(token));
                    break;
                case PERIOD_TOKEN:
                    expressions.push_back(parse_output_byte(token));
                    break;
                case COMMA_TOKEN:
                    expressions.push_back(parse_input_byte(token));
                    break;
                case LEFT_BRACKET_TOKEN:
                    expressions.push_back(parse_loop(token));
                    break;
                case RIGHT_BRACKET_TOKEN:
                    return false;
                case COMMENT_TOKEN:
                    (*token)++;
                case INVALID_TOKEN:
                    break;
            }
        }

        return true;
    }

    AST::Expression* parse_inc_data_ptr(BF_TOKEN** token) {
        AST::IncDataPtr* inc_data_ptr = new AST::IncDataPtr();

        while(**token == RIGHT_ANGLE_TOKEN) {
            inc_data_ptr->increment();
            (*token)++;
        }
        
        std::cout << "inc dptr \n";

        return inc_data_ptr;
    }
    
    AST::Expression* parse_dec_data_ptr(BF_TOKEN** token) {
        AST::DecDataPtr* dec_data_ptr = new AST::DecDataPtr();

        while(**token == LEFT_ANGLE_TOKEN) {
            dec_data_ptr->decrement();
            (*token)++;
        }

        return dec_data_ptr;
    }
    
    AST::Expression* parse_inc_byte(BF_TOKEN** token) {
        AST::IncByte* inc_byte = new AST::IncByte();

        while(**token == PLUS_TOKEN) {
            inc_byte->increment();
            (*token)++;
        }
        
        return inc_byte;
    }
    
    AST::Expression* parse_dec_byte(BF_TOKEN** token) {
        AST::DecByte* dec_byte = new AST::DecByte();

        while(**token == MINUS_TOKEN) {
            dec_byte->decrement();
            (*token)++;
        }

        return dec_byte;
    }
    
    AST::Expression* parse_output_byte(BF_TOKEN** token) {
        AST::OutputByte* output_byte = new AST::OutputByte();
        (*token)++;
        return output_byte;
    }
    
    AST::Expression* parse_input_byte(BF_TOKEN** token) {
        AST::InputByte* input_byte = new AST::InputByte();
        (*token)++;
        return input_byte;
    }
    
    AST::Expression* parse_loop(BF_TOKEN** token) {
        (*token)++;
        return new AST::Loop();
    }
}