//
// Created by Luka Robajac on 29. 12. 2025.
//

#ifndef READER_H
#define READER_H

#include <string>

class Reader
{
public:
    virtual ~Reader() = default;

    // Read a single line from the stream
    virtual std::string readLine() = 0;

    // Check if there's more data to read
    virtual bool hasMore() = 0;
};

#endif //READER_H
