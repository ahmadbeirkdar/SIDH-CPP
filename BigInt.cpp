//
// Created by Ahmad Beirkdar on 2020-10-30.
//

#include "BigInt.h"

BigInt::BigInt(unsigned long *mag, BigInt::Prime prime)
    : mag(mag), prime(prime),length(sizeof(mag)/mag[0])
{

}
