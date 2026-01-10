//
// Created by Luka Robajac on 5. 1. 2026..
//

#include "TouchCommand.h"

#include <filesystem>
#include <fstream>


TouchCommand::TouchCommand(Outputter* outputStream, std::vector<Argument*> argument, std::vector<Argument*> opts, std::ostream& errorOutputStream)
    :Command(outputStream, std::move(argument), std::move(opts), errorOutputStream)
{
}

unsigned int TouchCommand::minArgumentsCount() const
{
    return 1;
}

unsigned int TouchCommand::maxArgumentsCount() const
{
    return 1;
}

bool TouchCommand::expectsOutput() const
{
    return false;
}

void TouchCommand::handle(Interpreter* interpreter) const
{
    const std::string filename = this->argument.at(0)->getToken()->getToken();
    if (std::filesystem::exists(filename)) {
        throw std::runtime_error("File '" + filename + "' already exists");
    }

    std::ofstream file(filename);
    file.close();
}

bool TouchCommand::validate() const
{
    if (this->argument.empty())
    {
        this->errorOutputStream << "TouchCommand: Argument is required!" << std::endl;
        return false;
    }

    if (this->argument.size() > 1)
    {
        this->errorOutputStream << "TouchCommand: Only 1 argument is supported!" << std::endl;
        return false;
    }

    return true;
}
