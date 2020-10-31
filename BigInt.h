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

constexpr static const size_t machine_word = (int)sizeof(long)*CHAR_BIT;

constexpr unsigned long Ceil(double num) {
    auto inum = (unsigned long)num;

    return inum + (((num > 0 )) ? 1 : 0);
}


class BigInt {

public:
    enum Prime {P434};

    BigInt()=default;
    explicit BigInt(unsigned long *mag, BigInt::Prime prime = BigInt::Prime::P434);


//    static constexpr std::array<unsigned long,Ceil(434/machine_word)> construct_prime_P434();

private:
    unsigned long *mag;
    int length;
    Prime prime;



    static constexpr std::array<unsigned long,Ceil(434/machine_word)> P434_mag = [] {
        switch (machine_word) {
            case 64:{
                std::array<unsigned long, 7> temp = {0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF,
                                                     0xFFFFFFFFFFFFFFFF, 0xFDC1767AE2FFFFFF,
                                                     0x7BC65C783158AEA3, 0x6CFC5FD681C52056,
                                                     0x0002341F27177344};
#if __WORDSIZE==64
                return temp;
#endif
            }

            case 8:{
                std::array<unsigned long, Ceil(434 / 8)> temp = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
                                                                  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xE2,
                                                                  0x7A, 0x76, 0xC1, 0xFD, 0xA3, 0xAE, 0x58, 0x31, 0x78, 0x5C, 0xC6, 0x7B, 0x56, 0x20,
                                                                  0xC5, 0x81, 0xD6, 0x5F, 0xFC, 0x6C, 0x44, 0x73, 0x17, 0x27, 0x1F, 0x34, 0x02};
#if __WORDSIZE==8
                return temp;
#endif
            }



        }
    }();


};


#endif //SIDH_CPP_BIGINT_H
