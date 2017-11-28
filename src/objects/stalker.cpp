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

char Stalker::controlChar(string varname)
{
  checkInitialized();
  char c;
  cin >> c;
  Manipulator::getFromAllManipulators(varname)->setValue((int) c);
}

uint64_t Stalker::controlNumber(string varname)
{
  checkInitialized();
  uint64_t i;
  cin >> i;
  Manipulator::getFromAllManipulators(varname)->setValue(i);
}

void Stalker::actionChar(string varname)
{
  checkInitialized();
  uint64_t var = Manipulator::getConstFromAllManipulators(varname);
  char c = static_cast<char>(var);
  if(isDistant) output << c;
  else cout << c;
}

void Stalker::actionNumber(string varname)
{
  checkInitialized();
  uint64_t var = Manipulator::getConstFromAllManipulators(varname);
  if(isDistant) output << var;
  else cout << var;
}

void Stalker::echo()
{
  checkInitialized();
  if(isDistant) output << Voicelist::get()->read();
  else cout << Voicelist::get()->read();
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
  output.seekg(0, output.end);
  int length = output.tellg();
  output.seekg(0, output.beg);
  char* data = new char[length + 1];
  output.read(data, length);
  data[length] = 0;
  cout << data;
}

void Stalker::checkInitialized()
{
  if(!initialized) throw StalkerUninitializedError();
}
