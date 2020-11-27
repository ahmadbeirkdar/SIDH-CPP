//
// Created by Ahmad Beirkdar on 2020-11-27.
//

#ifndef SIDH_CPP_BPRIME_H
#define SIDH_CPP_BPRIME_H

#include <sstream>
#include "BMath.h"

namespace BPrime{
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

    template <typename T>
    struct construct_P434{
        constexpr construct_P434() : mag() {
            constexpr std::string_view P434 = "0002341F271773446CFC5FD681C520567BC65C783158AEA3FDC1767AE2FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF";
            auto it = P434.begin();
            std::for_each(mag.rbegin(),mag.rend(),[&it,&P434](T &i) {
                T ret = 0;
                int j = 0;
                while (it != P434.end() && ret >= 0 && j < 2 * sizeof(T)) {
                    ret = (ret << 4) | hextable[*it++]; j++;
                }
                i = ret;
            });
        }

        // Ceil(217/(4*sizeof(T))) - Calculate size of P434 prime array - as (434 bits)/(size of T * 8 bits)
        std::array<T,Ceil(217/(4*sizeof(T)))> mag;
    };


}
#endif //SIDH_CPP_BPRIME_H
