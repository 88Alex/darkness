#include "interpreter.hpp"

using namespace std;

void interpretCommand(string line, string mainObjName, MainObject *mainObject)
{
  //
}

bool isLetter(char c)
{
  return ('A' <= c && c <= 'Z') || ('a' <= c && c <= 'z');
}

bool isAlphaNumeric(char c)
{
  return ('0' <= c && c <= '9') || isLetter(c);
}

string parseFirstLine(string firstLine)
{
  string mainObjName = "";
  if(firstLine[0] != '+')
  {
    throw CriticalError("Invalid syntax at first line");
  }
  if(!isLetter(firstLine[1]))
  {
    throw CriticalError("Invalid syntax at first line");
  }
  int i = 1;
  for(; firstLine[i] != ' '; i++)
  {
    mainObjName.append(1, firstLine[i]);
  }
  if(firstLine.find(" hell") != i)
  {
    throw CriticalError("Invalid syntax at first line");
  }
  return mainObjName;
}

int runScript(vector<string> lines)
{
  int sanity = 100;
  try
  {
    string mainObjName = parseFirstLine(lines[0]);
    MainObject *mainObject = new MainObject();
    for(int i = 1; i < lines.size(); i++)
    {
      interpretCommand(lines[i], mainObjName, mainObject);
    }
  }
  catch(Error e)
  {
    sanity--;
    if(sanity < 1) goInsane();
  }
  catch(CriticalError ce)
  {
    cerr << ce.what() << endl;
    return 2;
  }
}
