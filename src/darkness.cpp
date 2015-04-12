/*
 * Darkness: an interpreter for the Dark programming language.
 * Darkness is licensed under the MIT license, which can be found in the LICENSE file in the project's root directory.
 */

#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <vector>
#include "interpreter.hpp"

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
	while(!file.eof())
	{
		getline(file, line);
    result.push_back(line);
	}
  return result;
}


int main(int argc, char** argv)
{
	if(argc < 2)
	{
		displayHelp();
		exit(0);
	}
  string filename = string(argv[1]);
	vector<string> lines = parseFile(filename);
	return runScript(lines);
}
