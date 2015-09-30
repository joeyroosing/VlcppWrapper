#ifndef VLCERROR_H
#define VLCERROR_H

#include <iostream>
#include <string>

class VlcError
{
public:
    static std::string getErrorMessage();
    static void showErrorMessage();
    static void clearError();
};

#endif // VLCERROR_H
