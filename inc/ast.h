#pragma once
#include <vector>

namespace AST {
    enum INSTRUCTION {
        INCREMENT_DATA_PTR,
        DECREMENT_DATA_PTR,
        INCREMENT_BYTE,
        DECREMENT_BYTE,
        OUTPUT_BYTE,
        INPUT_BYTE,
        LOOP
    };
    
    class Node {
    public:
        Node(INSTRUCTION instruction) :
            _instruction(instruction) {};
            
        void increment() { _value++; }
        inline INSTRUCTION instruction() { return _instruction; }
        int value() { return _value; }
        std::vector<Node*> sub_nodes;
        
    private:
        INSTRUCTION _instruction;
        int _value = 0;
    };
}