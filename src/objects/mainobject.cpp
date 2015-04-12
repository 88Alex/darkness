#include "mainobject.hpp"

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
			objects[name] = new Manipulator();
			break;
		case OT_ENTROPY:
			objects[name] = new Entropy();
			break;
		case OT_STALKER:
			objects[name] = new Stalker();
			break;
		case OT_SIGN:
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
    return OT_NONE;
  }
  return objects[name]->type;
}
