#include "inc/main.h"
#include "inc/lexer.h"
#include "inc/parser.h"

int main(int argc, char** argv) {

    if (argc > 1) {
        std::ifstream stream = std::ifstream(argv[1]);
        
        if (stream.is_open()) {
            BF_TOKEN* tokens = Lexer::lex(stream);

            bool successful_parse = Parser::parse(tokens);

            if (!successful_parse) {
                std::cout << "ERR: Brakets do not match\n";
                free(tokens);
                return -1; 
            }
            else {
                std::cout << "Brackets match!\n";
            }

            free(tokens);
        }
    }
    else {
        std::cout << "No file given as an argument.\n";
        return -1;
    }

    return 0;
}

