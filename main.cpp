#include<cereal/archives/portable_binary.hpp>
#include<cereal/types/string.hpp>
#include <iostream>
#include <ostream>
#include <boost/algorithm/hex.hpp>
#include "base.h"
/*


struct MyClass
{
    int x, y, z;
    std::string data;

    // 此函数告诉Cereal那些类需要序列化
    template<class Archive>
    void serialize(Archive & archive)
    {
        archive( x, y, z); //需要进行存储的变量
        archive(data);
    }
};

struct SonClass :public MyClass
{
    std::string son_data;

    template<class Archive>
    void serialize(Archive & archive)
    {
        archive( cereal::base_class<MyClass>(this),son_data);
    }

};
int main(int argc, char *argv[])
{

    std::stringstream ss; // string stream
    std::string data ;
    std::string hex_data;
    {
        cereal::PortableBinaryOutputArchive oarchive(ss); //创建一个二进制序列化存储类

        MyClass m1, m2, m3;
        std::string data1 = "data1";
        m1.x = 1;
        m1.y = 1;
        m1.z = 1;
        m1.data = data1;

        std::string data2 = "data2";
        m2.x = 2;
        m2.y = 2;
        m2.z = 2;
        m2.data = data2;

        std::string data3 = "data3";
        m3.x = 3;
        m3.y = 3;
        m3.z = 3;
        m3.data = data3;

       MyClass* m4 = new SonClass();
       m4->data = "data45";
       m4->x = 5;
       m4->y = 5;
       m4->z = 5;
       ((SonClass*)m4)->son_data = "son data";
       std::cout << m4->x << " : " << m4->y << " : "<< m4->z << " : " << m4->data << " : "  <<((SonClass*)m4)->son_data<< std::endl;

       SonClass* m41 = (SonClass*)m4;

        //oarchive(m1, m2, m3); //将三个数据写到存储类中
        oarchive(*m41);

        data = ss.str();

        std::cout  << std::endl;

        std::string symbol;
        boost::algorithm::hex(data, std::back_inserter(symbol));

        std::cout << "hex: " << symbol << std::endl;
        hex_data = symbol;

        std::cout << std::endl;
        ss.clear();
        delete m4;


    } // 存储类使用完毕，刷新内存

    {
         std::stringstream ss1;
         std::string unhex;
         boost::algorithm::unhex(hex_data, std::back_inserter(unhex));

         ss1 << unhex;
        cereal::PortableBinaryInputArchive iarchive(ss1); // 读取类
        MyClass m1, m2, m3;
        std::shared_ptr<MyClass> m41 = std::make_shared<SonClass>();

      //  iarchive(m1, m2, m3); // 从存储中读取数据
        iarchive(*m41);
        std::cout << m1.x << " : " << m1.y << " : "<< m1.z << " : " << m1.data << std::endl;
        std::cout << m2.x << " : " << m2.y << " : "<< m2.z << " : " << m2.data << std::endl;
        std::cout << m3.x << " : " << m3.y << " : "<< m3.z << " : " << m3.data << std::endl;
        std::cout << m41->x << " : " << m41->y << " : "<< m41->z << " : " << m41->data << std::endl;
    }

    return 0;
}
*/


int main()
{

    testBaseData();
    testStuff();
    return 0;
}
