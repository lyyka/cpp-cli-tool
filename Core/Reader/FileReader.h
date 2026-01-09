//
// Created by Luka Robajac on 29. 12. 2025.
//

#ifndef FILEREADER_H
#define FILEREADER_H

#include "Reader.h"
#include <fstream>
#include <string>

class FileReader : public Reader
{
private:
    std::ifstream fileStream;

public:
    explicit FileReader(const std::string& filePath);
    ~FileReader() override;

    std::string readLine() override;
    std::string getFileContents();
    bool hasMore() override;
};

#endif //FILEREADER_H
