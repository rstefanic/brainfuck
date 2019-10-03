#include <vector>

namespace AST {
    enum INSTRUCTION {
        INCREMENT_DATA_PTR,
        DECREMENT_DATA_PTR,
        INCREMENT_BYTE,
        DECREMENT_BYTE,
        OUTPUT_BYTE,
        INPUT_BYTE,
        BYTE_EQ_ZERO,
        BYTE_NEQ_ZERO 
    };
    
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
    
    class Node {
    public:
        Node(INSTRUCTION instruction) :
            _instruction(instruction) {};
        void increment() { _value++; }
        void decrement() { _value--; }
        INSTRUCTION instruction() { return _instruction; }
        int value() { return _value; }
        
    private:
        INSTRUCTION _instruction;
        int _value = 0;
    };
}