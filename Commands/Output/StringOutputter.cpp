//
// Created by Luka Robajac on 8. 1. 2026..
//

#include "StringOutputter.h"

#include <iostream>

StringOutputter::StringOutputter(std::string& output)
    : outputStream(output)
{
}

StringOutputter* StringOutputter::output(const std::string& content)
{
    this->outputStream += content;
    return this;
}
