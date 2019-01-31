#ifndef INHERITANCE_H
#define INHERITANCE_H
#include <cereal/types/base_class.hpp>
struct BaseData
{
    int x;
    template<class Archive>
    void serialize(Archive& ar)
    {
        ar(x);
    }
};

struct Derived : public BaseData
{
    int y;
    template<class Archive>
    void serialize(Archive& ar)
    {
        ar(cereal::base_class<BaseData>(this),y);
    }
};


struct Base
{
  int x;
  // Note the non-member serialize - trying to call serialize
  // from a derived class wouldn't work
};

template <class Archive>
void serialize( Archive & ar, Base & b )
{ ar( b.x ); }

struct Left : virtual Base
{
  int l;

  template <class Archive>
  void serialize( Archive & ar )
  {
    ar( cereal::virtual_base_class<Base>( this ), l );
  }
};

struct Right : virtual Base
{
  int r;

  template <class Archive>
  void serialize( Archive & ar )
  {
    ar( cereal::virtual_base_class<Base>( this ), r );
  }
};

struct Derived : virtual Left, virtual Right
{
  int y;
  template <class Archive>
  void serialize( Archive & ar )
  {
    // Since we've used virtual inheritance and virtual_base_class,
    // cereal will ensure that only one copy of each base class
    // is serialized
    ar( cereal::virtual_base_class<Left>( this ),
        cereal::virtual_base_class<Right>( this ),
        y );
  }
};

#endif // INHERITANCE_H
