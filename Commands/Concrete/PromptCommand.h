//
// Created by Luka Robajac on 4. 1. 2026..
//

#ifndef PROJEKAT_PROMPTCOMMAND_H
#define PROJEKAT_PROMPTCOMMAND_H
#include <iosfwd>
#include <iostream>
#include <vector>

#include "../Command.h"
#include "../../Core/Token.h"


class PromptCommand: public Command
{
public:
    PromptCommand(
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


#endif //PROJEKAT_PROMPTCOMMAND_H