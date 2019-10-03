#include <vector>

namespace AST {
    class Expression {};
    
    class ValExpression : public Expression {
    public:
        int amount = 0;
        void increment() { amount++; };
        void decrement() { amount--; };
    };

    class IncDataPtr : public ValExpression {};
    class DecDataPtr : public ValExpression {};
    class IncByte : public ValExpression {};
    class DecByte : public ValExpression {};
    class OutputByte : public Expression {};
    class InputByte : public Expression {};
    
    class Loop : public Expression {
    private:
        std::vector<Expression*> expressions;
    };
}