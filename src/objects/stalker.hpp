#ifndef STALKER_HPP_INCLUDED
#define STALKER_HPP_INCLUDED

#include <sstream>
#include <streambuf>
#include <sstream>
#include <iostream>
#include <cstdio>
#include "manipulator.hpp"
#include "../error.hpp"
#include "object.hpp"
#include "../voicelist.hpp"

class Stalker : public Object
{
  public:
    Stalker();
    void stalk();
    char controlChar(string varname);
    uint64_t controlNumber(string varname);
    void actionChar(string varname);
    void actionNumber(string varname);
    void echo();
    void distant();
    void personal();
    void paracusia();
    ObjectType getType() { return OT_STALKER; }
  private:
    void checkInitialized();
    bool initialized;
    stringstream output;
    bool isDistant;
};

#endif // #ifndef STALKER_HPP_INCLUDED
