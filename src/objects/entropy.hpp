#ifndef ENTROPY_HPP_INCLUDED
#define ENTROPY_HPP_INCLUDED

#include <string>
#include <map>
#include <cinttypes>
#include <iostream>
#include "manipulator.hpp"
#include "../error.hpp"
#include "object.hpp"

typedef enum { EQUALS, GT, LT, GTE, LTE, NE } Comparator;

class Entropy : public Object
{
  public:
    Entropy();
    void choice(uint64_t val1, Comparator comp, uint64_t val2, uint ip);
    void balance(uint ip);
    void reprogram(uint ip);
    void corpse(string name, uint ip); // ip is the instruction pointer to which the label points
    uint stumble(string name);
    void illusion(string name);
    bool skipInstruction();
    ObjectType getType() { return OT_ENTROPY; }
  private:
    map<string, uint> labels;
    bool inIfThenElse; // are we in a choice/balance/reprogram block?
    bool isConditionalTrue; // is the choice conditional true?
    bool inBalance; // have we reached the balance instruction yet?
    uint choiceIP;
    uint balanceIP;
    uint reprogramIP;
};

#endif // #ifndef ENTROPY_HPP_INCLUDED
