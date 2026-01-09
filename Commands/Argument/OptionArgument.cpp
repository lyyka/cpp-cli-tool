//
// Created by Luka Robajac on 5. 1. 2026..
//

#include "OptionArgument.h"

OptionArgument::OptionArgument(Token* token)
    : Argument(token)
{
}

std::string OptionArgument::getValue()
{
    // Returns the option name essentially
    return this->token->getToken().substr(1);
}