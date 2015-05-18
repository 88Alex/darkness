#include "manipulator.hpp"

vector<Manipulator*> Manipulator::manipulators = vector<Manipulator*>();

Variable::Variable(VarSize varsize, uint64_t val, uint disposition, bool master)
{
	size = varsize;
	value = val;
	this->disposition = disposition;
	this->master = master;
	servantNames = vector<string>();
  servants = vector<Variable*>();
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

vector<string> Variable::getServants()
{
	ticksSinceUsed = 0;
	if(!master) throw Error();
	return servantNames;
}

void Variable::addServant(string varname, Variable *var)
{
	ticksSinceUsed = 0;
	if(!master) throw Error();
	servantNames.push_back(varname);
  servants.push_back(var);
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
  manipulators.push_back(this);
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
	if(variable(mastername)->isMaster()) variable(mastername)->addServant(varname, var);
	varnames.push_back(varname);
	variables.push_back(var);
}

void Manipulator::kill(string varname)
{
	if(count(varnames.begin(), varnames.end(), varname) == 0) throw Error();
	delete variable(varname);
	variables.at(distance(varnames.begin(), find(varnames.begin(), varnames.end(), varname))) = 0;
}

void Manipulator::suicide(string varname)
{
	kill(varname);
}

void Manipulator::void_()
{
	for(int i = 0; i < varnames.size(); i++)
	{
		if(variables[i] == 0)
		{
			varnames.erase(find(varnames.begin(), varnames.end(), varnames[i]));
      variables.erase(find(variables.begin(), variables.end(), variables[i]));
		}
	}
}

void Manipulator::genocide(uint disposition)
{
	for(int i = 0; i < varnames.size(); i++)
  {
    if(variables.at(i)->getDisposition() == disposition)
    {
      kill(varnames.at(i));
    }
  }
}

void Manipulator::omnicide()
{
	for(int i = 0; i < varnames.size(); i++)
  {
    kill(varnames.at(i));
  }
}

void Manipulator::chaos(string varname)
{
	default_random_engine generator;
	uniform_int_distribution<uint64_t> distribution(0, (long) 1 << variable(varname)->getSize());
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

Variable* Manipulator::getMutable(string varname)
{
  return variable(varname);
}

uint64_t Manipulator::get(string varname)
{
	return variable(varname)->getValue();
}

Variable* Manipulator::getFromAllManipulators(string varname)
{
  for(int i = 0; i < manipulators.size(); i++)
  {
    Manipulator* m = manipulators.at(i);
    Variable* result;
    try
    {
      result = m->getMutable(varname);
    }
    catch(Error e)
    {
      continue;
    }
    return result;
  }
  throw Error();
}

uint64_t Manipulator::getConstFromAllManipulators(string varname)
{
  for(int i = 0; i < manipulators.size(); i++)
  {
    Manipulator* m = manipulators.at(i);
    uint64_t result;
    try
    {
      result = m->get(varname);
    }
    catch(Error e)
    {
      continue;
    }
    return result;
  }
  throw Error();
}

Variable* Manipulator::variable(string varname)
{
	if(count(varnames.begin(), varnames.end(), varname) >= 1)
	{
		return variables.at(distance(varnames.begin(), find(varnames.begin(), varnames.end(), varname)));
	}
	else
	{
		throw Error();
	}
}
