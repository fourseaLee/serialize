#ifndef COMPATIBILITY_BOOST_H
#define COMPATIBILITY_BOOST_H
#include <boost/archive/binary_oarchive.hpp>
#include <cereal/archives/binary.hpp>
#include <fstream>

class ComBoostData
{
public:
    ComBoostData() = default;
    int a;
    int b;

private:
    friend class cereal::access; // befriend the cereal version of access
    friend class boost::serialization::access;

    // cereal supports class versioning although it is considered
    // optional in cereal.
    //
    // Note that the second parameter is changed from const unsigned int to
    // const std::uint32_t
    template <class Archive>
    void save( Archive & ar, std::uint32_t const version ) const
    {
        // cereal supports Boost style syntax until you can change it
        ar << a << b;
    }

    template <class Archive>
    void load( Archive & ar, std::uint32_t const version )
    {
        ar >> a;
        ar >> b;
    }

    // cereal will figure out you've used split member load/save automatically
    BOOST_SERIALIZATION_SPLIT_MEMBER()
};
CEREAL_SPECIALIZE_FOR_ALL_ARCHIVES( ComBoostData, cereal::specialization::member_load_save )

BOOST_CLASS_VERSION(ComBoostData, 1);
CEREAL_CLASS_VERSION(ComBoostData, 1);

struct DataType
{
  int x;
  double y;
  ComBoostData s;

  template <class Archive>
  void serialize( Archive & ar, std::uint32_t const version )
  {
    ar & x & y; // the & operator is valid in cereal but not the preferred interface
    ar & s;
  }
};

void testCompatibility()
{
    std::ofstream os("out.bin", std::ios::binary);

  // using boost
  {
    boost::archive::binary_oarchive ar(os);
    DataType m;
    ar << m; // cereal supports Boost style serialization syntax until you can fully transition
  }

  // using cereal
  {
    cereal::BinaryOutputArchive ar(os);
    DataType m;
    ar << m;
  }
}



#endif // COMPATIBILITY_BOOST_H
