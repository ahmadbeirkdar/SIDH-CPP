//
// Created by Ahmad Beirkdar on 2020-10-30.
//

#include "BigInt.h"

//static const unsigned long* P434_mag = BigInt::construct_prime(BigInt::Prime::P434);

BigInt::BigInt(unsigned long *mag, BigInt::Prime prime)
    : mag(mag), prime(prime),length(sizeof(mag)/mag[0])
{

}

void BigInt::ADDC(unsigned long &r, unsigned long &c_o, unsigned long a, unsigned long b, unsigned long c_i) {
    if(__builtin_uaddl_overflow(a,b,&r) || __builtin_uaddl_overflow(a+b,c_i,&r))
        c_o = 1;
    else{
        r = a + b + c_i;
        c_o = 0;
    }
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
