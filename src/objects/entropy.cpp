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
  inIfThenElse = false;
  choiceIP = -1;
  balanceIP = -1;
  reprogramIP = -1;
}

void Entropy::choice(uint64_t val1, Comparator comp, uint64_t val2, uint ip)
{
  if(choiceIP < ip && ip < reprogramIP)
  {
    // nested if-then-else is not allowed using the same entropy
    throw Error();
  }
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
}

void Entropy::balance(uint ip)
{
  inBalance = true;
  balanceIP = ip;
}

void Entropy::reprogram(uint ip)
{
  inIfThenElse = false;
  inBalance = false;
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

bool Entropy::skipInstruction(uint ip)
{
  // either the conditional is true and we are in the first part,
  // or it is false and we are after the balance instruction.
  if(ip < choiceIP || reprogramIP <= ip) return false;
  if((ip < balanceIP && isConditionalTrue) || (balanceIP < ip && !isConditionalTrue))
  {
    DEBUG(cout << "Skipping line " << ip << ": choiceIP = " << choiceIP << "; balanceIP = "
          << balanceIP << "; reprogramIP =" << reprogramIP << endl;)
    return true;
  }
  return false;
}
