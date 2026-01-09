//
// Created by Luka Robajac on 29. 12. 2025..
//

#ifndef PROJEKAT_UNKNOWNCOMMAND_H
#define PROJEKAT_UNKNOWNCOMMAND_H
#include <stdexcept>

class UnknownCommand: public std::runtime_error
{
public:
    explicit UnknownCommand(const std::string& msg): std::runtime_error(msg) {};
};

#endif //PROJEKAT_UNKNOWNCOMMAND_H