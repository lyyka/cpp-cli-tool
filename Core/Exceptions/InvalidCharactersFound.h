//
// Created by Luka Robajac on 4. 1. 2026..
//

#ifndef PROJEKAT_INVALIDCHARACTERSFOUND_H
#define PROJEKAT_INVALIDCHARACTERSFOUND_H
#include <stdexcept>
#include <vector>

class InvalidCharactersFound: public std::runtime_error
{
public:
    explicit InvalidCharactersFound(const std::string& msg, const std::vector<size_t>& positions):
    std::runtime_error(msg), positions(positions) {}
    [[nodiscard]] std::vector<size_t> getPositions() const;
private:
    std::vector<size_t> positions;
};

inline std::vector<size_t> InvalidCharactersFound::getPositions() const
{
    return this->positions;
}

#endif //PROJEKAT_INVALIDCHARACTERSFOUND_H