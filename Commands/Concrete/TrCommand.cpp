//
// Created by Luka Robajac on 9. 1. 2026..
//

#include "TrCommand.h"

#include "../Argument/IntegralArgument.h"

TrCommand::TrCommand(Outputter* outputStream, std::vector<Argument*> argument, std::vector<Argument*> opts, std::ostream& errorOutputStream)
    :Command(outputStream, std::move(argument), std::move(opts), errorOutputStream)
{
}

unsigned int TrCommand::minArgumentsCount() const
{
    return 1;
}

unsigned int TrCommand::maxArgumentsCount() const
{
    return 2;
}

bool TrCommand::expectsOutput() const
{
    return true;
}

void TrCommand::handle(Interpreter* interpreter) const
{
    std::string text = this->argument.at(0)->getValue();

    auto* replacementArg = new IntegralArgument(new Token(this->opts.at(0)->getValue(), 0));
    const std::string replacementValue = replacementArg->getValue();

    std::string replaceWith;
    if (this->argument.size() == 2)
    {
        replaceWith = this->argument.at(1)->getValue();
    }

    size_t pos = 0;
    size_t i = text.find(replacementValue, pos);
    while (i != std::string::npos)
    {
        text.replace(i, replacementValue.size(), replaceWith);
        pos += replaceWith.size();
        i = text.find(replacementValue, pos);
    }

    this->outputStream->output(text);
}

bool TrCommand::validate() const
{
    if (this->argument.size() > 2)
    {
        this->errorOutputStream << "TrCommand: Only 2 arguments are supported!" << std::endl;
        return false;
    }

    if (this->opts.size() > 1)
    {
        this->errorOutputStream << "TrCommand: Only 1 option is supported!" << std::endl;
        return false;
    }

    if (this->opts.at(0)->getValue().size() < 3)
    {
        this->errorOutputStream << "TrCommand: Non-empty argument is expected!" << std::endl;
        return false;
    }

    const std::string argValue = this->opts.at(0)->getValue();
    if (argValue.at(0) != '"' || argValue.at(argValue.size() - 1) != '"')
    {
        this->errorOutputStream << "TrCommand: Option must be wrapped in double-quotes!" << std::endl;
        return false;
    }

    return true;
}