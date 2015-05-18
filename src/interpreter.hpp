#ifndef INTERPRETER_HPP_INCLUDED
#define INTERPRETER_HPP_INCLUDED

#include <vector>
#include <string>
#include <boost/regex.hpp>
#include "error.hpp"
#include "objects/mainobject.hpp"
#include "objects/manipulator.hpp"
#include "voicelist.hpp"
#include <boost/algorithm/string.hpp>
#include <boost/regex.hpp>

using namespace std;

int runScript(vector<string> lines);

#endif // #ifndef INTERPRETER_HPP_INCLUDED
