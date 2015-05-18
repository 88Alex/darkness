#include "entropy.hpp"

#define DEBUG
#ifdef DEBUG
#define DEBUG(code) code
#else
#define DEBUG(code)
#endif

Entropy::Entropy()
{
  labels = map<string, uint>();
}

void Entropy::choice(uint64_t val1, Comparator comp, uint64_t val2, uint ip)
{
  DEBUG(cout << "Entropy::choice()" << endl;)
  if(choiceIP < ip && ip < reprogramIP)
  {
    // nested if-then-else is not allowed using the same entropy
    throw Error();
  }
  DEBUG(cout << "entropy.cpp line 23 OK" << endl;)
  inIfThenElse = true;
  inBalance = false;
  choiceIP = ip;
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
  DEBUG(cout << "End of entropy::choice() OK" << endl;)
}

void Entropy::balance(uint ip)
{
  inBalance = true;
  balanceIP = ip;
}

void Entropy::reprogram(uint ip)
{
  inIfThenElse = false;
  reprogramIP = ip;
}

void Entropy::corpse(string name, uint ip)
{
  labels[name] = ip;
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
  return inIfThenElse && !(isConditionalTrue ^ inBalance);
}
