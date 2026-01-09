//
// Created by Luka Robajac on 7. 1. 2026..
//

#include "ConsoleOutputter.h"

#include <iostream>

ConsoleOutputter* ConsoleOutputter::output(const std::string& content)
{
    std::cout << content << std::endl;
    return this;
}
