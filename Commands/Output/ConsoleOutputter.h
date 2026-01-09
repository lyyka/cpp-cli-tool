//
// Created by Luka Robajac on 7. 1. 2026..
//

#ifndef PROJEKAT_CONSOLEOUTPUTTER_H
#define PROJEKAT_CONSOLEOUTPUTTER_H
#include <string>

#include "Outputter.h"


class ConsoleOutputter: public Outputter
{
public:
    ConsoleOutputter* output(const std::string& content) override;
};


#endif //PROJEKAT_CONSOLEOUTPUTTER_H