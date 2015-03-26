#ifndef ERROR_HPP_INCLUDED
#define ERROR_HPP_INCLUDED

#include <exception>
#include <random>
#include <string>

using namespace std;

class Error : public exception
{
	public:
    const char* what();
};

class CriticalError : public exception
{
  public:
    CriticalError(string message = "Murphy's Law is working correctly");
    const char* what();
  private:
    string err;
};

class StalkerUninitializedError : public exception
{
	const char* what();
};

void goInsane(); // THIS IS ACTUALLY DOCUMENTED IN THE SPECS- THIS IS NOT AN EASTER EGG!!!

#endif
