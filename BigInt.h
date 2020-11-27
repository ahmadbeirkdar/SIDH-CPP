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



    static constexpr auto P434_mag = BPrime::construct_prime<T,434>("0002341F271773446CFC5FD681C520567BC65C783158AEA3FDC1767AE2FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF").mag;

    // Testing P751 prime.
    static constexpr auto P751_mag = BPrime::construct_prime<T,751>("00006FE5D541F71C0E12909F97BADC668562B5045CB25748084E9867D6EBE876DA959B1A13F7CC76E3EC968549F878A8EEAFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF").mag;



};


#endif //SIDH_CPP_BIGINT_H
