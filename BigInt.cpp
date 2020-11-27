//
// Created by Ahmad Beirkdar on 2020-10-30.
//

#include "BigInt.h"

//static const unsigned long* P434_mag = BigInt::construct_prime(BigInt::Prime::P434);
template<typename T>
BigInt<T>::BigInt(T *mag, BigInt::Prime prime)
    : mag(mag), prime(prime),length(sizeof(mag)/mag[0])
{

}
template<typename T>
void BigInt<T>::add_schoolbook(BigInt &r, BigInt &a, BigInt &c) {

}
