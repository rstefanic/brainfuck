#pragma once
#include "main.h"

enum BF_TOKEN {
    INVALID_TOKEN,
    RIGHT_ANGLE_TOKEN,
    LEFT_ANGLE_TOKEN,
    PLUS_TOKEN,
    MINUS_TOKEN,
    PERIOD_TOKEN,
    COMMA_TOKEN,
    LEFT_BRACKET_TOKEN,
    RIGHT_BRACKET_TOKEN,
    COMMENT_TOKEN
};

namespace Lexer {
    BF_TOKEN* lex(std::istream& stream);
    BF_TOKEN get_instruction(char ch);
    std::ostream& operator<<(std::ostream& out, const BF_TOKEN instruction);
}