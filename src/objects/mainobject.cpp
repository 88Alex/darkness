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
			exit(1); // TODO- perhaps display a meaningful error message?
	}
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