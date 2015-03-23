#ifndef ERROR_HPP_INCLUDED
#define ERROR_HPP_INCLUDED

#include <exception>
#include <random>
#include <string>

using namespace std;

class Error : public exception
{
	const char* what();
};

class CriticalError : public exception
{
	const char* what();
};

class StalkerUninitializedError : public exception
{
	const char* what();
};

void goInsane(); // THIS IS ACTUALLY DOCUMENTED IN THE SPECS- THIS IS NOT AN EASTER EGG!!!

#endif