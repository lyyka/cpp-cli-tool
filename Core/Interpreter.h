#ifndef PROJEKAT_INTERPRETER_H
#define PROJEKAT_INTERPRETER_H
#include "Parser.h"
#include "Reader/Reader.h"

class Interpreter
{
public:
    explicit Interpreter(char commandPromptChar, Reader* reader, Parser* parser);
    ~Interpreter();
    void run();
    void setCommandPromptChar(char ch);
private:
    char commandPromptChar;
    Reader* reader;
    Parser* parser;
};


#endif //PROJEKAT_INTERPRETER_H