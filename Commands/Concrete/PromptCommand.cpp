//
// Created by Luka Robajac on 4. 1. 2026..
//

#include "PromptCommand.h"

#include "../../Core/Interpreter.h"

PromptCommand::PromptCommand(Outputter* outputStream, std::vector<Argument*> argument, std::vector<Argument*> opts, std::ostream& errorOutputStream)
    :Command(outputStream, std::move(argument), std::move(opts), errorOutputStream)
{
}

unsigned int PromptCommand::minArgumentsCount() const
{
    return 1;
}

unsigned int PromptCommand::maxArgumentsCount() const
{
    return 1;
}

bool PromptCommand::expectsOutput() const
{
    return false;
}

void PromptCommand::handle(Interpreter* interpreter) const
{
    interpreter->setCommandPromptChar(this->argument.at(0)->getValue().at(0));
}

bool PromptCommand::validate() const
{
    if (this->argument.empty())
    {
        this->errorOutputStream << "PromptCommand: Argument is required!" << std::endl;
        return false;
    }

    if (this->argument.size() > 1)
    {
        this->errorOutputStream << "PromptCommand: Only 1 argument is supported!" << std::endl;
        return false;
    }

    if (this->argument.at(0)->getValue().size() > 1)
    {
        this->errorOutputStream << "PromptCommand: Argument must be one char only!" << std::endl;
        return false;
    }

    return true;
}
