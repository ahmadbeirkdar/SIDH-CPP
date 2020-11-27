//
// Created by Ahmad Beirkdar on 2020-10-30.
//

#ifndef SIDH_CPP_BIGINT_H
#define SIDH_CPP_BIGINT_H


#include <cstdint>
#include <cstdio>
#include <climits>
#include <array>
#include <initializer_list>
#include <string>
#include <sstream>
#include "BMath.h"
#include "BPrime.h"

//constexpr static const size_t machine_word = (int)sizeof(long)*CHAR_BIT;



template <typename T>
class BigInt {

public:
    enum Prime {P434};

    BigInt()=default;
    explicit BigInt(T *mag, BigInt::Prime prime = BigInt::Prime::P434);
    void add_schoolbook(BigInt& r,BigInt& a, BigInt &c);


//    static constexpr std::array<unsigned long,Ceil(434/machine_word)> construct_prime_P434();

public:
    unsigned long *mag;
    int length;
    Prime prime;



    static constexpr auto P434_mag = BPrime::construct_P434<T>().mag;


};


#endif //SIDH_CPP_BIGINT_H
