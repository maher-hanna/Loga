#pragma once
#include <exception>

class ParseError : public std::exception
{
    virtual const char* what() const throw()
    {
        return "Parse error happened";
    }
} ;