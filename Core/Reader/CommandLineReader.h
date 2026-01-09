//
// Created by Luka Robajac on 29. 12. 2025.
//

#ifndef COMMANDLINEREADER_H
#define COMMANDLINEREADER_H

#include "Reader.h"
#include <iostream>
#include <string>

class CommandLineReader : public Reader
{
public:
    std::string readLine() override;
    bool hasMore() override;
    void resetInputStream();
};

#endif //COMMANDLINEREADER_H
