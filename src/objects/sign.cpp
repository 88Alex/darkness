#include "sign.hpp"

//#define DEBUG
#ifdef DEBUG
#define DEBUG(code) code
#else
#define DEBUG(code)
#endif

Sign::Sign() {}

Sign::Sign(string str)
{
  val = str;
}

void Sign::scrawlCharacter(string varname)
{
  uint64_t var = Manipulator::getConstFromAllManipulators(varname);
  char c = static_cast<char>(var);
  val.append(1, c); // append 1 repetition of c
}

void Sign::scrawlNumber(string varname)
{
  uint64_t var = Manipulator::getConstFromAllManipulators(varname);
  val.append(to_string(var));
}

void Sign::scrawl(string str)
{
  val.append(str);
}

void Sign::tear()
{
  val.erase(val.begin());
}

void Sign::tear(size_t n)
{
  val.erase(0, n);
}

void Sign::tearAll()
{
  val = "";
}

void Sign::observe(string varname)
{
  Manipulator::getFromAllManipulators(varname)->setValue(static_cast<uint64_t>(val[0]));
}

void Sign::steal(string varname)
{
  observe(varname);
  tear();
}

void Sign::read(bool eraseAfterRead)
{
  string result = val;
  if(eraseAfterRead) tearAll();
  Voicelist::get()->enqueue(result);
}
