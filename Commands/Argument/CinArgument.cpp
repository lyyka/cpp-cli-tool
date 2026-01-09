//
// Created by Luka Robajac on 8. 1. 2026..
//

#include "CinArgument.h"

#include <iostream>
#include "../../Core/Reader/CommandLineReader.h"

CinArgument::CinArgument()
= default;

std::string CinArgument::getValue()
{
    auto* reader = new CommandLineReader();
    std::string value;
    while (reader->hasMore())
    {
        value += reader->readLine() + '\n';
    }
    reader->resetInputStream();
    delete reader;
    return value.substr(0, value.size() - 1);
}
