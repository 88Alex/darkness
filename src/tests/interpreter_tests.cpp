#include <string>
#include <iostream>
#include "../interpreter.cpp"
#include "../error.hpp"

int main()
{
  cout << parseFirstLine("+test hell");
  try
  {
    parseFirstLine("+ hell");
    cout << "#2 Failed!" << endl;
  }
  catch(CriticalError ce)
  {
    cout << "#2 Passed: " << ce.what() << endl;
  }
  try
  {
    parseFirstLine("test hell");
    cout << "#3 Failed!" << endl;
  }
  catch(CriticalError ce)
  {
    cout << "#3 Passed: " << ce.what() << endl;
  }
  try
  {
    parseFirstLine("+test");
    cout << "#4 Failed!" << endl;
  }
  catch(CriticalError ce)
  {
    cout << "#4 Passed: " << ce.what() << endl;
  }
}
