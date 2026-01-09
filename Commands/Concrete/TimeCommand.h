//
// Created by Luka Robajac on 5. 1. 2026..
//

#ifndef PROJEKAT_TIMECOMMAND_H
#define PROJEKAT_TIMECOMMAND_H
#include <iostream>
#include <string>

#include "../Command.h"

class TimeCommand: public Command
{
public:
    TimeCommand(
        Outputter* outputStream,
        std::vector<Argument*> argument,
        std::vector<Argument*> opts,
        std::ostream& errorOutputStream = std::cout
        );
    [[nodiscard]] unsigned int maxArgumentsCount() const override;
    [[nodiscard]] unsigned int minArgumentsCount() const override;
    [[nodiscard]] bool expectsOutput() const override;
protected:
    void handle(
        Interpreter* interpreter
    ) const override;
    [[nodiscard]] bool validate() const override;
};


#endif //PROJEKAT_TIMECOMMAND_H