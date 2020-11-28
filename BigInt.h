//
// Created by Ahmad Beirkdar on 2020-10-30.
//

#ifndef SIDH_CPP_BIGINT_H
#define SIDH_CPP_BIGINT_H


#include <array>
#include <string>
#include "BMath.h"
#include "BPrime.h"



template <typename T>
class BigInt {

public:
    enum Prime {P434};

    BigInt()=default;
    constexpr explicit BigInt(T *mag, BigInt::Prime prime = BigInt::Prime::P434)
            : mag(mag), prime(prime),length(sizeof(mag)/mag[0]) {};

    explicit BigInt(std::string_view num, BigInt::Prime prime = BigInt::Prime::P434)
    : prime(prime), length(Ceil((num.length() - 2)/(2*sizeof(T))))
    {
            if(num.substr(0,2) != "0x")
                throw std::runtime_error("BigInt: Invalid number, number must be in base 16 and starting with 0x");
            mag = new T[length];
            auto it = num.begin() +2;
            for(auto i = 0; i < length; i++){
                T ret = 0;
                int j = 0;
                while (it != num.end() && ret >= 0 && j < 2 * sizeof(T)) {
                    ret = (ret << 4) | BPrime::hextable[*it++]; j++;
                }
                mag[i] = ret;
            }
    };

    void add_schoolbook(BigInt& r,BigInt& a, BigInt &b){
        if (a.prime != b.prime != r.prime)
            throw std::runtime_error("BigInt: To use the add_schoolbook method, both BigInts must have the same prime.");

        T c_i = 0;
        T c_o = 0;
        BigInt<T>* min = (a.length < b.length) ? &a : &b;
        BigInt<T>* max = (a.length < b.length) ? &b : &a;

        if(min->length == 0){
            r.length = max->length;
            r.mag = new T[r.length];
            for(auto i = 0; i < r.length; i++)
                r.mag[i] = max->mag[i];
            return;
        }

        r.length = max->length;
        r.mag = new T[max->length + 1];

        for(auto i = 0; i < min->length; i++){
            BMath::ADDC<T>(r.mag[i],c_o,min->mag[i],max->mag[i],c_i);
            c_i = c_o;
            std::cout << r.mag[i] << " "<< max->mag[i] << " " << min->mag[i] << std::endl;
        }
        for(auto i = min->length; i < max->length ; i++){
            BMath::ADDC<T>(r.mag[i],c_o,max->mag[i],0,c_i);
            c_i = c_o;
        }

        if(c_i == 1) {
            r.length++;
            BMath::ADDC<T>(r.mag[r.length-1],c_o,0,0,c_i);
        }

    };


public:
    T *mag;
    int length{};
    Prime prime;



    static constexpr auto P434_mag = BPrime::construct_prime<T,434>("0002341F271773446CFC5FD681C520567BC65C783158AEA3FDC1767AE2FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF").mag;

    // Testing P751 prime.
    static constexpr auto P751_mag = BPrime::construct_prime<T,751>("00006FE5D541F71C0E12909F97BADC668562B5045CB25748084E9867D6EBE876DA959B1A13F7CC76E3EC968549F878A8EEAFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF").mag;



};


#endif //SIDH_CPP_BIGINT_H
