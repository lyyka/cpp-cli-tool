//
// Created by Luka Robajac on 8. 1. 2026..
//

#include "TruncateCommand.h"

TruncateCommand::TruncateCommand(Outputter* outputStream, std::vector<Argument*> argument, std::vector<Argument*> opts, std::ostream& errorOutputStream)
    :Command(outputStream, std::move(argument), std::move(opts), errorOutputStream)
{
}

unsigned int TruncateCommand::minArgumentsCount() const
{
    return 1;
}

unsigned int TruncateCommand::maxArgumentsCount() const
{
    return 1;
}

bool TruncateCommand::expectsOutput() const
{
    return false;
}

void TruncateCommand::handle(Interpreter* interpreter) const
{
    const std::string filename = this->argument.at(0)->getValue();
    std::ofstream file(filename, std::ofstream::trunc);
    if (!file.is_open())
    {
        this->errorOutputStream << "TruncateCommand: Could not open file " << filename << std::endl;
        return;
    }
    file.close();
}

bool TruncateCommand::validate() const
{
    if (this->argument.empty())
    {
        this->errorOutputStream << "TruncateCommand: Argument is required!" << std::endl;
        return false;
    }

    if (this->argument.size() > 1)
    {
        this->errorOutputStream << "TruncateCommand: Only 1 argument is supported!" << std::endl;
        return false;
    }

    return true;
}