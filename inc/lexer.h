#pragma once
#include "main.h"

enum BF_TOKEN {
    INVALID_INSTRUCTION,
    INC_DATA_PTR,
    DEC_DATA_PTR,
    INC_BYTE,
    DEC_BYTE,
    OUTPUT_BYTE,
    INPUT_BYTE,
    BYTE_EQ_ZERO,
    BYTE_NEQ_ZERO
};

namespace Lexer 
{
    BF_TOKEN* lex(std::istream& stream);
    BF_TOKEN get_instruction(char ch);
    std::ostream& operator<<(std::ostream& out, const BF_TOKEN instruction);
}