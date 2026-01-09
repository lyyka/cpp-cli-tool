#ifndef PROJEKAT_COMMAND_H
#define PROJEKAT_COMMAND_H

#include <iostream>
#include <fstream>
#include <memory>
#include <utility>

#include "Argument/Argument.h"
#include "Output/Outputter.h"

class Interpreter;

class Command
{
public:
    explicit Command(
        Outputter* outputStream,
        std::vector<Argument*> argument,
        std::vector<Argument*> opts,
        std::ostream& errorOutputStream = std::cout
    ) : outputStream(outputStream), errorOutputStream(errorOutputStream), argument(std::move(argument)),
        opts(std::move(opts))
    {
    }
    virtual ~Command();

    void execute(Interpreter* interpreter) const;
    void prependArgument(Argument* arg);
    void appendArgument(Argument* arg);
    void setOutputter(Outputter* newOutputter);
    std::vector<Argument*> getArguments();
    /**
     * @return How many arguments command can take max.
     */
    [[nodiscard]] virtual unsigned int maxArgumentsCount() const = 0;
    /**
     * @return How many arguments command realistically needs to execute.
     *  It may happen that command has 1 optional argument, but min arguments is still 1
     *  since that 1 argument, if not passed explicitly, should be picked up from CLI.
     */
    [[nodiscard]] virtual unsigned int minArgumentsCount() const = 0;
    [[nodiscard]] virtual bool expectsOutput() const = 0;
protected:
    virtual void handle(
        Interpreter* interpreter
    ) const = 0;
    [[nodiscard]] virtual bool validate() const = 0;
    Outputter* outputStream;
    std::ostream& errorOutputStream;
    std::vector<Argument*> argument;
    std::vector<Argument*> opts;

    // Owns the output file stream if output redirection is used
    std::unique_ptr<std::ofstream> outputFile;
};

#endif //PROJEKAT_COMMAND_H
