//
// Created by Ahmad Beirkdar on 2020-10-30.
//

#include "BigInt.h"

//static const unsigned long* P434_mag = BigInt::construct_prime(BigInt::Prime::P434);

BigInt::BigInt(unsigned long *mag, BigInt::Prime prime)
    : mag(mag), prime(prime),length(sizeof(mag)/mag[0])
{

}

//constexpr std::array<unsigned long,Ceil(434/machine_word)>  BigInt::construct_prime_P434() {
//    switch (machine_word) {
//        case 64:
//            std::array<unsigned long,Ceil(434/machine_word)> temp = {0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF,0xFDC1767AE2FFFFFF,0x7BC65C783158AEA3,0x6CFC5FD681C52056,0x0002341F27177344};
//            return temp;
//
//
//    }
//}
