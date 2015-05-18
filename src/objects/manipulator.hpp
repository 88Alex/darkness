#ifndef MANIPULATOR_HPP_INCLUDED
#define MANIPULATOR_HPP_INCLUDED

#include <string>
#include <map>
#include <cinttypes>
#include <typeinfo>
#include <random>
#include <algorithm>
#include "object.hpp"
#include "../error.hpp"

using namespace std;

typedef enum { BYTE = 8, SHORT = 16, INT = 32, LONG = 64 } VarSize;

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
		void set(string varname, uint64_t value);
		void add(string varname, uint64_t val1, uint64_t val2);
		void subtract(string varname, uint64_t val1, uint64_t val2);
		void multiply(string varname, uint64_t val1, uint64_t val2);
		void divide(string varname, uint64_t val1, uint64_t val2);
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
};

#endif // #ifndef MANIPULATOR_HPP_INCLUDED
