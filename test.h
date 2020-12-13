//
// Created by Ahmad Beirkdar on 2020-12-02.
//
#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <cassert>
#include <gmp.h>
#include <gmpxx.h>
#include "BigInt.h"
#include "BMath.h"

void objectBenchmark(){
    std::vector<std::string> inputs;
    std::vector<std::string> outputs;

    std::ifstream file("../tests/add_inputs.txt");

    if(file.is_open()){
        std::string line;
        while(std::getline(file,line))
            inputs.push_back(line);
        file.close();
    }
    std::ifstream file2("../tests/add_result.txt");
    if(file2.is_open()){
        std::string line;
        while(std::getline(file2,line))
            outputs.push_back(line);
        file.close();
    }
    int i = 0;
    auto t1 = std::chrono::high_resolution_clock::now();
    auto t2 = std::chrono::high_resolution_clock::now();
    t1 = std::chrono::high_resolution_clock::now();
    for(auto &o : outputs){
        auto a = BigInt<u_int64_t>(inputs.at(i++));
        auto b = BigInt<u_int64_t>(inputs.at(i++));
        auto r = BigInt<u_int64_t>();
    }
    t2 = std::chrono::high_resolution_clock::now();
    auto time1 = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();

    std::cout << "BigInt constructor tested " << 3*outputs.size() << std::endl;


    i = 0;
    t1 = std::chrono::high_resolution_clock::now();
    for(auto &o : outputs){
        auto a = mpz_class(inputs.at(i++).substr(2),16);
        auto b = mpz_class(inputs.at(i++).substr(2),16);
        auto r = mpz_class();
    }
    t2 = std::chrono::high_resolution_clock::now();

    std::cout << "          This is " << std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count()/static_cast<double>(time1) << "x faster" << std::endl;
    std::cout << "          This took " << time1 << " ms and GMP took " << std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count() << " ms" << std::endl;

}

void addTests(){
    std::vector<std::string> inputs;
    std::vector<std::string> outputs;

    std::ifstream file("../tests/add_inputs.txt");

    if(file.is_open()){
        std::string line;
        while(std::getline(file,line))
            inputs.push_back(line);
        file.close();
    }
    std::ifstream file2("../tests/add_result.txt");
    if(file2.is_open()){
        std::string line;
        while(std::getline(file2,line))
            outputs.push_back(line);
        file.close();
    }
    int i = 0;
    auto t1 = std::chrono::high_resolution_clock::now();
    for(auto &o : outputs){
        auto a = BigInt<u_int64_t>(inputs.at(i++));
        auto b = BigInt<u_int64_t>(inputs.at(i++));
        auto r = BigInt<u_int64_t>();
        r = a + b;
        assert(o == r.to_std_string());
    }
    auto t2 = std::chrono::high_resolution_clock::now();

    std::cout << "Addition tests passed, tested " << outputs.size() << std::endl;

    auto time1 = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();

    std::for_each(outputs.begin(),outputs.end(),[](std::string &data){
        std::for_each(data.begin(), data.end(), [](char & c){
            c = ::tolower(c);
        });
    });

    i = 0;
    t1 = std::chrono::high_resolution_clock::now();
    for(auto &o : outputs){
        auto a = mpz_class(inputs.at(i++).substr(2),16);
        auto b = mpz_class(inputs.at(i++).substr(2),16);
        auto r = mpz_class();
        r = a + b;
        assert(o.substr(2) == r.get_str(16));
    }
    t2 = std::chrono::high_resolution_clock::now();

    std::cout << "          This is " << std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count()/static_cast<double>(time1) << "x faster" << std::endl;
    std::cout << "          This took " << time1 << " ms and GMP took " << std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count() << " ms" << std::endl;

}

void customTests(){
    std::cout << "Hello, World!" << std::endl;

    // Tests Below
    unsigned int r;
    unsigned int c_o;
    BMath::ADDC<unsigned int>(r,c_o,UINT_MAX,12,0);
    std::cout << r << " " << c_o <<std::endl;

    unsigned short c1;
    unsigned short c_o_o;
    BMath::ADDC<unsigned short>(c1,c_o_o,65535,65535,0);
    std::cout << c1 << " " << c_o_o <<std::endl;

    std::cout << sizeof(unsigned long) << std::endl;

//    std::cout << BigInt<unsigned int>::P434_mag

    std::cout << "P434 mag in as unsigned long 'words': " << std::endl;
    constexpr auto temp = BigInt<unsigned long>::P434_mag;
    for(auto i : temp)
        std::cout << i << std::endl;

    std::cout << "P434 mag in as unsigned int 'words': " << std::endl;
    constexpr auto temp1 = BigInt<unsigned int>::P434_mag;
    for(auto i : temp1)
        std::cout << i << std::endl;

//    static_assert(temp.at(0) == 18446744073709551615,"Is @ compile time" );
    unsigned short b[3] = {1,2,3};
    auto a = BigInt<unsigned short>(b);

    std::cout << "c = 0xFFFF986709860876AAEEFF as BigInt, mag in unsigned short(16bits): " << std::endl;
    auto c = BigInt<unsigned short>("0xFFFF986709860876AAEEFF");
    for(auto i = 0; i < c.length; i++)
        std::cout << c.mag[i] << std::endl;


    std::cout << "\nSchoolbook addition test" << std::endl;
    auto a1 = BigInt<unsigned short>("0xFFFF986709860876AAEEFF");
    auto b1 = BigInt<unsigned short>("0xFFFF986709860876AAEEFF");
    auto r1 = BigInt<unsigned short>();
    a1.add_schoolbook(r1,a1,b1);
    std::cout << r1.to_std_string() << std::endl;
    assert(r1.to_std_string() == "0x1FFFF30CE130C10ED55DDFE");

    auto a2 = BigInt<unsigned short>("0x169b7d3ca093c49cf7aa56ff7eab415da876290f11d96f95f90b08aa8681a8be24498eacc6c404396a532");
    auto b2 = BigInt<unsigned short>("0x13b31781aac37da039fbe8fcfc58b29f727a93342cd758a83b069636287ce74ee10c13a90a20e5278f0e4");
    auto r2 = BigInt<unsigned short>();
    a2.add_schoolbook(r2,a2,b2);
    std::cout << r2.to_std_string() << std::endl;
    assert(r2.to_std_string() == "0x2A4E94BE4B57423D31A63FFC7B03F3FD1AF0BC433EB0C83E34119EE0AEFE900D0555A255D0E4E960F9616");

    auto a3 = BigInt<unsigned short>("0x169b7d3ca093c49cf7aa56ff7eab415da876290f11d96f95f90b08aa8681a8be24498eacc6c404396a532");
    auto b3 = BigInt<unsigned short>("0x13b31781aac37da039fbe8fcfc58b29f727a93342cd758a83b069636287ce74ee1");
    auto r3 = BigInt<unsigned short>();
    r3 = a3 + b3;
    std::cout << r3.to_std_string() << std::endl;
    assert(r3.to_std_string() == "0x169B7D3CA093C49CF7AB9230F6C5ED958279C8CDA1A9352123023053B9C47633AECD3F162A268C07DF413");
}
