//
// Created by Luka Robajac on 8. 1. 2026..
//

#ifndef PROJEKAT_CINARGUMENT_H
#define PROJEKAT_CINARGUMENT_H
#include "Argument.h"


class CinArgument: public Argument
{
public:
    CinArgument();
    std::string getValue() override;
};


#endif //PROJEKAT_CINARGUMENT_H