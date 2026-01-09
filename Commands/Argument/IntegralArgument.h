//
// Created by Luka Robajac on 5. 1. 2026..
//

#ifndef PROJEKAT_INTEGRALARGUMENT_H
#define PROJEKAT_INTEGRALARGUMENT_H
#include "Argument.h"

class IntegralArgument: public Argument
{
public:
    IntegralArgument(Token* token);
    std::string getValue() override;
};


#endif //PROJEKAT_INTEGRALARGUMENT_H