#include "error.hpp"

const char* Error::what()
{
	return "An interesting occurence...";
}

const char* CriticalError::what()
{
	return "Murphy's Law is working correctly...";
}

const char* StalkerUninitializedError::what()
{
	default_random_engine generator;
	uniform_int_distribution<int> distribution(1, 3);
	int randomMessage = distribution(generator);
	switch(randomMessage)
	{
		case 1:
			return "All of your ingenious plans have failed.";
		case 2:
			return "It is not worth trying any further. We were doomed from the time we started.";
		case 3:
			return "What a pathetic waste of effort...";
		default:
			throw CriticalError();
	}
}

void goInsane()
{
	// This is going to be fun.
}