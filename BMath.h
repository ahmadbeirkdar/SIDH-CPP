//
// Created by Ahmad Beirkdar on 2020-10-31.
//
#pragma once
#ifndef SIDH_CPP_BMATH_H
#define SIDH_CPP_BMATH_H
#include <climits>
#include <iostream>

constexpr unsigned long Ceil(double num) {
    auto inum = (unsigned long)num;

    return inum + (((num > 0 )) ? 1 : 0);
}


namespace BMath {
    /**
     * Add with carry function
     * @param r - Result
     * @param c_o - Carry out
     * @param a - Addend one
     * @param b - Addend two
     * @param c_i - Carry in
     * @return - void
     */
    template <typename T>
    inline constexpr void ADDC(T &r, T &c_o, T a, T b, T c_i){
        if(__builtin_add_overflow(a,b,&r) || __builtin_add_overflow(a+b,c_i,&r)){
            __builtin_add_overflow(a+b,c_i,&r);
            c_o = 1;
        }
        else{
            r = a + b + c_i;
            c_o = 0;
        }
    }

    /**
     * Sub with carry function
     * @param r - Result
     * @param c_o - Carry out
     * @param a - Addend one
     * @param b - Addend two
     * @param c_i - Carry in
     * @return - void
     */
    template <typename T>
    inline constexpr void SUBC(T &r, T &c_o, T a, T b, T c_i){
        if(__builtin_sub_overflow(a,b,&r) || __builtin_sub_overflow(a-b,c_i,&r)){
            __builtin_sub_overflow(a-b,c_i,&r);
            c_o = 1;
        }
        else{
            r = a - b - c_i;
            c_o = 0;
        }
    }

    template <typename T>
    inline constexpr void MULC(T &r, T &c_o, T a, T b, T c_i){
        T bh, temp;
        T albl, albh, ahbl, ahbh, carry;
        T mask_low = std::numeric_limits<T>::max() >> (sizeof(T)*4);
        T mask_high = std::numeric_limits<T>::max() << (sizeof(T)*4);

        albl = (a & mask_low)*(b & mask_low);
        albh = (a & mask_low)*(b >> (sizeof(T) * 4));
        ahbl = (a >> (sizeof(T) * 4))*(b & mask_low);
        ahbh = (a >> (sizeof(T) * 4))*(b >> (sizeof(T) * 4));
        r = albl & mask_low;

        temp = (albl >> (sizeof(T) * 4)) + (ahbl & mask_low) + (albh & mask_low);
        carry = temp >> (sizeof(T) * 4);
        r ^= temp << (sizeof(T) * 4);

        temp = (ahbl >> (sizeof(T) * 4)) + (albh >> (sizeof(T) * 4)) + (ahbh & mask_low) + carry;
        c_o = temp & mask_low;
        carry = temp & mask_high;
        c_o ^= (ahbh & mask_high) + carry;

        ADDC<T>(r,temp,r,c_i,0);
        c_o += temp;
    }

    static constexpr long hextable[] = {
            -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
            -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
            -1,-1, 0,1,2,3,4,5,6,7,8,9,-1,-1,-1,-1,-1,-1,-1,10,11,12,13,14,15,-1,
            -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
            -1,-1,10,11,12,13,14,15,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
            -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
            -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
            -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
            -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
            -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
            -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1
    };

}

#endif //SIDH_CPP_BMATH_H
