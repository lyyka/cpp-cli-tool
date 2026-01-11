#include "Interpreter.h"

#include <iostream>

#include "Parser.h"
#include "../Commands/Exceptions/UnknownCommand.h"

Interpreter::Interpreter(const char commandPromptChar, Reader* reader, Parser* parser, const bool disablePrompt)
    : commandPromptChar(commandPromptChar), reader(reader), parser(parser), disablePrompt(disablePrompt)
{
}

Interpreter::~Interpreter()
{
    delete this->reader;
    delete this->parser;
}

void Interpreter::setCommandPromptChar(const char ch)
{
    this->commandPromptChar = ch;
}

void Interpreter::run()
{
    while (true)
    {
        if (!this->disablePrompt)
        {
            std::cout << this->commandPromptChar << " ";
        }

        std::string line = this->reader->readLine();

        if (!this->reader->hasMore() && line.empty())
        {
            break;
        }

        try
        {
            const auto* pipeline = this->parser->parse(line);
            pipeline->execute(this);
            delete pipeline;
        }
        catch (UnknownCommand& e)
        {
            std::cout << "Unknown command: " << e.what() << std::endl;
        }
    }
}
