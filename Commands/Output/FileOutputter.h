//
// Created by Luka Robajac on 7. 1. 2026..
//

#ifndef PROJEKAT_FILEOUTPUTTER_H
#define PROJEKAT_FILEOUTPUTTER_H
#include <fstream>
#include <string>

#include "Outputter.h"


class FileOutputter: public Outputter
{
public:
    explicit FileOutputter(const std::string& filename, std::ios_base::openmode mode);
    ~FileOutputter() override;
    FileOutputter* output(const std::string& content) override;
private:
    std::ofstream outputStream;
};


#endif //PROJEKAT_FILEOUTPUTTER_H