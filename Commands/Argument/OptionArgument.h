//
// Created by Luka Robajac on 5. 1. 2026..
//

#ifndef PROJEKAT_OPTIONARGUMENT_H
#define PROJEKAT_OPTIONARGUMENT_H
#include "Argument.h"


class OptionArgument: public Argument
{
public:
    OptionArgument(Token* token);
    std::string getValue() override;
};


#endif //PROJEKAT_OPTIONARGUMENT_H