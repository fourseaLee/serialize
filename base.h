#ifndef BASE_H
#define BASE_H
#include <cereal/access.hpp>
#include <cereal/cereal.hpp>
#include <cereal/archives/portable_binary.hpp>
#include <cereal/archives/adapters.hpp>
#include <cereal/archives/binary.hpp>
#include <cereal/types/string.hpp>
#include<cereal/types/map.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/archives/xml.hpp>
#include <sstream>
#include <iostream>
#include <ostream>
#include <boost/algorithm/hex.hpp>
struct BaseData
{
    int x;
    std::string data;
    template<class Archive>
    void serialize(Archive& archive)
    {
        archive(x);
        archive(data);
    }
};


void testBaseData()
{

    std::stringstream ss;
    std::string hex_data;
    std::string bin_data;

    {
        cereal::BinaryOutputArchive oarchive(ss); // Create an output archive

        BaseData m1, m2, m3;
        m1.x = 1;
        m1.data = "data1";
        m2.x = 2;
        m2.data = "data2";
        m3.x = 4;
        m3.data = "data4";


        oarchive(m1, m2, m3); // Write the data to the archive
        bin_data = ss.str();
        boost::algorithm::hex(bin_data,std::back_inserter(hex_data));
        std::cout << "size pre: " << ss.str().capacity() << std::endl;
        ss.clear();
        std::cout << "size after: " << ss.str().capacity() << std::endl;
    } // archive goes out of scope, ensuring all contents are flushed

    {
        std::string unhex;
        boost::algorithm::unhex(hex_data, std::back_inserter(unhex));
        cereal::BinaryInputArchive iarchive(ss); // Create an input archive
        //ss << unhex;
        ss << bin_data;
        ss.clear();

        BaseData m11, m21, m31,m41;
        iarchive(m11, m21); // Read the data from the archive
        iarchive(m31);
        iarchive(m41);
        std::cout << "m1: " << m11.x <<"  " << m11.data << std::endl;

        std::cout << "m2: " << m21.x <<"  " << m21.data << std::endl;

        std::cout << "m3: " << m31.x <<"  " << m31.data << std::endl;

        std::cout << "m4: " << m41.x << "  " << m41.data << std::endl;
    }
}

class  Stuff
{
public:
    Stuff() =default;

    void fillData(std::map<std::string,std::vector<double>> data)
    {
        data_ = data;
    }
private:

    friend class cereal::access;

    template<class Archive>

    void serialize( Archive & ar )
    {
        ar( data_ );
    }
public:
    std::map<std::string,std::vector<double>> data_;
};

void testStuff()
{

    std::stringstream ss;
    std::string hex_data;
    std::string bin_data;

    {
        cereal::BinaryOutputArchive oarchive(ss); // Create an output archive

        std::map<std::string,std::vector<double>> data;
        std::vector<double> vect_data;
        vect_data.push_back(12.1254);
        data["test"] = vect_data;

        Stuff  tuff;
        tuff.fillData(data);

        oarchive(tuff); // Write the data to the archive
        bin_data = ss.str();
        boost::algorithm::hex(bin_data,std::back_inserter(hex_data));
        std::cout << "size pre: " << ss.str().capacity() << std::endl;
        ss.clear();
        std::cout << "size after: " << ss.str().capacity() << std::endl;
    } // archive goes out of scope, ensuring all contents are flushed

    {
        std::string unhex;
        boost::algorithm::unhex(hex_data, std::back_inserter(unhex));
        cereal::BinaryInputArchive iarchive(ss); // Create an input archive
        //ss << unhex;
        ss << bin_data;
        ss.clear();

        Stuff tuff;

        iarchive(tuff); // Read the data from the archive
        std::cout << "stuff data: " << std::endl;
        std::cout << tuff.data_["test"].at(0) << std::endl;

    }
}


#endif // BASE_H
