#include "../inc/parser.h"

namespace Parser {
    bool parse(BF_TOKEN* tokens) {
        int open_loops = 0;
        
        for (BF_TOKEN* t = tokens; *t != INVALID_TOKEN; t++) {
            if (*t == BYTE_EQ_ZERO) {
                open_loops++;
            } 
            else if (*t == BYTE_NEQ_ZERO) {
                open_loops--;
            }
            
            if (open_loops < 0) {
                return false;
            }
        }
        
        return open_loops == 0;
    }
}