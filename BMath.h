//
// Created by Ahmad Beirkdar on 2020-10-31.
//
#pragma once
#ifndef SIDH_CPP_BMATH_H
#define SIDH_CPP_BMATH_H
#include <climits>
#include <iostream>

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
    inline constexpr void ADDC(unsigned long &r, unsigned long &c_o, unsigned long a, unsigned long b, unsigned long c_i){
        if(__builtin_uaddl_overflow(a,b,&r) || __builtin_uaddl_overflow(a+b,c_i,&r))
            c_o = 1;
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
    inline constexpr void SUBC(unsigned long &r, unsigned long &c_o, unsigned long a, unsigned long b, unsigned long c_i){
        if(__builtin_usubl_overflow(a,b,&r)){
//            unsigned long temp = a + (ULONG_MAX - b) + 1;
            __builtin_usubl_overflow(r,c_i,&r);
            c_o = 1;
        }
        else if(__builtin_usubl_overflow(a-b,c_i,&r))
            c_o = 1;
        else{
            r = a - b - c_i;
            c_o = 0;
        }
    }

}

#endif //SIDH_CPP_BMATH_H
