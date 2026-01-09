//
// Created by Luka Robajac on 29. 12. 2025..
//

#include "Token.h"

#include <iostream>
#include <ostream>

#include "../Commands/Argument/FilenameArgument.h"
#include "../Commands/Argument/IntegralArgument.h"
#include "../Commands/Argument/OptionArgument.h"

Token::Token(const std::string& token, const size_t pos)
{
    this->token = token;
    this->pos = pos;
}

size_t Token::getPos() const
{
    return this->pos;
}

std::string Token::getToken()
{
    return this->token;
}

Argument* Token::toArgument()
{
    if (this->isIntegral())
    {
        return new IntegralArgument(this);
    }

    if (this->isOpt())
    {
        return new OptionArgument(this);
    }

    return new FilenameArgument(this);
}


bool Token::isOpt() const
{
    return !this->token.empty() &&
        this->token.at(0) == '-';
}

bool Token::isFilename() const
{
    return !this->isOpt() &&
        !this->isIntegral() &&
        !this->isInputRedirect() &&
        !this->isOutputRedirect();
}

bool Token::isIntegral() const
{
    return !this->token.empty() &&
        this->token.at(0) == '"' &&
        this->token.at(this->token.size() - 1) == '"';
}

bool Token::isInputRedirect() const
{
    return this->token.size() >= 2 &&
        this->token.at(0) == '<';
}

bool Token::isDoubleOutputRedirect() const
{
    return this->token.size() > 2 &&
        this->token.at(0) == '>' &&
        this->token.at(1) == '>';
}

/**
 * @return If token is ANY kind of output redirection (single or double)
 */
bool Token::isOutputRedirect() const
{
    return this->token.size() >= 2 &&
        this->token.at(0) == '>';
}
