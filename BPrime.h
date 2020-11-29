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
            auto it = Prime.rbegin();
            auto it2 = Prime.rbegin();
            bool flag = false;
            std::for_each(mag.begin(),mag.end(),[&it,&it2,&flag,&Prime](T &i) {
                T ret = 0;
                int j = 0;
                it = it2;
                while(it < Prime.rend() && j < (2*sizeof(T))){
                    if(flag || j > 0)
                        it++;
                    j++;
                }
                j = 2*sizeof(T) - std::distance(it2,it) - ((!flag) ? 1 : 0);
                if(it == Prime.rend()){
                    int k = 0;
                    while(it!=Prime.rbegin() && k != 1){
                        it--; k++; j++;
                    }
                }
                it2 = it;
                flag = true;
                while (it != Prime.rend() && ret >= 0 && j < 2 * sizeof(T)) {
                    ret = (ret << 4) | hextable[*it];it--; j++;
                }
                i = ret;
            });
        }

        // Ceil(N/(4*sizeof(T))) - Calculate size of PN prime array - as (N bits)/(size of T * 8 bits)
        std::array<T,Ceil(N/(8*sizeof(T)))> mag;
    };


}
#endif //SIDH_CPP_BPRIME_H
