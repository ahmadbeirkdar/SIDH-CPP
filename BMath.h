//
// Created by Ahmad Beirkdar on 2020-10-31.
//
#pragma once
#ifndef SIDH_CPP_BMATH_H
#define SIDH_CPP_BMATH_H

namespace BMath {

    inline constexpr void ADDC(unsigned long &r, unsigned long &c_o, unsigned long a, unsigned long b, unsigned long c_i){
        if(__builtin_uaddl_overflow(a,b,&r) || __builtin_uaddl_overflow(a+b,c_i,&r))
            c_o = 1;
        else{
            r = a + b + c_i;
            c_o = 0;
        }
    }

}

#endif //SIDH_CPP_BMATH_H
