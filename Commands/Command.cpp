//
// Created by Luka Robajac on 7. 1. 2026..
//

#include "Command.h"

Command::~Command()
{
    for (const auto arg : argument)
    {
        delete arg;
    }

    for (const auto opt : opts)
    {
        delete opt;
    }

    delete this->outputStream;
}

void Command::setOutputter(Outputter* newOutputter)
{
    delete this->outputStream;
    this->outputStream = newOutputter;
}

void Command::prependArgument(Argument* arg)
{
    this->argument.insert(this->argument.begin(), arg);
}

void Command::appendArgument(Argument* arg)
{
    this->argument.push_back(arg);
}

std::vector<Argument*> Command::getArguments()
{
    return this->argument;
}

void Command::execute(Interpreter* interpreter) const
{
    if (this->validate())
    {
        this->handle(interpreter);
    }
}
