/*
 * Darkness: an interpreter for the Dark programming language.
 * Darkness is licensed under the MIT license, which can be found in the LICENSE file in the project's root directory.
 */

#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <vector>
#include "error.hpp"
#include "objects/mainobject.hpp"
#include "objects/manipulator.hpp"

using namespace std;

void displayHelp()
{
	cout << "Usage: darkness [options] file.dark" << endl;
}

vector<string> parseFile(string filename)
{
	vector<string> result = vector<string>();
	ifstream file(filename.c_str());
	string line;
	while(getline(file, line))
	{
		result.push_back(line);
	}
}

int runScript(vector<string> lines)
{
	//
}

int main(int argc, char** argv)
{
	if(argc < 2)
	{
		displayHelp();
		exit(0);
	}
	vector<string> lines = parseFile(string(argv[2]));
	return runScript(lines);
}