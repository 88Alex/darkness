#ifndef SIGN_HPP_INCLUDED
#define SIGN_HPP_INCLUDED

#include <string>
#include "manipulator.hpp"
#include "object.hpp"

class Sign : public Object
{
  public:
    Sign();
    Sign(string str);
    void scrawlCharacter(string varname);
    void scrawlNumber(string varname);
    void scrawl(string varname);
    void tear();
    void tear(size_t n);
    void tearAll();
    uint64_t observe();
    uint64_t steal();
    string read(bool eraseAfterRead);
    const ObjectType type = OT_SIGN;
  private:
    string val;
};

#endif // #ifndef SIGN_HPP_INCLUDED
