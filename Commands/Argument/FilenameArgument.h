//
// Created by Luka Robajac on 5. 1. 2026..
//

#ifndef PROJEKAT_FILENAMEARGUMENT_H
#define PROJEKAT_FILENAMEARGUMENT_H
#include "Argument.h"


class FilenameArgument: public Argument
{
public:
    FilenameArgument(Token* token);
    std::string getValue() override;
};


#endif //PROJEKAT_FILENAMEARGUMENT_H