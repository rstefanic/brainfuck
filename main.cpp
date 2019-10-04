#include "inc/interpreter.h"
#include "inc/lexer.h"
#include "inc/main.h"
#include "inc/parser.h"

void handle_loop_print(AST::Node* node);

int main(int argc, char** argv) 
{
    if (argc > 1) {
        std::ifstream stream = std::ifstream(argv[1]);
        
        if (stream.is_open()) {
            BF_TOKEN* tokens = Lexer::lex(stream);

            std::vector<AST::Node*> ast = Parser::parse(tokens);

            auto evaluator = new Interpreter::Environment(ast);

            evaluator->Eval();
            
            free(tokens);
        }
    }
    else {
        std::cout << "No file given as an argument.\n";
        return -1;
    }

    return 0;
}
