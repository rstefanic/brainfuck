#include "inc/main.h"
#include "inc/lexer.h"
#include "inc/parser.h"

void handle_loop_print(AST::Node* node);

int main(int argc, char** argv) {

    if (argc > 1) {
        std::ifstream stream = std::ifstream(argv[1]);
        
        if (stream.is_open()) {
            BF_TOKEN* tokens = Lexer::lex(stream);

            std::vector<AST::Node*> ast = Parser::parse(tokens);
            
            for(auto n: ast) {
                if (n->instruction() == AST::LOOP) {
                    handle_loop_print(n);
                }
                else {
                    std::cout << "INS: " << n->instruction() << " - VAL: " << n->value() << "\n";
                }
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

void handle_loop_print(AST::Node* node) {
    std::cout << "In Loop:\n";
    for (auto n: node->subexpressions) {
        if (n->instruction() == AST::LOOP) {
            handle_loop_print(n);
        }
        else  {
            std::cout << "\t" << n->instruction() << " -- VAL: " << n->value() << "\n";
        }
    }
    
    std::cout << "Loop Exit\n";
}