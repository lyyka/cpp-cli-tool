//
// Created by Luka Robajac on 29. 12. 2025..
//

#ifndef PROJEKAT_TOKEN_H
#define PROJEKAT_TOKEN_H
#include <string>

class Argument;

class Token
{
public:
    Token(const std::string& token, size_t pos);

    [[nodiscard]] std::string getToken();
    [[nodiscard]] size_t getPos() const;
    [[nodiscard]] Argument* toArgument();
    [[nodiscard]] bool isOpt() const;
    [[nodiscard]] bool isFilename() const;
    [[nodiscard]] bool isIntegral() const;
    [[nodiscard]] bool isInputRedirect() const;
    [[nodiscard]] bool isDoubleOutputRedirect() const;
    [[nodiscard]] bool isOutputRedirect() const;
private:
    /**
     * Actual token representation as a string.
     */
    std::string token;

    /**
     * Position of this token in the source parsed string.
     */
    size_t pos;
};


#endif //PROJEKAT_TOKEN_H