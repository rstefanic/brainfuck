#include "../inc/parser.h"

namespace Parser {
    std::vector<AST::Node*> parse(BF_TOKEN* tokens) 
    {
        std::vector<AST::Node*> expressions;
        
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
                    parse_error("Unmatched left bracket to start this right bracket.");
                case COMMENT_TOKEN:
                    (*token)++;
                case INVALID_TOKEN:
                    break;
            }
        }

        return expressions;
    }

    AST::Node* parse_inc_data_ptr(BF_TOKEN** token) 
    {
        AST::Node* inc_data_ptr = new AST::Node(AST::INCREMENT_DATA_PTR);

        while(**token == RIGHT_ANGLE_TOKEN) {
            inc_data_ptr->increment();
            (*token)++;
        }

        return inc_data_ptr;
    }
    
    AST::Node* parse_dec_data_ptr(BF_TOKEN** token) 
    {
        AST::Node* dec_data_ptr = new AST::Node(AST::DECREMENT_DATA_PTR);

        while(**token == LEFT_ANGLE_TOKEN) {
            dec_data_ptr->increment();
            (*token)++;
        }

        return dec_data_ptr;
    }
    
    AST::Node* parse_inc_byte(BF_TOKEN** token) 
    {
        AST::Node* inc_byte = new AST::Node(AST::INCREMENT_BYTE);

        while(**token == PLUS_TOKEN) {
            inc_byte->increment();
            (*token)++;
        }
        
        return inc_byte;
    }
    
    AST::Node* parse_dec_byte(BF_TOKEN** token) 
    {
        AST::Node* dec_byte = new AST::Node(AST::DECREMENT_BYTE);

        while(**token == MINUS_TOKEN) {
            dec_byte->increment();
            (*token)++;
        }

        return dec_byte;
    }
    
    AST::Node* parse_output_byte(BF_TOKEN** token) 
    {
        AST::Node* output_byte = new AST::Node(AST::OUTPUT_BYTE);
        (*token)++;
        return output_byte;
    }
    
    AST::Node* parse_input_byte(BF_TOKEN** token) 
    {
        AST::Node* input_byte = new AST::Node(AST::INPUT_BYTE);
        (*token)++;
        return input_byte;
    }
    
    AST::Node* parse_loop(BF_TOKEN** token) 
    {
        AST::Node* loop = new AST::Node(AST::LOOP);
        (*token)++; // parse the first left_bracket_token out
        
        while(**token != RIGHT_BRACKET_TOKEN && **token != INVALID_TOKEN) {
            switch(**token) {
                case RIGHT_ANGLE_TOKEN:
                    loop->subexpressions.push_back(parse_inc_data_ptr(token));
                    break;
                case LEFT_ANGLE_TOKEN:
                    loop->subexpressions.push_back(parse_dec_data_ptr(token));
                    break;
                case PLUS_TOKEN:
                    loop->subexpressions.push_back(parse_inc_byte(token));
                    break;
                case MINUS_TOKEN:
                    loop->subexpressions.push_back(parse_dec_byte(token));
                    break;
                case PERIOD_TOKEN:
                    loop->subexpressions.push_back(parse_output_byte(token));
                    break;
                case COMMA_TOKEN:
                    loop->subexpressions.push_back(parse_input_byte(token));
                    break;
                case LEFT_BRACKET_TOKEN:
                    loop->subexpressions.push_back(parse_loop(token));
                   break;
                case RIGHT_BRACKET_TOKEN:
                    parse_error("ERR: Unmatched Right Bracket");
                case COMMENT_TOKEN:
                    (*token)++;
                case INVALID_TOKEN:
                    break;
            }
        }
        
        if (**token == RIGHT_BRACKET_TOKEN) {
            (*token)++;
        }
        
        return loop;
    }
    
    std::string parse_error(std::string error_description) 
    {
        std::cout << "An error occured during parsing\n";
        std::cout << error_description << "\n";
        exit(EXIT_FAILURE);
    }
}