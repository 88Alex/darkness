#include "entropy.hpp"

//#define DEBUG
#ifdef DEBUG
#define DEBUG(code) code
#else
#define DEBUG(code)
#endif

Entropy::Entropy()
{
  labels = map<string, uint>();
  choiceDefined = false;
  choiceIP = 0;
  balanceDefined = false;
  balanceIP = 0;
  reprogramDefined = false;
  reprogramIP = 0;
}

void Entropy::choice(uint64_t val1, Comparator comp, uint64_t val2, uint ip)
{
  if(choiceIP < ip && ip < reprogramIP)
  {
    // nested if-then-else is not allowed using the same entropy
    throw Error();
  }
  choiceDefined = true;
  balanceDefined = false;
  reprogramDefined = false;
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
  balanceDefined = true;
  balanceIP = ip;
}

void Entropy::reprogram(uint ip)
{
  reprogramDefined = true;
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
  if(!choiceDefined) return false;
  if(balanceDefined)
  {
    if(choiceIP < ip && ip < balanceIP)
    {
      DEBUG(cout << "Skipping because conditional is false: ip = " << ip << "; choiceIP = " << choiceIP << "; balanceIP = " << balanceIP << endl;)
      return !isConditionalTrue;
    }
    else if(reprogramDefined)
    {
      if(balanceIP < ip && ip < reprogramIP)
      {
        DEBUG(cout << "Skipping because conditional is true: ip = " << ip << "; choiceIP = " << choiceIP << "; balanceIP = " << balanceIP
              << "; reprogramIP = " << reprogramIP << endl;)
        return isConditionalTrue;
      }
    }
    else
    {
      if(balanceIP < ip)
      {
        DEBUG(cout << "Skipping because conditional is true: ip = " << ip << "; choiceIP = " << choiceIP << "; balanceIP = " << balanceIP << endl;)
        return isConditionalTrue;
      }
    }
  }
  else
  {
    if(reprogramDefined)
    {
      if(choiceIP < ip && ip < reprogramIP)
      {
        DEBUG(cout << "Skipping because conditional is false: ip = " << ip << "; choiceIP = " << choiceIP << "; reprogramIP = " << reprogramIP << endl;)
        return !isConditionalTrue;
      }
    }
    else
    {
      if(choiceIP < ip)
      {
        DEBUG(cout << "Skipping because conditional is false: ip = " << ip << "; choiceIP = " << choiceIP << endl;)
        return !isConditionalTrue;
      }
    }
  }
  return false;
}

void Entropy::setIP(uint ip)
{
  currentIP = ip;
}
