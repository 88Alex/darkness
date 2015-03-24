#include "../objects/stalker.hpp"
#include <string>
#include <iostream>
using namespace std;

int main()
{
  Manipulator m;
  m.manufactureMaster("a", 0, BYTE);
  m.set("a", 54);
  m.manufactureMaster("newline", 0, BYTE);
  m.set("newline", 10);
  Stalker s;
  s.stalk();
  s.personal();
  s.actionChar("a");
  s.actionChar("newline");
  s.actionNumber("a");
  s.actionChar("newline");
  m.set("a", s.controlChar());
  s.actionChar("a");
  s.actionChar("newline");
  m.set("a", s.controlNumber());
  s.actionNumber("a");
  s.actionChar("newline");
  s.distant();
  m.set("a", 54);
  s.actionChar("a");
  s.actionNumber("a");
  cout << "This should happen before the final output." << endl;
  s.paracusia();
}
