//
// Created by Luka Robajac on 8. 1. 2026..
//

#include "RmCommand.h"

RmCommand::RmCommand(Outputter* outputStream, std::vector<Argument*> argument, std::vector<Argument*> opts, std::ostream& errorOutputStream)
    :Command(outputStream, std::move(argument), std::move(opts), errorOutputStream)
{
}

unsigned int RmCommand::minArgumentsCount() const
{
    return 1;
}

unsigned int RmCommand::maxArgumentsCount() const
{
    return 1;
}

bool RmCommand::expectsOutput() const
{
    return false;
}

void RmCommand::handle(Interpreter* interpreter) const
{
    const std::string filename = this->argument.at(0)->getToken()->getToken();
    if (std::remove(filename.c_str()) != 0)
    {
        this->errorOutputStream << "RmCommand: Could not remove file " << filename << std::endl;
    }
}

bool RmCommand::validate() const
{
    if (this->argument.empty())
    {
        this->errorOutputStream << "RmCommand: Argument is required!" << std::endl;
        return false;
    }

    if (this->argument.size() > 1)
    {
        this->errorOutputStream << "RmCommand: Only 1 argument is supported!" << std::endl;
        return false;
    }

    return true;
}