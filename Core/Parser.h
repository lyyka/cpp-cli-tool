#ifndef PROJEKAT_PARSER_H
#define PROJEKAT_PARSER_H
#include <vector>

#include "../Commands/Command.h"
#include "Token.h"
#include "../Commands/CommandFactory.h"
#include "../Commands/CommandPipeline.h"


class Parser
{
public:
    Parser();
    ~Parser();
    [[nodiscard]] CommandPipeline* parse(const std::string& commandLine);
private:
    [[nodiscard]] bool isValidChar(char ch);

    /**
     * @param parsable String to tokenize
     * @return A list of tokens found in the string.
     */
    [[nodiscard]] std::vector<std::vector<Token*>> tokenize(const std::string& parsable);

    /**
     *
     * @param commandLine Complete command line from the stream.
     * @param maxLength Max number of chars to take for parsing.
     * @return Command line truncated to the max parsable length.
     */
    [[nodiscard]] std::string getParsableChunk(const std::string& commandLine, size_t maxLength = 512);

    CommandFactory* commandFactory;
};


#endif //PROJEKAT_PARSER_H