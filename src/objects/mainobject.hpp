#ifndef MAINOBJECT_HPP_INCLUDED
#define MAINOBJECT_HPP_INCLUDED

#include <string>
#include <map>
#include "object.hpp"
#include "manipulator.hpp"
#include "entropy.hpp"
#include "stalker.hpp"
#include "sign.hpp"

using namespace std;

class MainObject
{
	public:
		MainObject();
		// Note: The names of the following functions are as specified by language reference.
		// I did not make them up!
		void twist(ObjectType type, string name);
		Object* getObject(string name);
    void break_(string error = "Program willingly terminated");
		void consume(string name);
		void empty();
private:
		map<string, Object*> objects;
};

#endif // #ifndef MAINOBJECT_HPP_INCLUDED
