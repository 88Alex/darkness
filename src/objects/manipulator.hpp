#ifndef MANIPULATOR_HPP_INCLUDED
#define MANIPULATOR_HPP_INCLUDED

#include <string>
#include <map>
#include <cinttypes>
#include <typeinfo>
#include <random>
#include <algorithm>
#include <boost/regex.hpp>
#include "object.hpp"
#include "../error.hpp"

using namespace std;

typedef enum { BYTE = 8, SHORT = 16, INT = 32, LONG = 64 } VarSize;

bool isNumber(string str);

class Variable
{
	public:
		Variable(VarSize varsize, uint64_t val, uint disposition, bool master);
		uint64_t getValue();
		VarSize getSize();
		uint getDisposition();
		void setValue(uint64_t val);
		vector<string> getServants();
		void addServant(string varname, Variable *var);
		bool isMaster();
		void tick();
	private:
		VarSize size;
		uint64_t value;
		uint disposition;
		bool master;
		vector<string> servantNames;
    vector<Variable*> servants;
		int ticksSinceUsed;
};

class Manipulator : public Object
{
	public:
		Manipulator();
		void manufactureMaster(string varname, uint disposition, VarSize size);
		void manufactureServant(string varname, uint disposition, VarSize size, string mastername = "");
		void kill(string varname);
		void suicide(string varname);
		void void_(); // NOTE the underscore at the end of the function name
		void genocide(uint disposition);
		void omnicide();
		void chaos(string varname);
		void set(string dest, string source);
		void add(string varname, string arg1, string arg2);
		void subtract(string varname, string arg1, string arg2);
		void multiply(string varname, string arg1, string val2);
		void divide(string varname, string arg1, string val2);
    Variable* getMutable(string varname);
		uint64_t get(string varname);
    static Variable* getFromAllManipulators(string varname);
    static uint64_t getConstFromAllManipulators(string varname);
		void tick();
    ObjectType getType() { return OT_MANIPULATOR; }
	private:
		vector<string> varnames;
		vector<Variable*> variables;
		Variable* variable(string varname);
    static vector<Manipulator*> manipulators;
    void checkDispositionConflicts(string var1, string var2);
};

#endif // #ifndef MANIPULATOR_HPP_INCLUDED
