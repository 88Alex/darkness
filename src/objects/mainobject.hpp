#ifndef MAINOBJECT_HPP_INCLUDED
#define MAINOBJECT_HPP_INCLUDED

#include <string>
#include <map>

using namespace std;

typedef enum { OT_MANIPULATOR, OT_ENTROPY, OT_STALKER, OT_SIGN } ObjectType;

class MainObject
{
	public:
		MainObject();
		// NOTE: The names of the following functions are as specified by language reference.
		// I did not make them up!
		void twist(ObjectType type, string name);
		Object* getObject(string name);
		void consume(string name);
		void empty();
private:
		map<string, Object*> objects;
};

#endif // #ifndef MAINOBJECT_HPP_INCLUDED