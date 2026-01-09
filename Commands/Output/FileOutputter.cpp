//
// Created by Luka Robajac on 7. 1. 2026..
//

#include "FileOutputter.h"

FileOutputter::FileOutputter(const std::string& filename, const std::ios_base::openmode mode)
{
    this->outputStream.open(filename, mode);

    if (!this->outputStream.is_open())
    {
        throw std::runtime_error("Could not open file " + filename);
    }
}

FileOutputter* FileOutputter::output(const std::string& content)
{
    this->outputStream << content << std::endl;
    return this;
}

FileOutputter::~FileOutputter()
{
    this->outputStream.close();
}
