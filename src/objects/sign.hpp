#ifndef SIGN_HPP_INCLUDED
#define SIGN_HPP_INCLUDED



#include <string>
#include "manipulator.hpp"
#include "object.hpp"
#include "mainobject.hpp"
#include "../voicelist.hpp"

class Sign : public Object
{
  public:
    Sign();
    Sign(string str);
    void scrawlCharacter(string varname);
    void scrawlNumber(string varname);
    void scrawl(string str);
    void tear();
    void tear(size_t n);
    void tearAll();
    void observe(string varname);
    void steal(string varname);
    void read(bool eraseAfterRead);
    ObjectType getType() { return OT_SIGN; }
  private:
    string val;
};

#endif // #ifndef SIGN_HPP_INCLUDED
