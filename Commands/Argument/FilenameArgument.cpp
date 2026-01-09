//
// Created by Luka Robajac on 5. 1. 2026..
//

#include "FilenameArgument.h"

#include "../../Core/Reader/FileReader.h"

FilenameArgument::FilenameArgument(Token* token)
    : Argument(token)
{
}

std::string FilenameArgument::getValue()
{
    auto* reader = new FileReader(this->token->getToken());
    std::string contents = reader->getFileContents();
    delete reader;
    return contents;
}