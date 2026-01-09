//
// Created by Luka Robajac on 29. 12. 2025.
//

#include "FileReader.h"

#include <sstream>

FileReader::FileReader(const std::string& filePath)
{
    fileStream.open(filePath);
}

FileReader::~FileReader()
{
    if (fileStream.is_open())
    {
        fileStream.close();
    }
}

std::string FileReader::getFileContents()
{
    std::stringstream buff;
    while (this->hasMore())
    {
        buff << this->readLine();
    }
    fileStream.seekg(0);
    return buff.str();
}

std::string FileReader::readLine()
{
    std::string line;
    if (fileStream.is_open() && std::getline(fileStream, line))
    {
        return line;
    }
    return "";
}

bool FileReader::hasMore()
{
    return fileStream.is_open() && !fileStream.eof() && fileStream.good();
}
