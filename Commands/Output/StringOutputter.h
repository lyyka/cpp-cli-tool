//
// Created by Luka Robajac on 8. 1. 2026..
//

#ifndef PROJEKAT_STRINGOUTPUTTER_H
#define PROJEKAT_STRINGOUTPUTTER_H
#include "Outputter.h"


class StringOutputter: public Outputter
{
public:
    explicit StringOutputter(std::string& output);
    StringOutputter* output(const std::string& content) override;
private:
    std::string& outputStream;
};


#endif //PROJEKAT_STRINGOUTPUTTER_H