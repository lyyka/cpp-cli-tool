//
// Created by Luka Robajac on 29. 12. 2025..
//

#include "EchoCommand.h"

#include <iostream>
#include <utility>

EchoCommand::EchoCommand(Outputter* outputStream, std::vector<Argument*> argument, std::vector<Argument*> opts, std::ostream& errorOutputStream)
    :Command(outputStream, std::move(argument), std::move(opts), errorOutputStream)
{
}

unsigned int EchoCommand::minArgumentsCount() const
{
    return 1;
}

unsigned int EchoCommand::maxArgumentsCount() const
{
    return 1;
}

bool EchoCommand::expectsOutput() const
{
    return true;
}

void EchoCommand::handle(Interpreter* interpreter) const
{
    this->outputStream
        ->output(this->argument.at(0)->getValue());
}

bool EchoCommand::validate() const
{
    if (this->argument.empty())
    {
        this->errorOutputStream << "EchoCommand: Argument is expected!" << std::endl;
        return false;
    }

    if (this->argument.size() > 1)
    {
        this->errorOutputStream << "EchoCommand: Only 1 argument is supported!" << std::endl;
        return false;
    }

    return true;
}
