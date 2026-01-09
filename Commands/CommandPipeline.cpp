//
// Created by Luka Robajac on 8. 1. 2026..
//

#include "CommandPipeline.h"

#include "Argument/CinArgument.h"
#include "Argument/IntegralArgument.h"
#include "Output/StringOutputter.h"

void CommandPipeline::add(Command* command)
{
    this->commands.push_back(command);
}

void CommandPipeline::execute(Interpreter* i) const
{
    if (this->commands.size() == 1)
    {
        // if not enough arguments were given in single execution mode,
        // fill the missing arguments with std::cin implementation
        size_t given = this->commands[0]->getArguments().size();
        while (given < this->commands[0]->minArgumentsCount())
        {
            this->commands[0]->appendArgument(new CinArgument());
            given++;
        }
        this->commands[0]->execute(i);
    }
    else if (this->commands.size() > 1)
    {
        std::string lastOutput;
        auto* localOutputStream = new StringOutputter(lastOutput);
        for (size_t idx = 0; idx < this->commands.size(); idx++)
        {
            auto* currentCommand = this->commands[idx];

            if (idx > 0)
            {
                currentCommand->prependArgument(new IntegralArgument(new Token("\"" + lastOutput + "\"", 0)));
                lastOutput = "";
            }

            /*
             * All commands in pipeline should have the StringOutputter,
             * except the last one which should have the default one.
             */
            if (idx != this->commands.size() - 1)
            {
                currentCommand->setOutputter(localOutputStream);
            }
            currentCommand->execute(i);
        }
        delete localOutputStream;
    }
}

CommandPipeline::~CommandPipeline()
{
    // for (const auto c : this->commands)
    // {
    //     delete c;
    // }
}
