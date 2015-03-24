#include "stalker.hpp"

Stalker::Stalker()
{
  initialized = false;
  isDistant = true;
}

void Stalker::stalk()
{
  initialized = true;
}

char Stalker::controlChar()
{
  checkInitialized();
  char c;
  cin >> c;
  return c;
}

uint64_t Stalker::controlNumber()
{
  checkInitialized();
  uint64_t i;
  cin >> i;
  return i;
}

void Stalker::actionChar(string varname)
{
  checkInitialized();
  uint64_t var = Manipulator::getFromAllManipulators(varname);
  char c = static_cast<char>(var);
  if(isDistant) output << c;
  else cout << c;
}

void Stalker::actionNumber(string varname)
{
  checkInitialized();
  uint64_t var = Manipulator::getFromAllManipulators(varname);
  if(isDistant) output << var;
  else cout << var;
}

void Stalker::echo(string str)
{
  checkInitialized();
  if(isDistant) output << str;
  else cout << str;
}

void Stalker::distant()
{
  checkInitialized();
  isDistant = true;
}

void Stalker::personal()
{
  checkInitialized();
  isDistant = false;
}

void Stalker::paracusia()
{
  checkInitialized();
  output.seekg (0, output.end);
  int length = output.tellg();
  output.seekg (0, output.beg);
  char* data = new char[length + 1];
  output.read(data, length);
  data[length] = 0;
  cout << data;
}

void Stalker::checkInitialized()
{
  if(!initialized) throw StalkerUninitializedError();
}
