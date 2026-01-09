#include <iostream>

#include "Core/Interpreter.h"
#include "Core/Reader/CommandLineReader.h"
#include "Core/Parser.h"

int main()
{
    auto* engine = new Interpreter(
        '$',
        new CommandLineReader(),
        new Parser()
    );
    engine->run();
    delete engine;
    return 0;
}
