//
// Created by Luka Robajac on 5. 1. 2026..
//

#include "DateCommand.h"

#include <iostream>
#include <utility>


DateCommand::DateCommand(Outputter* outputStream, std::vector<Argument*> argument, std::vector<Argument*> opts, std::ostream& errorOutputStream)
    :Command(outputStream, std::move(argument), std::move(opts), errorOutputStream)
{
}

unsigned int DateCommand::minArgumentsCount() const
{
    return 0;
}

unsigned int DateCommand::maxArgumentsCount() const
{
    return 0;
}

bool DateCommand::expectsOutput() const
{
    return true;
}

void DateCommand::handle(Interpreter* interpreter) const
{
    const std::time_t now = std::time(nullptr);
    const std::tm* timeInfo = std::localtime(&now);

    char dateBuffer[11];  // YYYY-MM-DD + null terminator
    std::strftime(dateBuffer, sizeof(dateBuffer), "%Y-%m-%d", timeInfo);

    this->outputStream->output(dateBuffer);
}

bool DateCommand::validate() const
{
    if (!this->argument.empty())
    {
        this->errorOutputStream << "Date command does not expect any arguments!" << std::endl;
        return false;
    }

    if (!this->opts.empty())
    {
        this->errorOutputStream << "Date command does not expect any options!" << std::endl;
        return false;
    }

    return true;
}
