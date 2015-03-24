#ifndef STALKER_HPP_INCLUDED
#define STALKER_HPP_INCLUDED

#include <sstream>
#include <streambuf>
#include <sstream>
#include <iostream>
#include <cstdio>
#include "manipulator.hpp"
#include "../error.hpp"

class Stalker
{
  public:
    Stalker();
    void stalk();
    char controlChar();
    uint64_t controlNumber();
    void actionChar(string varname);
    void actionNumber(string varname);
    void echo(string str);
    void distant();
    void personal();
    void paracusia();
  private:
    void checkInitialized();
    bool initialized;
    stringstream output;
    bool isDistant;
};

#endif // #ifndef STALKER_HPP_INCLUDED
