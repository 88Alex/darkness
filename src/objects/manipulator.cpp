#include "manipulator.hpp"

Variable::Variable(VarSize varsize, uint64_t val, uint disposition, bool master)
{
	size = varsize;
	value = val;
	this->disposition = disposition;
	this->master = master;
	servants = map<string, Variable>();
}

uint64_t Variable::getValue()
{
	return value;
}

VarSize Variable::getSize()
{
	return size;
}

uint Variable::getDisposition()
{
	return disposition;
}

void Variable::setValue(uint64_t val)
{
	value = val;
	switch(size)
	{
		case BYTE:
			value %= 256;
			break;
		case SHORT:
			value %= 65536;
			break;
		case INT:
			value %= (long) 2 << 32;
			break;
	}
}

map<string, Variable> Variable::getServants()
{
	if(!master) throw 0;
	return servants;
}

void Variable::addServant(string varname, Variable var)
{
	if(!master) throw 0;
	servants.at(varname) = var;
}

bool Variable::isMaster()
{
	return master;
}

Manipulator::Manipulator()
{
	variables = map<string, Variable>();
}

void Manipulator::manufactureMaster(string varname, uint disposition, VarSize size)
{
	Variable var = Variable(size, 0, disposition, true);
	variables.at(varname) = var;
}

void Manipulator::manufactureServant(string varname, uint disposition, VarSize size, string mastername)
{
	Variable var = Variable(size, 0, disposition, false);
	if(variables.at(mastername).isMaster()) variables.at(mastername).addServant(varname, var);
	variables.at(varname) = var;
}