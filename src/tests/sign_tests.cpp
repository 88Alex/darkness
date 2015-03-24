#include "../objects/sign.hpp"
#include <string>
#include <iostream>
using namespace std;

int main()
{
  Manipulator m;
  m.manufactureMaster("a", 0, BYTE);
  m.set("a", 54);
  Sign s;
  s.scrawlCharacter("a");
  cout << s.read(false) << endl;
  s.tear();
  s.scrawlNumber("a");
  cout << s.read(false) << endl;
  s.tear(2);
  s.scrawl("Hello, World!\n");
  cout << s.read(false) << endl;
}
