//
// Created by Luka Robajac on 29. 12. 2025..
//

#include "CommandFactory.h"

#include <fstream>
#include <complex>

#include "../Core/Reader/CommandLineReader.h"
#include "Argument/Argument.h"
#include "Concrete/BatchCommand.h"
#include "Concrete/DateCommand.h"
#include "Concrete/EchoCommand.h"
#include "Concrete/HeadCommand.h"
#include "Concrete/PromptCommand.h"
#include "Concrete/RmCommand.h"
#include "Concrete/TimeCommand.h"
#include "Concrete/TouchCommand.h"
#include "Concrete/TrCommand.h"
#include "Concrete/TruncateCommand.h"
#include "Concrete/WcCommand.h"
#include "Exceptions/UnknownCommand.h"
#include "Output/ConsoleOutputter.h"
#include "Output/FileOutputter.h"

bool CommandFactory::commandNameIsSupported(const std::string& commandName)
{
    return commandName == "echo" ||
        commandName == "prompt" ||
        commandName == "time" ||
        commandName == "date" ||
        commandName == "touch" ||
        commandName == "truncate" ||
        commandName == "rm" ||
        commandName == "wc" ||
        commandName == "tr" ||
        commandName == "head" ||
        commandName == "batch";
}

Command* CommandFactory::make(const std::string& commandName, const std::vector<Argument*>& arguments,
    const std::vector<Argument*>& opts, Token* outputRedirect, Outputter* defaultOutputter)
{
    // Early exception to avoid hanging on input for arguments
    // when an unknown command is passed in.
    if (!commandNameIsSupported(commandName))
    {
        throw UnknownCommand(commandName);
    }

    return this->resolveFromName(
        commandName, arguments, opts, this->resolveOutputter(outputRedirect, defaultOutputter)
    );
}

Outputter* CommandFactory::resolveOutputter(Token* outputRedirect, const Outputter* defaultOutputter)
{
    std::unique_ptr<Outputter> outputter;

    if (outputRedirect != nullptr)
    {
        if (outputRedirect->isDoubleOutputRedirect())
        {
            // >> means append mode
            outputter = std::make_unique<FileOutputter>(outputRedirect->getToken().substr(2), std::ios::out | std::ios::app);
        }
        else
        {
            // > means overwrite mode (truncate)
            outputter = std::make_unique<FileOutputter>(outputRedirect->getToken().substr(1), std::ios::out | std::ios::trunc);
        }
    }
    else if (defaultOutputter != nullptr)
    {
        // Clone the default outputter to create a separate instance for this command
        outputter.reset(defaultOutputter->clone());
    }
    else
    {
        outputter = std::make_unique<ConsoleOutputter>();
    }

    // Transfer ownership to caller (Command destructor will delete it)
    return outputter.release();
}

Command* CommandFactory::resolveFromName(const std::string& commandName, const std::vector<Argument*>& arguments,
                                         const std::vector<Argument*>& opts, Outputter* outputter)
{
    if (commandName == "echo")
    {
        return new EchoCommand(outputter, arguments, opts);
    }

    if (commandName == "prompt")
    {
        return new PromptCommand(outputter, arguments, opts);
    }

    if (commandName == "time")
    {
        return new TimeCommand(outputter, arguments, opts);
    }

    if (commandName == "date")
    {
        return new DateCommand(outputter, arguments, opts);
    }

    if (commandName == "touch")
    {
        return new TouchCommand(outputter, arguments, opts);
    }

    if (commandName == "truncate")
    {
        return new TruncateCommand(outputter, arguments, opts);
    }

    if (commandName == "rm")
    {
        return new RmCommand(outputter, arguments, opts);
    }

    if (commandName == "wc")
    {
        return new WcCommand(outputter, arguments, opts);
    }

    if (commandName == "tr")
    {
        return new TrCommand(outputter, arguments, opts);
    }

    if (commandName == "head")
    {
        return new HeadCommand(outputter, arguments, opts);
    }

    if (commandName == "batch")
    {
        return new BatchCommand(outputter, arguments, opts);
    }

    throw UnknownCommand(commandName);
}
