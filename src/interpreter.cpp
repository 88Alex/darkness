#include "interpreter.hpp"

using namespace std;

bool isNumber(string str)
{
  boost::regex numberRegex = "[0-9]+"; // only natural numbers and 0
  boost::cmatch m // required by Boost- NOT USED
  return boost::regex_match(str, m, numberRegex);
}

void interpretMainObjectCommand(MainObject *mainObject, vector<string> arguments)
{
  if(arguments[0] == "twist")
  {
    if(arguments.size() < 3) throw Error();
    ObjectType type = OT_NONE;
    if(arguments[1] == "manipulator") type = OT_MANIPULATOR;
    else if(arguments[1] == "entropy") type = OT_ENTROPY;
    else if(arguments[1] == "stalker") type = OT_STALKER;
    else if(arguments[1] == "sign") type = OT_SIGN;
    mainObject->twist(type, arguments[2]);
  }
  else if(arguments[0] == "consume")
  {
    if(arguments.size() < 2) throw Error();
    mainObject->consume(arguments[1]);
  }
  else if(arguments[0] == "break")
  {
    if(arguments.size() < 2)
    {
      mainObject->break_("");
    }
    else
    {
      mainObject->break_(arguments[1]);
    }
  }
  else if(arguments[0] == "empty")
  {
    mainObject->empty();
  }
  else if(arguments[0] == "apocalypse")
  {
    delete mainObject;
    exit(0);
  }
}

void interpretManipulatorCommand(Manipulator *manipulator, vector<string> arguments)
{
  if(arguments[0] == "manufacture")
  {
    if(arguments.size() < 5) throw Error();
    string varname = arguments[1];
    uint disposition = atoi(arguments[2]);
    VarSize size;
    if(arguments[3] == "8")
    {
      size = BYTE;
    }
    else if(arguments[3] == "16")
    {
      size = SHORT;
    }
    else if(arguments[3] == "32")
    {
      size = INT;
    }
    else if(arguments[4] == "64")
    {
      size = LONG:
    }
    else throw Error();
    if(arguments[4] == "master")
    {
      manipulator->manufactureMaster(varname, disposition, size);
    }
    else if(arguments[4] == "servant")
    {
      string mastername = "";
      if(arguments.size() >= 6)
      {
        mastername = arguments[5];
      }
      manipulator->manufactureServant(varname, disposition, size, mastername);
    }
  }
  else if(arguments[0] == "suicide")
  {
    if(arguments.size() < 2) throw Error();
    manipulator->kill(arguments[1]);
  }
  else if(arguments[0] == "kill")
  {
    if(arguments.size() < 2) throw Error();
    manipulator->kill(arguments[1]);
  }
  else if(arguments[0] == "void")
  {
    manipulator->void_();
  }
  else if(arguments[0] == "genocide")
  {
    if(arguments.size() < 2) throw Error();
    uint disposition = atoi(arguments[1]);
    manipulator->genocide(disposition);
  }
  else if(arguments[0] == "omnicide")
  {
    manipulator->omnicide();
  }
  else if(arguments[0] == "chaos")
  {
    if(arguments.size() < 2) throw Error();
    manipulator->chaos(arguments[1]);
  }
  else if(arguments[0] == "set")
  {
    if(arguments.size() < 3) throw Error();
    uint64_t val;
    if(isNumber(arguments[2]))
    {
      val = atoi(arguments[2]);
    }
    else
    {
      val = manipulator->get(arguments[2]);
    }
    manipulator->set(arguments[1], val);
  }
  else if(arguments[0] == "add")
  {
    if(arguments.size() < 4) throw Error();
    uint64_t val1, val2;
    if(isNumber(arguments[2]))
    {
      val1 = atoi(arguments[2]);
    }
    else
    {
      val1 = manipulator->get(arguments[2]);
    }
    if(isNumber(arguments[3]))
    {
      val2 = atoi(arguments[3]);
    }
    else
    {
      val2 = manipulator->get(arguments[3]);
    }
    manipulator->add(arguments[1], val1, val2);
  }
  else if(arguments[0] == "subtract")
  {
    if(arguments.size() < 4) throw Error();
    uint64_t val1, val2;
    if(isNumber(arguments[2]))
    {
      val1 = atoi(arguments[2]);
    }
    else
    {
      val1 = manipulator->get(arguments[2]);
    }
    if(isNumber(arguments[3]))
    {
      val2 = atoi(arguments[3]);
    }
    else
    {
      val2 = manipulator->get(arguments[3]);
    }
    manipulator->subtract(arguments[1], val1, val2);
  }
  else if(arguments[0] == "multiply")
  {
    if(arguments.size() < 4) throw Error();
    uint64_t val1, val2;
    if(isNumber(arguments[2]))
    {
      val1 = atoi(arguments[2]);
    }
    else
    {
      val1 = manipulator->get(arguments[2]);
    }
    if(isNumber(arguments[3]))
    {
      val2 = atoi(arguments[3]);
    }
    else
    {
      val2 = manipulator->get(arguments[3]);
    }
    manipulator->multiply(arguments[1], val1, val2);
  }
  else if(arguments[0] == "divide")
  {
    if(arguments.size() < 4) throw Error();
    uint64_t val1, val2;
    if(isNumber(arguments[2]))
    {
      val1 = atoi(arguments[2]);
    }
    else
    {
      val1 = manipulator->get(arguments[2]);
    }
    if(isNumber(arguments[3]))
    {
      val2 = atoi(arguments[3]);
    }
    else
    {
      val2 = manipulator->get(arguments[3]);
    }
    manipulator->divide(arguments[1], val1, val2);
  }
}

void interpretEntropyCommand(Entropy *entropy, vector<string> arguments)
{
  //
}

void interpretStalkerCommand(Stalker *stalker, vector<string> arguments)
{
  //
}

void interpretSignCommand(Sign *sign, vector<string> arguments)
{
  //
}

void interpretCommand(string line, string mainObjName, MainObject *mainObject)
{
  string objname = "";
  size_t foundDollarSign = line.find("$", 0);
  if(foundDollarSign == string::npos)
  {
    throw Error();
  }
  objname = line.substr(0, foundDollarSign);
  size_t foundSpace = line.find(" ", foundDollarSign + 1);
  string argstr = line.substr(foundSpace + 1);
  vector<string> arguments = vector<string>();
  boost::split(arguments, argstr, boost::is_any_of(" "), boost::token_compress_on);
  if(objname == mainObjName)
  {
    interpretMainObjectCommand(mainObject, arguments);
  }
  Object* object = mainObject->getObject(objname);
  if(object == 0) throw Error();
  switch(object->type)
  {
    case OT_MANIPULATOR:
      interpretManipulatorCommand((Manipulator*)object, arguments);
      break;
    case OT_ENTROPY:
      interpretEntropyCommand((Entropy*)object, arguments);
      break;
    case OT_STALKER:
      interpretStalkerCommand((Stalker*)object, arguments);
      break;
    case OT_SIGN:
      interpretSignCommand((Sign*)object, arguments);
      break;
    default:
      throw Error();
  }
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
