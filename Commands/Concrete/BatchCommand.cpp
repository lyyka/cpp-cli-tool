//
// Created by Luka Robajac on 10. 1. 2026..
//

#include "BatchCommand.h"

#include "../../Core/Interpreter.h"
#include "../../Core/Reader/FileReader.h"

BatchCommand::BatchCommand(Outputter* outputStream, std::vector<Argument*> argument, std::vector<Argument*> opts, std::ostream& errorOutputStream)
    :Command(outputStream, std::move(argument), std::move(opts), errorOutputStream)
{
}

unsigned int BatchCommand::minArgumentsCount() const
{
    return 1;
}

unsigned int BatchCommand::maxArgumentsCount() const
{
    return 1;
}

bool BatchCommand::expectsOutput() const
{
    return true;
}

void BatchCommand::handle(Interpreter* interpreter) const
{
    const std::string filename = this->argument.at(0)->getToken()->getToken();

    // Clone the outputter to avoid file pointer conflicts when original is opened in truncate mode
    // The clone uses append mode, ensuring all writes happen sequentially without overwrites.
    Outputter* clonedOutput = this->outputStream->clone();

    // Run the "inner" interpreter to allow seamless recursions which all work in the same exact way.
    auto* i = new Interpreter(' ', new FileReader(filename), new Parser(clonedOutput), true);
    i->run();

    // Delete objects created in this handle.
    delete i;
    delete clonedOutput;
}

bool BatchCommand::validate() const
{
    if (this->argument.empty())
    {
        this->errorOutputStream << "BatchCommand: Argument is required!" << std::endl;
        return false;
    }

    if (this->argument.size() > 1)
    {
        this->errorOutputStream << "BatchCommand: Only 1 argument is supported!" << std::endl;
        return false;
    }

    return true;
}