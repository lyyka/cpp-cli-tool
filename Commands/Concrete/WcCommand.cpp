//
// Created by Luka Robajac on 8. 1. 2026..
//

#include "WcCommand.h"

WcCommand::WcCommand(Outputter* outputStream, std::vector<Argument*> argument, std::vector<Argument*> opts, std::ostream& errorOutputStream)
    :Command(outputStream, std::move(argument), std::move(opts), errorOutputStream)
{
}

unsigned int WcCommand::minArgumentsCount() const
{
    return 1;
}

unsigned int WcCommand::maxArgumentsCount() const
{
    return 1;
}

bool WcCommand::expectsOutput() const
{
    return true;
}

void WcCommand::handle(Interpreter* interpreter) const
{
    const std::string text = this->argument.at(0)->getValue();

    if (this->opts.at(0)->getValue() == "c")
    {
        this->outputStream->output(std::to_string(text.size()));
    }
    else if (this->opts.at(0)->getValue() == "w")
    {
        unsigned int counter = 0;
        // Allows us to skip multiple concatenated ' ' chars (spaces).
        bool activeSeek = true;
        for (const unsigned char c : text)
        {
            if (std::isspace(c))
            {
                // When a space is encountered...
                if (activeSeek)
                {
                    // ... prevent further isspace chars to be counted ...
                    activeSeek = false;
                    counter++;
                }
            }
            else
            {
                // ... until we hit a non-isspace char.
                activeSeek = true;
            }
        }
        this->outputStream->output(std::to_string(counter + (activeSeek ? 1 : 0)));
    }
}

bool WcCommand::validate() const
{
    if (this->argument.size() > 1)
    {
        this->errorOutputStream << "WcCommand: Only 1 argument is supported!" << std::endl;
        return false;
    }

    if (this->opts.size() > 1)
    {
        this->errorOutputStream << "WcCommand: Only 1 option is supported!" << std::endl;
        return false;
    }

    if (this->opts.at(0)->getValue() != "c" && this->opts.at(0)->getValue() != "w")
    {
        this->errorOutputStream << "WcCommand: only -w and -c options are supported!" << std::endl;
        return false;
    }

    return true;
}