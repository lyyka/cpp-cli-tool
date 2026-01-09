//
// Created by Luka Robajac on 29. 12. 2025..
//

#ifndef PROJEKAT_COMMANDFACTORY_H
#define PROJEKAT_COMMANDFACTORY_H
#include <vector>

#include "Command.h"
#include "../Core/Token.h"


class CommandFactory
{
public:
    [[nodiscard]] Command* make(const std::string& commandName, const std::vector<Argument*>& arguments, const std::vector<Argument*>& opts, Token* outputRedirect = nullptr);
private:
    [[nodiscard]] bool commandNameIsSupported(const std::string& commandName);
    [[nodiscard]] Outputter* resolveOutputter(Token* outputRedirect = nullptr);
    [[nodiscard]] Command* resolveFromName(const std::string& commandName, const std::vector<Argument*>& arguments, const std::vector<Argument*>& opts, Outputter* outputter);
};


#endif //PROJEKAT_COMMANDFACTORY_H