//
// Created by Luka Robajac on 8. 1. 2026..
//

#ifndef PROJEKAT_RMCOMMAND_H
#define PROJEKAT_RMCOMMAND_H
#include "../Command.h"


class RmCommand: public Command
{
public:
    RmCommand(
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


#endif //PROJEKAT_RMCOMMAND_H