//
// Created by Luka Robajac on 5. 1. 2026..
//

#ifndef PROJEKAT_DATECOMMAND_H
#define PROJEKAT_DATECOMMAND_H
#include "../Command.h"


class DateCommand: public Command
{
public:
    DateCommand(
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


#endif //PROJEKAT_DATECOMMAND_H