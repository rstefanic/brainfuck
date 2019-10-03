#include "../inc/lexer.h"

namespace Lexer 
{
    BF_TOKEN* lex(std::istream& stream) {
        BF_TOKEN* tokens = new BF_TOKEN[30000] { INVALID_TOKEN };
        BF_TOKEN* token_ptr = tokens;

        char c;
        while (true) {
            stream >> c;
            
            if (!stream) {
                break;
            }
            
            BF_TOKEN token = get_instruction(c); 
            
            if (token != COMMENT_TOKEN) {
                *token_ptr = token;
                token_ptr++;
            }
        }
        
        for (token_ptr = tokens; *token_ptr != INVALID_TOKEN; token_ptr++) {
            std::cout << *token_ptr << "\n";
        }
        
        return tokens;
    }
    
    BF_TOKEN get_instruction(char ch) {
        switch (ch) {
            case '>':
                return RIGHT_ANGLE_TOKEN;
            case '<':
                return LEFT_ANGLE_TOKEN;
            case '+':
                return PLUS_TOKEN;
            case '-':
                return MINUS_TOKEN;
            case '.':
                return PERIOD_TOKEN;
            case ',':
                return COMMA_TOKEN;
            case '[':
                return LEFT_BRACKET_TOKEN;
            case ']':
                return RIGHT_BRACKET_TOKEN;
            default:
                return COMMENT_TOKEN;
        }
    }
    
    std::ostream& operator<<(std::ostream& out, const BF_TOKEN instruction) {
        static std::map<BF_TOKEN, std::string> strings;
        if (strings.size() == 0) {
    #define INSERT_ELEMENT(p) strings[p] = #p
            INSERT_ELEMENT(INVALID_TOKEN);
            INSERT_ELEMENT(RIGHT_ANGLE_TOKEN);
            INSERT_ELEMENT(LEFT_ANGLE_TOKEN);
            INSERT_ELEMENT(PLUS_TOKEN);
            INSERT_ELEMENT(MINUS_TOKEN);
            INSERT_ELEMENT(PERIOD_TOKEN);
            INSERT_ELEMENT(COMMA_TOKEN);
            INSERT_ELEMENT(LEFT_BRACKET_TOKEN);
            INSERT_ELEMENT(RIGHT_BRACKET_TOKEN);
    #undef INSERT_ELEMENT
        }
        
        return out << strings[instruction];
    }
}