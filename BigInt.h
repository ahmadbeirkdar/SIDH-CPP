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

class BigInt {

public:
    enum Prime {P343};

    BigInt()=default;
    explicit BigInt(unsigned long *mag, BigInt::Prime prime = BigInt::Prime::P343);


    static const unsigned long* construct_prime(BigInt::Prime prime);

private:
    unsigned long *mag;
    int length;
    Prime prime;



    constexpr static const size_t machine_word = (int)sizeof(long)*CHAR_BIT;

//    static constexpr unsigned long *P343_mag;


};


#endif //SIDH_CPP_BIGINT_H
