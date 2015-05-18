#ifndef VOICELIST_HPP_INCLUDED
#define VOICELIST_HPP_INCLUDED

#include <string>
#include <vector>
using namespace std;

// Note: this class uses the "singleton" design pattern.
// There is only one instance of the Voicelist class.
// This instance is managed internally, and accessed through get().

class Voicelist
{
  public:
    static Voicelist* get();
    void enqueue(string str);
    string read();
  private:
    Voicelist(); // private constructor for singleton pattern
    static Voicelist* voicelist;
    vector<string> list;
};

#endif // #ifndef VOICELIST_HPP_INCLUDED
