//
// Created by Luka Robajac on 29. 12. 2025.
//

#include "CommandLineReader.h"

std::string CommandLineReader::readLine()
{
    std::string line;
    std::getline(std::cin, line);
    return line;
}

bool CommandLineReader::hasMore()
{
    return std::cin.good() && !std::cin.eof();
}

void CommandLineReader::resetInputStream()
{
    std::cin.clear();
    clearerr(stdin);
    // std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
