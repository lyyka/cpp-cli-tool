#include "Parser.h"

#include <complex>
#include <iostream>

#include "../Commands/CommandPipeline.h"
#include "../Commands/Argument/Argument.h"
#include "../Commands/Argument/FilenameArgument.h"
#include "Exceptions/InvalidCharactersFound.h"

Parser::Parser(Outputter* overrideOutputter)
    : overrideOutputter(overrideOutputter)
{
    this->commandFactory = new CommandFactory();
}

Parser::~Parser()
{
    delete this->commandFactory;
}

CommandPipeline* Parser::parse(const std::string& commandLine)
{
    auto* commands = new CommandPipeline();

    const std::string parsableChunk = this->getParsableChunk(commandLine);

    try
    {
        const std::vector<std::vector<Token*>> tokenSets = this->tokenize(parsableChunk);

        for (size_t j = 0; j < tokenSets.size(); j++)
        {
            const auto tokens = tokenSets[j];

            /*
             * Check if the tokens list is empty and throw an exception!
             */
            if (tokens.empty())
            {
                throw std::runtime_error("Empty command given!");
            }

            /*
             * - Extract a list of options & arguments.
             * - Extract one input redirect (optional).
             * - Extract one output redirect (optional).
             */
            std::vector<Argument*> opts;
            std::vector<Argument*> arguments;
            Token* inputRedirect = nullptr;
            Token* outputRedirect = nullptr;

            for (size_t i = 1; i < tokens.size(); i++)
            {
                if (tokens[i]->isOpt())
                {
                    /*
                     * When dealing with an OPT, we must not have already seen input/output redirection.
                     */
                    if (inputRedirect != nullptr || outputRedirect != nullptr)
                    {
                        throw std::runtime_error("Input & output redirects must come at the end!");
                    }

                    opts.push_back(tokens[i]->toArgument());
                }
                else if (tokens[i]->getToken() == ">" || tokens[i]->getToken() == ">>")
                {
                    /*
                     * It is important that this "else if" is handled here to prevent
                     * going into "output redirection" when ">>" is seen.
                     * (since that can be parsed as output redirection to ">")
                     *
                     * If there is next token, and it is just a filename, make the next token
                     * be the output redirection and skip current and next by doing i++.
                     *
                     * In other case throw an invalid char exception since ">" or ">>" cannot be seen
                     * without following filename.
                     */
                    if (i + 1 < tokens.size() && tokens[i + 1]->isFilename())
                    {
                        /*
                         * Make a new token by merging current and next to retain information about ">" or ">>"
                         */
                        outputRedirect = new Token(tokens[i]->getToken() + tokens[i + 1]->getToken(), tokens[i]->getPos());
                        i++;
                        // delete tokens[i];
                        // delete tokens[i + 1];
                        continue;
                    }

                    throw InvalidCharactersFound("Invalid chars!", {tokens[i]->getPos() + 1});
                }
                else if (tokens[i]->getToken() == "<")
                {
                    /*
                     * If there is next token, and it is just a filename, make the next token
                     * be the output redirection and skip current and next by doing i++.
                     *
                     * In other case throw an invalid char exception since "<" cannot be seen
                     * without following filename.
                     */
                    if (i + 1 < tokens.size() && tokens[i + 1]->isFilename())
                    {
                        /*
                         * When dealing with an any redirection, it is not allowed if an argument was already parsed.
                         */
                        if (!arguments.empty())
                        {
                            throw std::runtime_error("Input redirect is not allowed if argument is given!");
                        }

                        /*
                         * Make a new token by merging current and next to retain information about "<"
                         */
                        inputRedirect = new Token(tokens[i]->getToken() + tokens[i + 1]->getToken(), tokens[i]->getPos());
                        i++;
                        // delete tokens[i];
                        // delete tokens[i + 1];
                        continue;
                    }

                    throw InvalidCharactersFound("Invalid chars!", {tokens[i]->getPos() + 1});
                }
                else if (tokens[i]->isInputRedirect())
                {
                    /*
                     * When dealing with an input redirection, we must not have already seen it.
                     */
                    if (inputRedirect)
                    {
                        throw std::runtime_error("Only 1 input redirect is allowed!");
                    }

                    /*
                     * When dealing with an any redirection, it is not allowed if an argument was already parsed.
                     */
                    if (!arguments.empty())
                    {
                        throw std::runtime_error("Input redirect is not allowed if argument is given!");
                    }

                    inputRedirect = tokens[i];
                }
                else if (tokens[i]->isOutputRedirect())
                {
                    /*
                     * When dealing with an output redirection, we must not have already seen it.
                     */
                    if (outputRedirect)
                    {
                        throw std::runtime_error("Only 1 output redirect is allowed!");
                    }

                    outputRedirect = tokens[i];
                }
                else
                {
                    /*
                     * If no above cases were satisfied, then it's an argument.
                     * When argument is reached, if we already parsed input or output redirection,
                     * throw an exception since that is not permitted.
                     */
                    if (inputRedirect != nullptr || outputRedirect != nullptr)
                    {
                        throw std::runtime_error("Input & output redirects must come at the end!");
                    }

                    arguments.push_back(tokens[i]->toArgument());
                }
            }

            /*
             * If the input REDIRECT exists,
             * treat it the same way as if a filename argument was seen.
             */
            if (inputRedirect != nullptr)
            {
                arguments.clear(); // just in case :D
                arguments.push_back(
                    new FilenameArgument(new Token(inputRedirect->getToken().substr(1), inputRedirect->getPos()))
                );
                // delete inputRedirect;
            }

            std::string commandName = tokens[0]->getToken();
            auto* command = this->commandFactory->make(
                commandName,
                arguments,
                opts,
                outputRedirect,
                this->overrideOutputter
            );

            /*
             * If command received equal or more than what it can take, and
             * it is not the first in the list (so it'll receive even more!),
             * then throw an exception.
             */
            if (j > 0 && arguments.size() + 1 > command->maxArgumentsCount())
            {
                throw std::runtime_error("Command argument overflow for " + commandName);
            }
            if (j > 0 && arguments.size() + 1 < command->minArgumentsCount())
            {
                throw std::runtime_error("Command arguments missing for " + commandName);
            }

            /*
             * Each command (except the last one) must provide an output
             * in order to be used in the pipeline.
             */
            if (j < tokenSets.size() - 1 && !command->expectsOutput())
            {
                throw std::runtime_error("Command must have an output to be used in the pipeline! Command: " + commandName);
            }

            commands->add(command);

            // delete tokens[0];
        }
    }
    catch (InvalidCharactersFound& e)
    {
        std::cout << "Error - unexpected characters" << std::endl;
        std::cout << commandLine << std::endl;
        size_t errorI = 0;
        for (size_t i = 0; i < commandLine.size(); i++)
        {
            if (errorI < e.getPositions().size() && i == e.getPositions().at(errorI))
            {
                std::cout << "^";
                errorI++;
            } else
            {
                std::cout << " ";
            }
        }
        std::cout << std::endl;
    }

    return commands;
}

std::vector<std::vector<Token*>> Parser::tokenize(const std::string& parsable)
{
    std::vector<std::vector<Token*>> tokenSets = {};
    std::vector<Token*> tokens = {};

    // Tokenize the input stream first:
    // Buffer holds the current token being read.
    std::string buffer;
    size_t i = 0;
    size_t pos = 0;
    std::vector<size_t> invalidCharsIndexes = {};
    bool isInsideIntegral = false;
    for (const char ch : parsable)
    {
        // Support pipelines
        if (ch == '|' && !isInsideIntegral)
        {
            if (!buffer.empty())
            {
                tokens.push_back(new Token(buffer, pos));
                buffer = "";
            }
            tokenSets.push_back(tokens);
            tokens.clear();

            pos = i;
            i++;
            continue;
        }

        // When we hit a blank char (" " or "\t")
        // we push whatever is in the buffer to the tokens list
        // and then clear the buffer to make it ready for next token.
        if (std::isblank(ch) && !isInsideIntegral)
        {
            if (!buffer.empty())
            {
                tokens.push_back(new Token(buffer, pos));
                buffer = "";
            }

            pos = i;
            i++;

            // Since we don't want to tokenize blank chars
            // this line skips them.
            continue;
        }

        if (ch == '"' && !isInsideIntegral)
        {
            isInsideIntegral = true;
        } else if (ch == '"')
        {
            isInsideIntegral = false;
        } else
        {
            if (!isInsideIntegral && !this->isValidChar(ch))
            {
                invalidCharsIndexes.push_back(i);
            }
        }

        buffer += ch;
        i++;
    }

    // Push whatever overflowed in the buffer to the tokens list.
    if (!buffer.empty())
    {
        tokens.push_back(new Token(buffer, pos));
    }

    if (!tokens.empty())
    {
        tokenSets.push_back(tokens);
    }

    if (!invalidCharsIndexes.empty())
    {
        throw InvalidCharactersFound(
            "Invalid chars found!",
            invalidCharsIndexes
        );
    }

    return tokenSets;
}

bool Parser::isValidChar(const char ch)
{
    return (ch >= 'A' && ch <= 'Z') ||
        (ch >= 'a' && ch <= 'z') ||
        (ch >= '0' && ch <= '9') ||
        // for filenames
        ch == '.' ||
        ch == '_' ||
        // for redirection
        ch == '<' ||
        ch == '>' ||
        // for pipelines
        ch == '|' ||
        // for opts
        ch == '-';
}

std::string Parser::getParsableChunk(const std::string& commandLine, size_t maxLength)
{
    // Validate command size
    /*
        *Командна линија се састоји од низа знакова максималне дужине 512 знакова типа char
        који се завршава знаком за нови ред ('\n'); уколико се на улазу не наиђе на знак за нови
        ред до наведене дужине 512 знакова (која не укључује и знак за нови ред), сви
        преостали знакови се игноришу, а као запис командне линије узима се унетих 512
        знакова (не укључујући знак за нови ред).
     */
    size_t size = commandLine.length();

    if (size > maxLength)
    {
        return commandLine.substr(0, maxLength);
    }

    /*
     * Check if the newline char exists somewhere in the middle.
     * Example of a 250 chars text where \n char is a 128th char.
     */
    size_t newLinePos = commandLine.find('\n');
    if (newLinePos != std::string::npos)
    {
        return commandLine.substr(0, newLinePos);
    }

    size_t returnPos = commandLine.find('\r');
    if (returnPos != std::string::npos)
    {
        return commandLine.substr(0, returnPos);
    }

    return commandLine;
}
