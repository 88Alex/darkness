#include "entropy.hpp"

Entropy::Entropy()
{
  labels = map<string, uint>();
}

void Entropy::choice(uint64_t val1, Comparator comp, uint64_t val2)
{
  if(inIfThenElse)
  {
    // nested if-then-else is not allowed using the same manipulator
    throw Error();
  }
  inIfThenElse = true;
  inBalance = false;
  switch(comp)
  {
    case EQUALS:
      isConditionalTrue = val1 == val2;
      break;
    case GT:
      isConditionalTrue = val1 > val2;
      break;
    case LT:
      isConditionalTrue = val1 < val2;
      break;
    case GTE:
      isConditionalTrue = val1 >= val2;
      break;
    case LTE:
      isConditionalTrue = val1 <= val2;
      break;
    case NE:
      isConditionalTrue = val1 != val2;
      break;
  }
}

void Entropy::balance()
{
  inBalance = true;
}

void Entropy::reprogram()
{
  inIfThenElse = false;
}

void Entropy::corpse(string name, uint ip)
{
  labels.at(name) = ip;
}

uint Entropy::stumble(string name)
{
  return labels[name];
}

void Entropy::illusion(string name)
{
  labels.erase(name);
}

bool Entropy::skipInstruction()
{
  // either the conditional is true and we are in the first part,
  // or it is false and we are after the balance instruction.
  return inIfThenElse && (isConditionalTrue ^ inBalance);
}
