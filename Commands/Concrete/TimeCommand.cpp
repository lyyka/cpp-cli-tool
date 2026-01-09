//
// Created by Luka Robajac on 5. 1. 2026..
//

#include "TimeCommand.h"

#include <iostream>
#include <utility>


TimeCommand::TimeCommand(Outputter* outputStream, std::vector<Argument*> argument, std::vector<Argument*> opts, std::ostream& errorOutputStream)
    :Command(outputStream, std::move(argument), std::move(opts), errorOutputStream)
{
}

unsigned int TimeCommand::minArgumentsCount() const
{
    return 0;
}

unsigned int TimeCommand::maxArgumentsCount() const
{
    return 0;
}

bool TimeCommand::expectsOutput() const
{
    return true;
}

void TimeCommand::handle(Interpreter* interpreter) const
{
    const std::time_t now = std::time(nullptr);
    const std::tm* timeInfo = std::localtime(&now);

    char timeBuffer[9];  // HH:MM:SS + null terminator
    std::strftime(timeBuffer, sizeof(timeBuffer), "%H:%M:%S", timeInfo);

    this->outputStream->output(timeBuffer);
}

bool TimeCommand::validate() const
{
    if (!this->argument.empty())
    {
        this->errorOutputStream << "Time command does not expect any arguments!" << std::endl;
        return false;
    }

    if (!this->opts.empty())
    {
        this->errorOutputStream << "Time command does not expect any options!" << std::endl;
        return false;
    }

    return true;
}
