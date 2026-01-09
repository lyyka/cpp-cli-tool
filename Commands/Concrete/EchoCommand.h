//
// Created by Luka Robajac on 29. 12. 2025..
//

#ifndef PROJEKAT_ECHOCOMMAND_H
#define PROJEKAT_ECHOCOMMAND_H
#include <iostream>
#include <string>

#include "../Command.h"


class EchoCommand: public Command
{
public:
    EchoCommand(
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


#endif //PROJEKAT_ECHOCOMMAND_H