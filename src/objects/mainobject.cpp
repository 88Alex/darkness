#include "mainobject.hpp"

#define DEBUG
#ifdef DEBUG
#define DEBUG(code) code
#else
#define DEBUG(code)
#endif

MainObject::MainObject()
{
	objects = map<string, Object*>();
}

void MainObject::twist(ObjectType type, string name)
{
	// TODO: Test for duplicate names
	switch(type)
	{
		case OT_MANIPULATOR:
      DEBUG(cout << "Creating new manipulator " << name << endl;)
			objects[name] = new Manipulator();
			break;
		case OT_ENTROPY:
      DEBUG(cout << "Creating new entropy " << name << endl;)
			objects[name] = new Entropy();
			break;
		case OT_STALKER:
      DEBUG(cout << "Creating new stalker " << name << endl;)
			objects[name] = new Stalker();
			break;
		case OT_SIGN:
      DEBUG(cout << "Creating new sign " << name << endl;)
			objects[name] = new Sign();
			break;
		default:
			throw Error();
	}
}

void MainObject::break_(string error)
{
  cerr << error << endl;
  throw CriticalError();
}

void MainObject::consume(string name)
{
	delete objects[name];
	objects.erase(name);
}

void MainObject::empty()
{
	for(map<string, Object*>::iterator i = objects.begin(); i != objects.end(); ++i)
	{
		delete i->second;
	}
	objects.clear();
}

Object* MainObject::getObject(string name)
{
  if(objects.count(name) >= 1)
  {
    return objects[name];
  }
  else return 0;
}

ObjectType MainObject::getObjType(string name)
{
  if(objects.count(name) < 1)
  {
    DEBUG(cout << "Object " << name << " not found when queried for type" << endl;)
    return OT_NONE;
  }
  return objects[name]->getType();
}

vector<Entropy*> MainObject::getEntropies()
{
  vector<Entropy*> entropies = vector<Entropy*>();
  for(map<string, Object*>::iterator i = objects.begin(); i != objects.end(); ++i)
  {
    if(i->second->getType() == OT_ENTROPY)
    {
      entropies.push_back((Entropy*)i->second);
    }
  }
  return entropies;
}
