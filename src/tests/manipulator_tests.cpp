#include <iostream>
#include <string>
#include "../objects/manipulator.hpp"
using namespace std;

int main()
{
	Manipulator m = Manipulator();
	m.manufactureMaster("a", 1, INT);
	m.manufactureServant("b", 1, INT, "a");
	m.set("a", 5);
	m.set("b", 6);
	if(m.get("a") == 5)
	{
		cout << "Test 1 Part A Passed (a == 5)" << endl;
	}
	else
	{
		cout << "Test 1 Part A Failed! (a != 5) (a == " << m.get("b") << ")" << endl;
	}
	if(m.get("b") == 6)
	{ 
                cout << "Test 1 Part B Passed (b == 6)" << endl;
        }
        else
        { 
                cout << "Test 1 Part B Failed! (b != 6) (b == " << m.get("b") << ")" << endl;
        }

}
