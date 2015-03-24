#include "sign.hpp"

Sign::Sign() {}

Sign::Sign(string str)
{
  val = str;
}

void Sign::scrawlCharacter(string varname)
{
  uint64_t var = Manipulator::getFromAllManipulators(varname);
  char c = static_cast<char>(var);
  val.append(1, c); // append 1 repetition of c
}

void Sign::scrawlNumber(string varname)
{
  uint64_t var = Manipulator::getFromAllManipulators(varname);
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

uint64_t Sign::observe()
{
  return static_cast<uint64_t>(val[0]);
}

uint64_t Sign::steal()
{
  uint64_t result = observe();
  tear();
  return result;
}

string Sign::read(bool eraseAfterRead)
{
  string result = val;
  if(eraseAfterRead) tearAll();
  return result;
}
