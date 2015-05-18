#include "interpreter.hpp"

#define DEBUG
#ifdef DEBUG
#define DEBUG(code) code
#else
#define DEBUG(code)
#endif

using namespace std;

class GotoEvent : public exception
{
  public:
  GotoEvent(uint ip_)
  {
    ip = ip_;
  }
  uint getIP()
  {
    return ip;
  }
  private:
  uint ip;
};

bool isNumber(string str)
{
  boost::regex numberRegex = boost::regex();
  numberRegex.assign("[0-9]+"); // only natural numbers and 0
  boost::cmatch m; // required by Boost- NOT USED
  bool result = boost::regex_match(str.c_str(), m, numberRegex);
  return result;
}

void interpretMainObjectCommand(MainObject *mainObject, vector<string> arguments)
{
  DEBUG(cout << "Executing main object command: " << arguments[0] << endl;)
  if(arguments[0] == "twist")
  {
    DEBUG(cout << "Creating new object: type = " << arguments[1] << "; name = " << arguments[2] << endl;)
    if(arguments.size() < 3) throw Error();
    ObjectType type = OT_NONE;
    if(arguments[1] == "manipulator") type = OT_MANIPULATOR;
    else if(arguments[1] == "entropy") type = OT_ENTROPY;
    else if(arguments[1] == "stalker") type = OT_STALKER;
    else if(arguments[1] == "sign") type = OT_SIGN;
    if(type == OT_NONE)
    {
      DEBUG(cout << "New object has undefined type!" << endl;)
      throw Error();
    }
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
  DEBUG(cout << "Executing manipulator command: " << arguments[0] << endl;)
  if(arguments[0] == "manufacture")
  {
    if(arguments.size() < 5) throw Error();
    string varname = arguments[1];
    uint disposition = atoi(arguments[2].c_str());
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
      size = LONG;
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
    uint disposition = atoi(arguments[1].c_str());
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
      val = atoi(arguments[2].c_str());
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
      val1 = atoi(arguments[2].c_str());
    }
    else
    {
      val1 = manipulator->get(arguments[2]);
    }
    if(isNumber(arguments[3]))
    {
      val2 = atoi(arguments[3].c_str());
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
      val1 = atoi(arguments[2].c_str());
    }
    else
    {
      val1 = manipulator->get(arguments[2]);
    }
    if(isNumber(arguments[3]))
    {
      val2 = atoi(arguments[3].c_str());
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
      val1 = atoi(arguments[2].c_str());
    }
    else
    {
      val1 = manipulator->get(arguments[2]);
    }
    if(isNumber(arguments[3]))
    {
      val2 = atoi(arguments[3].c_str());
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
      val1 = atoi(arguments[2].c_str());
    }
    else
    {
      val1 = manipulator->get(arguments[2]);
    }
    if(isNumber(arguments[3]))
    {
      val2 = atoi(arguments[3].c_str());
    }
    else
    {
      val2 = manipulator->get(arguments[3]);
    }
    manipulator->divide(arguments[1], val1, val2);
  }
}

void interpretEntropyCommand(Entropy *entropy, vector<string> arguments, uint ip)
{
  DEBUG(cout << "Executing entropy command: " << arguments[0] << endl;)
  if(arguments[0] == "choice")
  {
    if(arguments.size() < 4) throw Error();
    uint64_t val1, val2;
    if(isNumber(arguments[1]))
    {
      val1 = atoi(arguments[1].c_str());
    }
    else
    {
      val1 = Manipulator::getConstFromAllManipulators(arguments[1]);
    }
    Comparator cmp;
    if(arguments[2] == "=" || arguments[2] == "==") cmp = EQUALS;
    else if(arguments[2] == ">") cmp = GT;
    else if(arguments[2] == "<") cmp = LT;
    else if(arguments[2] == ">=") cmp = GTE;
    else if(arguments[2] == "<=") cmp = LTE;
    else if(arguments[2] == "!=" || arguments[2] == "<>") cmp = NE;
    else throw Error();
    if(isNumber(arguments[3]))
    {
      val2 = atoi(arguments[3].c_str());
    }
    else
    {
      val2 = Manipulator::getConstFromAllManipulators(arguments[3]);
    }
    entropy->choice(val1, cmp, val2);
  }
  else if(arguments[0] == "balance")
  {
    entropy->balance();
  }
  else if(arguments[0] == "reprogram")
  {
    entropy->reprogram();
  }
  else if(arguments[0] == "corpse")
  {
    if(arguments.size() < 2) throw Error();
    string lblname = arguments[1];
    entropy->corpse(lblname, ip);
  }
  else if(arguments[0] == "stumble")
  {
    if(arguments.size() < 2) throw Error();
    string lblname = arguments[1];
    uint newIp = entropy->stumble(lblname);
    throw GotoEvent(newIp);
  }
  else if(arguments[0] == "illusion")
  {
    if(arguments.size() < 2) throw Error();
    string lblname = arguments[1];
    entropy->illusion(lblname);
  }
}

void interpretStalkerCommand(Stalker *stalker, vector<string> arguments, MainObject* mainObject)
{
  DEBUG(cout << "Executing stalker command: " << arguments[0] << endl;)
  if(arguments[0] == "stalk")
  {
    stalker->stalk();
  }
  else if(arguments[0] == "control")
  {
    if(arguments.size() < 2) throw Error();
    if(arguments[1] == "#")
    {
      if(arguments.size() < 3) throw Error();
      stalker->controlNumber(arguments[2]);
    }
    else
    {
      stalker->controlChar(arguments[1]);
    }
  }
  else if(arguments[0] == "action")
  {
    if(arguments.size() < 2) throw Error();
    if(arguments[1] == "#")
    {
      if(arguments.size() < 3) throw Error();
      stalker->actionNumber(arguments[2]);
    }
    else
    {
      stalker->actionChar(arguments[1]);
    }
  }
  else if(arguments[0] == "echo")
  {
    stalker->echo();
  }
  else if(arguments[0] == "distant")
  {
    stalker->distant();
  }
  else if(arguments[0] == "personal")
  {
    stalker->personal();
  }
  else if(arguments[0] == "paracusia")
  {
    stalker->paracusia();
  }
}

void interpretSignCommand(Sign *sign, vector<string> arguments, MainObject *mainObject)
{
  DEBUG(cout << "Executing sign command: " << arguments[0] << endl;)
  if(arguments[0] == "scrawl")
  {
    if(arguments.size() < 2) throw Error();
    if(arguments[1] == "#")
    {
      if(arguments.size() < 3) throw Error();
      sign->scrawlNumber(arguments[2]);
    }
    else if(arguments[1] == "\"")
    {
      if(arguments.size() < 3) throw Error();
      string str;
      for(int i = 2; i < arguments.size(); i++)
      {
        str.append(arguments[i]);
        str.append(" ");
      }
      str.append("\n");
      sign->scrawl(str);
    }
    else
    {
      sign->scrawlCharacter(arguments[1]);
    }
  }
  else if(arguments[0] == "tear")
  {
    if(arguments.size() == 1)
    {
      sign->tear();
    }
    else
    {
      if(arguments.size() < 2) throw Error();
      if(arguments[1] == "*")
      {
        sign->tearAll();
      }
      else
      {
        sign->tear(atoi(arguments[1].c_str()));
      }
    }
  }
  else if(arguments[0] == "observe")
  {
    if(arguments.size() < 2) throw Error();
    sign->observe(arguments[1]);
  }
  else if(arguments[0] == "steal")
  {
    if(arguments.size() < 2) throw Error();
    sign->steal(arguments[1]);
  }
  else if(arguments[0] == "read")
  {
    if(arguments.size() == 1)
    {
      sign->read(true);
    }
    else if(arguments[1] == "~")
    {
      sign->read(false);
    }
    else sign->read(true);
  }
}

void interpretCommand(string line, string mainObjName, MainObject *mainObject, int ip)
{
  // first check whether or not to skip this line
  vector<Entropy*> entropies = mainObject->getEntropies();
  for(int i = 0; i < entropies.size(); i++)
  {
    if(entropies[i]->skipInstruction())
    {
      return;
    }
  }
  string objname = "";
  size_t foundDollarSign = line.find("$", 0);
  if(foundDollarSign == string::npos)
  {
    throw Error();
  }
  objname = line.substr(0, foundDollarSign);
  string argstr = line.substr(foundDollarSign + 1);
  vector<string> arguments = vector<string>();
  boost::split(arguments, argstr, boost::is_any_of(" "), boost::token_compress_on);
  if(objname == mainObjName)
  {
    interpretMainObjectCommand(mainObject, arguments);
    return;
  }
  Object* object = mainObject->getObject(objname);
  if(object == 0)
  {
    DEBUG(cout << "Object " << objname << " not found!" << endl;)
    throw Error();
  }
  switch(mainObject->getObjType(objname))
  {
    case OT_MANIPULATOR:
      interpretManipulatorCommand((Manipulator*)object, arguments);
      break;
    case OT_ENTROPY:
      interpretEntropyCommand((Entropy*)object, arguments, ip);
      break;
    case OT_STALKER:
      interpretStalkerCommand((Stalker*)object, arguments, mainObject);
      break;
    case OT_SIGN:
      interpretSignCommand((Sign*)object, arguments, mainObject);
      break;
    default:
      DEBUG(cout << "Object " << objname << " has undefined type" << endl;)
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
  string mainObjName = parseFirstLine(lines[0]);
  MainObject *mainObject = new MainObject();
  for(int i = 1; i < lines.size(); i++)
  {
    try
    {
      interpretCommand(lines[i], mainObjName, mainObject, i);
    }
    catch(GotoEvent ge)
    {
      i = ge.getIP();
    }
    catch(Error e)
    {
      DEBUG(cout << "Error occured!" << endl;)
      sanity--;
      if(sanity < 1) goInsane();
    }
    catch(CriticalError ce)
    {
      cerr << ce.what() << endl;
      return 2;
    }
  }
}
