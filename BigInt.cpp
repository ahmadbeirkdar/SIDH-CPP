//
// Created by Ahmad Beirkdar on 2020-10-30.
//

#include "BigInt.h"

static const unsigned long* P343_mag = BigInt::construct_prime(BigInt::Prime::P343);

BigInt::BigInt(unsigned long *mag, BigInt::Prime prime)
    : mag(mag), prime(prime),length(sizeof(mag)/mag[0])
{

}

const unsigned long* BigInt::construct_prime(BigInt::Prime prime) {
    switch (prime) {

        case P343:
            switch (machine_word) {
                case 64:
                    const static unsigned long temp[7] = {0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF,0xFDC1767AE2FFFFFF,0x7BC65C783158AEA3,0x6CFC5FD681C52056,0x0002341F27177344};
                    return temp;
                case 32:
                    return nullptr;

            }
    }
}
