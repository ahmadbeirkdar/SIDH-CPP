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
    template <typename T, std::size_t N>
    struct construct_prime{
        constexpr explicit construct_prime(std::string_view Prime) : mag() {
            int firstL = (Prime.length() - 2)%(2*sizeof(T)) == 0 ? 2*sizeof(T) :  (Prime.length() - 2)%(2*sizeof(T));
            auto it = Prime.begin();
            std::advance(it,2); // Assuming the base 16 number as a string given starts 0x

            std::for_each(mag.rbegin(),mag.rend(),[&it,&Prime,&firstL](T &i) {
                int j = 0;
                T r = 0;

                while (it != Prime.end() && r >= 0 && j < firstL) {
                    r = (r << 4) | BPrime::hextable[*it++];
                    j++;
                }

                i = r;
                firstL = 2*sizeof(T);
            });
        }

        // Ceil(N/(4*sizeof(T))) - Calculate size of PN prime array - as (N bits)/(size of T * 8 bits)
        std::array<T,Ceil(N/(8*sizeof(T)))> mag;
    };


}
#endif //SIDH_CPP_BPRIME_H
