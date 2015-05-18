#include "voicelist.hpp"

Voicelist* Voicelist::voicelist;

Voicelist::Voicelist()
{
  list = vector<string>();
}

Voicelist* Voicelist::get()
{
  if(voicelist == 0)
  {
    voicelist = new Voicelist();
  }
  return voicelist;
}

void Voicelist::enqueue(string str)
{
  list.push_back(str);
}

string Voicelist::read()
{
  string result = list[0];
  list.erase(list.begin());
  return result;
}
