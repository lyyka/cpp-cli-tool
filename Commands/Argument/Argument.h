//
// Created by Luka Robajac on 5. 1. 2026..
//

#ifndef PROJEKAT_ARGUMENT_H
#define PROJEKAT_ARGUMENT_H
#include "../../Core/Token.h"

/**
 * 'Argument' is something that gives value to the command.
 */
class Argument
{
public:
    explicit Argument(): token(nullptr) {};
    explicit Argument(Token* token) : token(token) {}
    virtual ~Argument();
    [[nodiscard]] Token* getToken() const;
    virtual std::string getValue() = 0;
protected:
    Token* token;
};

inline Token* Argument::getToken() const
{
    return this->token;
}

inline Argument::~Argument()
{
    delete this->token;
}

#endif //PROJEKAT_ARGUMENT_H