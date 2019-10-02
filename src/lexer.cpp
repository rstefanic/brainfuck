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
            
            if (token != COMMENT) {
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
                return INC_DATA_PTR;
            case '<':
                return DEC_DATA_PTR;
            case '+':
                return INC_BYTE;
            case '-':
                return DEC_BYTE;
            case '.':
                return OUTPUT_BYTE;
            case ',':
                return INPUT_BYTE;
            case '[':
                return BYTE_EQ_ZERO;
            case ']':
                return BYTE_NEQ_ZERO;
            default:
                return COMMENT;
        }
    }
    
    std::ostream& operator<<(std::ostream& out, const BF_TOKEN instruction) {
        static std::map<BF_TOKEN, std::string> strings;
        if (strings.size() == 0) {
    #define INSERT_ELEMENT(p) strings[p] = #p
            INSERT_ELEMENT(INVALID_TOKEN);
            INSERT_ELEMENT(INC_DATA_PTR);
            INSERT_ELEMENT(DEC_DATA_PTR);
            INSERT_ELEMENT(INC_BYTE);
            INSERT_ELEMENT(DEC_BYTE);
            INSERT_ELEMENT(OUTPUT_BYTE);
            INSERT_ELEMENT(INPUT_BYTE);
            INSERT_ELEMENT(BYTE_EQ_ZERO);
            INSERT_ELEMENT(BYTE_NEQ_ZERO);
    #undef INSERT_ELEMENT
        }
        
        return out << strings[instruction];
    }
}