#include "../inc/parser.h"

namespace Parser {
    bool parse(BF_TOKEN* tokens) {
        
        std::vector<AST::Expression*> expressions;
        
        for (BF_TOKEN** token = &tokens; **token != INVALID_TOKEN;) {
            switch(**token) {
                case INC_DATA_PTR:
                    expressions.push_back(parse_inc_data_ptr(token));
                    break;
                case DEC_DATA_PTR:
                    expressions.push_back(parse_dec_data_ptr(token));
                    break;
                case INC_BYTE:
                    expressions.push_back(parse_inc_byte(token));
                    break;
                case DEC_BYTE:
                    expressions.push_back(parse_dec_byte(token));
                    break;
                case OUTPUT_BYTE:
                    expressions.push_back(parse_output_byte(token));
                    break;
                case INPUT_BYTE:
                    expressions.push_back(parse_input_byte(token));
                    break;
                case BYTE_EQ_ZERO:
                    expressions.push_back(parse_loop(token));
                    break;
                case BYTE_NEQ_ZERO:
                    return false;
                case COMMENT:
                    (*token)++;
                case INVALID_TOKEN:
                    break;
            }
        }
            
        //     if (*t == BYTE_EQ_ZERO) {
        //         open_loops++;
        //     } 
        //     else if (*t == BYTE_NEQ_ZERO) {
        //         open_loops--;
        //     }
            
        //     if (open_loops < 0) {
        //         return false;
        //     }
        // }
        
        //return true;open_loops == 0;
        return true;
    }

    AST::Expression* parse_inc_data_ptr(BF_TOKEN** token) {
        AST::IncDataPtr* inc_data_ptr = new AST::IncDataPtr();

        while(**token == INC_DATA_PTR) {
            inc_data_ptr->increment();
            (*token)++;
        }
        
        std::cout << "inc dptr \n";

        return inc_data_ptr;
    }
    
    AST::Expression* parse_dec_data_ptr(BF_TOKEN** token) {
        AST::DecDataPtr* dec_data_ptr = new AST::DecDataPtr();

        while(**token == DEC_DATA_PTR) {
            dec_data_ptr->decrement();
            (*token)++;
        }

        return dec_data_ptr;
    }
    
    AST::Expression* parse_inc_byte(BF_TOKEN** token) {
        AST::IncByte* inc_byte = new AST::IncByte();

        while(**token == INC_BYTE) {
            inc_byte->increment();
            (*token)++;
        }
        
        return inc_byte;
    }
    
    AST::Expression* parse_dec_byte(BF_TOKEN** token) {
        AST::DecByte* dec_byte = new AST::DecByte();

        while(**token == DEC_BYTE) {
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