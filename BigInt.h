//
// Created by Ahmad Beirkdar on 2020-10-30.
//

#ifndef SIDH_CPP_BIGINT_H
#define SIDH_CPP_BIGINT_H


#include <array>
#include <string>
#include "BMath.h"
#include "BPrime.h"



template <typename T>
class BigInt {

public:
    enum Prime {P434};

    BigInt()=default;
    explicit BigInt(T *mag, BigInt::Prime prime = BigInt::Prime::P434);
    void add_schoolbook(BigInt& r,BigInt& a, BigInt &c);


public:
    unsigned long *mag;
    int length;
    Prime prime;



    static constexpr auto P434_mag = BPrime::construct_P434<T>().mag;

    // Testing P751 prime.
    static constexpr auto P751_mag = BPrime::construct_P751<T>().mag;


};


#endif //SIDH_CPP_BIGINT_H
