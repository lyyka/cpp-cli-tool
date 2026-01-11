//
// Created by Luka Robajac on 7. 1. 2026..
//

#include "FileOutputter.h"

FileOutputter::FileOutputter(const std::string& filename, const std::ios_base::openmode mode)
    : filename(filename), mode(mode)
{
    this->outputStream.open(filename, mode);

    if (!this->outputStream.is_open())
    {
        throw std::runtime_error("Could not open file " + filename);
    }
}

FileOutputter* FileOutputter::output(const std::string& content)
{
    this->outputStream << content;
    this->outputStream.flush();
    return this;
}

FileOutputter::~FileOutputter()
{
    this->outputStream.close();
}

FileOutputter* FileOutputter::clone() const
{
    std::ios_base::openmode cloneMode = this->mode;

    // When cloning a file outputter, since we are cloning for the same file,
    // we don't want to have 2 "truncate" outputters to the same file since they can easily overwrite each other.
    // Instead, ALWAYS clone into append mode.
    if (this->mode & std::ios::trunc)
    {
        cloneMode = std::ios::out | std::ios::app;
    }

    return new FileOutputter(this->filename, cloneMode);
}
