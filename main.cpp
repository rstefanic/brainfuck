#include "inc/interpreter.h"
#include "inc/lexer.h"
#include "inc/main.h"
#include "inc/parser.h"

void run_repl(std::istream& input);
int count_open_braces(std::string line);

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
        run_repl(std::cin);
        return -1;
    }

    return 0;
}

void run_repl(std::istream& input)
{
    const std::string new_command_prompt = ">> ";
    const std::string continuing_command_prompt = ".. ";
    bool running = true;

    std::cout << "Brainfuck 1.0.0\n";
    std::cout << "Type \"quit\" to quit.\n";

    while (running) {
        std::string code;
        int open_braces = 0;

        std::cout << new_command_prompt;

        for (std::string line; std::getline(input, line);) {

            if (line.compare("quit") == 0) {
                return;
            }

            code += line;

            open_braces += count_open_braces(line);
            if (open_braces == 0) {
                break;
            }

            std::cout << continuing_command_prompt;
        }

        std::stringstream ss;
        ss.str(code);
        BF_TOKEN* tokens = Lexer::lex(ss);
        std::vector<AST::Node*> ast = Parser::parse(tokens);
        auto evaluator = new Interpreter::Environment(ast);
        evaluator->Eval();
    }
}

int count_open_braces(std::string line)
{
    int open_braces = 0;

    for(char& c: line) {
        switch(c) {
            case '[': open_braces++; break;
            case ']': open_braces--; break;
        }
    }

    return open_braces;
}