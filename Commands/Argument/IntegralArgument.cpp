//
// Created by Luka Robajac on 5. 1. 2026..
//

#include "IntegralArgument.h"

#include <iostream>

IntegralArgument::IntegralArgument(Token* token)
    : Argument(token)
{
}

std::string IntegralArgument::getValue()
{
    std::string rawValue = this->token->getToken().substr(1, this->token->getToken().size() - 2);

    // Escape the \n sequence with actual \n char
    size_t pos;
    while ((pos = rawValue.find("\\n")) != std::string::npos) {
        rawValue.replace(pos, 2, "\n");
    }

    return rawValue;
}
