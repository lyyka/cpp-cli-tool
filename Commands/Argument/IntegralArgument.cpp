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
    return this->token->getToken().substr(1, this->token->getToken().size() - 2);
}
