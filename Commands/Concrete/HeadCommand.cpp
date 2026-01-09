//
// Created by Luka Robajac on 9. 1. 2026..
//

#include "HeadCommand.h"

HeadCommand::HeadCommand(Outputter* outputStream, std::vector<Argument*> argument, std::vector<Argument*> opts, std::ostream& errorOutputStream)
    :Command(outputStream, std::move(argument), std::move(opts), errorOutputStream)
{
}

unsigned int HeadCommand::minArgumentsCount() const
{
    return 1;
}

unsigned int HeadCommand::maxArgumentsCount() const
{
    return 1;
}

bool HeadCommand::expectsOutput() const
{
    return true;
}

void HeadCommand::handle(Interpreter* interpreter) const
{
    const std::string optVal = this->opts.at(0)->getValue().substr(1);
    int lines = std::stoi(optVal);

    std::string buffer;
    const std::string text = this->argument.at(0)->getValue();
    for (const char c : text)
    {
        if (lines == 0)
        {
            break;
        }

        if (c == '\n')
        {
            this->outputStream->output(buffer);
            buffer = "";
            lines--;
            continue;
        }
        buffer += c;
    }
}

bool HeadCommand::validate() const
{
    if (this->argument.size() > 1)
    {
        this->errorOutputStream << "HeadCommand: Only 1 argument is supported!" << std::endl;
        return false;
    }

    if (this->opts.empty())
    {
        this->errorOutputStream << "HeadCommand: -ncount option is required!" << std::endl;
        return false;
    }

    if (this->opts.size() > 1)
    {
        this->errorOutputStream << "HeadCommand: Only 1 option is supported!" << std::endl;
        return false;
    }

    if (this->opts.at(0)->getValue().size() == 1)
    {
        this->errorOutputStream << "HeadCommand: -ncount expects value after -n!" << std::endl;
        return false;
    }

    // Get everything after first char (after 'n')
    const std::string optVal = this->opts.at(0)->getValue().substr(1);
    if (optVal.size() > 5)
    {
        this->errorOutputStream << "HeadCommand: count in -ncount must be at most 5 digits!" << std::endl;
        return false;
    }

    return true;
}