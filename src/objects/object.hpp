#ifndef OBJECT_HPP_INCLUDED
#define OBJECT_HPP_INCLUDED

typedef enum { OT_MANIPULATOR, OT_ENTROPY, OT_STALKER, OT_SIGN, OT_NONE } ObjectType;

class Object{
  public:
    virtual ObjectType getType() { return OT_NONE; }
};

#endif // #ifndef OBJECT_HPP_INCLUDED
