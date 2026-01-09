//
// Created by Luka Robajac on 8. 1. 2026..
//

#ifndef PROJEKAT_COMMANDPIPELINE_H
#define PROJEKAT_COMMANDPIPELINE_H
#include "Command.h"


class CommandPipeline
{
public:
    ~CommandPipeline();
    void execute(Interpreter* i) const;
    void add(Command* command);
private:
    std::vector<Command*> commands;
};


#endif //PROJEKAT_COMMANDPIPELINE_H