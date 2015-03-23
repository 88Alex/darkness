#include "manipulator.hpp"

Variable::Variable(VarSize varsize, uint64_t val, uint disposition, bool master)
{
	size = varsize;
	value = val;
	this->disposition = disposition;
	this->master = master;
	servants = map<string, Variable*>();
	ticksSinceUsed = 0;
}

uint64_t Variable::getValue()
{
	ticksSinceUsed = 0;
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
	ticksSinceUsed = 0;
}

map<string, Variable*> Variable::getServants()
{
	ticksSinceUsed = 0;
	if(!master) throw Error();
	return servants;
}

void Variable::addServant(string varname, Variable *var)
{
	ticksSinceUsed = 0;
	if(!master) throw Error();
	servants.at(varname) = var;
}

bool Variable::isMaster()
{
	return master;
}

void Variable::tick()
{
	ticksSinceUsed++;
	if(ticksSinceUsed >= 65535)
	{
		// flip a random bit
		default_random_engine generator;
		uniform_int_distribution<int> distribution(0, size - 1);
		int randomBit = distribution(generator);
		value ^= (long) 1 << randomBit;
		ticksSinceUsed = 32767;
	}
}

Manipulator::Manipulator()
{
	varnames = vector<string>();
	variables = vector<Variable*>();
}

void Manipulator::manufactureMaster(string varname, uint disposition, VarSize size)
{
	if(count(varnames.begin(), varnames.end(), varname) > 0) throw Error();
	Variable* var = new Variable(size, 0, disposition, true);
	varnames.push_back(varname);
	variables.push_back(var);
}

void Manipulator::manufactureServant(string varname, uint disposition, VarSize size, string mastername)
{
	if(count(varnames.begin(), varnames.end(), varname) > 0) throw Error();
	Variable* var = new Variable(size, 0, disposition, false);
	if(variable(mastername)->isMaster()) variable(mastername)->addServant(varname, &var);
	varnames.push_back(varname);
	variables.push_back(var);
}

void Manipulator::kill(string varname)
{
	if(count(varnames.begin(), varnames.end(), varname) == 0) throw Error();
	delete variable(varname);
	variable(varname) = 0;
}

void Manipulator::suicide(string varname)
{
	if(count(varnames.begin(), varnames.end(), varname) == 0) throw Error();
	delete variable(varname);
	variable(varname) = 0;
}

void Manipulator::void_()
{
	for(int i = 0; i < varnames.size(); i++)
	{
		if(variables[i] == 0)
		{
			varnames.
		}
	}
}

void Manipulator::genocide(uint disposition)
{
	for(map<uint, Variable*>::iterator it = variables.begin(); it != variables.end(); it++)
	{
		if(it->second->getDisposition() == disposition)
		{
			delete it->second;
			it->second = 0;
		}
	}
}

void Manipulator::omnicide()
{
	for(map<uint, Variable*>::iterator it = variables.begin(); it != variables.end(); it++)
	{
		delete it->second;
		it->second = 0;
	}
}

void Manipulator::chaos(string varname)
{
	default_random_engine generator;
	uniform_int_distribution<uint64_t> distribution(0, (long) 1 << variables.at(strHash(varname))->getSize());
	variable(varname)->setValue(distribution(generator));
}

void Manipulator::set(string varname, uint64_t value)
{
	variable(varname)->setValue(value);
}

void Manipulator::add(string varname, uint64_t val1, uint64_t val2)
{
	variable(varname)->setValue(val1 + val2);
}

void Manipulator::subtract(string varname, uint64_t val1, uint64_t val2)
{
	variable(varname)->setValue(val1 - val2);
}

void Manipulator::multiply(string varname, uint64_t val1, uint64_t val2)
{
	variable(varname)->setValue(val1 * val2);
}

void Manipulator::divide(string varname, uint64_t val1, uint64_t val2)
{
	if(val2 == 0)
	{
		variable(varname)->setValue(42); // EASTER EGG
	}
	else
	{
		variable(varname)->setValue(val1 / val2);
	}
}

uint64_t Manipulator::get(string varname)
{
	return variable(varname)->getValue();
}

Variable* Manipulator::variable(string varname)
{
	if(variables.count(strHash(varname)) >= 1)
	{
		return variables.at(strHash(varname));
	}
	else
	{
		throw Error();
	}
}