//
// Created by Luka Robajac on 7. 1. 2026..
//

#ifndef PROJEKAT_OUTPUTTER_H
#define PROJEKAT_OUTPUTTER_H

#include <string>

class Outputter
{
public:
    Outputter();
    virtual ~Outputter();
    virtual Outputter* output(const std::string& content) = 0;
    [[nodiscard]] virtual Outputter* clone() const = 0;
};

#endif //PROJEKAT_OUTPUTTER_H