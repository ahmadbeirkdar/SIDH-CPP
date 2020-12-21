//
// Created by Ahmad Beirkdar on 2020-10-30.
//

#ifndef SIDH_CPP_BIGINT_H
#define SIDH_CPP_BIGINT_H


#include <array>
#include <string>
#include "BMath.h"
#include "BPrime.h"
#include "DTS.h"
#include <cmath>

template <typename T>
class BigInt {

    static_assert(std::is_unsigned<T>::value, "BigInt template parameter must be unsigned.");
    static_assert(std::is_integral<T>::value, "BigInt template parameter must be integral.");

public:
    enum Prime {P434};

    BigInt()=default;
    constexpr explicit BigInt(T *mag, BigInt::Prime prime = BigInt::Prime::P434)
            : mag(mag), prime(prime),length(sizeof(mag)/mag[0]) {};

    explicit BigInt(std::string_view num, BigInt::Prime prime = BigInt::Prime::P434)
    : prime(prime), length(std::ceil((num.length() - 2.0)/(2.0*sizeof(T))))
    {
//            if(num.substr(0,2) != "0x")
//                throw std::runtime_error("BigInt: Invalid number, number must be in base 16 and starting with 0x");
//            mag = std::make_unique_for_overwrite<T[]>(length);
            mag = new T[length];
//            mag = std::make_unique<T[]>(length);
            int firstL = (num.length() - 2)%(2*sizeof(T)) == 0 ? 2*sizeof(T) :  (num.length() - 2)%(2*sizeof(T));
            auto it = num.begin();
            std::advance(it,2); // Assuming the base 16 number as a string given starts 0x
            int j;
            T r;
            for(auto i = length - 1; i >= 0 ;i--){
                r = 0;
                j = 0;

                while (it != num.end() && r >= 0 && j < firstL) {
                    r = (r << 4) | BMath::hextable[*it++];
                    j++;
                }

                mag[i] = r;
                firstL = 2*sizeof(T);
            }
    };

    void add_schoolbook(BigInt& r,BigInt& a, BigInt &b){
        // No need to check prime, because it is not meant to be for modular arithmetic, rather just a test implementation of
//        if (a.prime != b.prime != r.prime)
//            throw std::runtime_error("BigInt: To use the add_schoolbook method, both BigInts must have the same prime.");

        T c_i = 0;
        T c_o = 0;
        BigInt<T>* min = (a.length < b.length) ? &a : &b;
        BigInt<T>* max = (a.length < b.length) ? &b : &a;

        if(min->length == 0){
            r.length = max->length;
//            r.mag = DTS::make_unique_for_overwrite<T[]>(r.length);
            r.mag = new T[r.length];
            for(auto i = 0; i < r.length; i++)
                r.mag[i] = max->mag[i];
            return;
        }

        r.length = max->length;
//        r.mag = DTS::make_unique_for_overwrite<T[]>(r.length + 1);
        r.mag = new T[r.length + 1];
        for(auto i = 0; i < min->length; i++){
            BMath::ADDC<T>(r.mag[i],c_o,min->mag[i],max->mag[i],c_i);
//            std::cout << r.mag[i] << " "<< max->mag[i] << " " << min->mag[i] << ((c_o == 1) ? " CARRY OUT": "  ") << ((c_i == 1) ? " CARRY IN": "  ") << std::endl; // DEBUGGING
            c_i = c_o;
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

    // Dumb and enfficent meant for debugging, will be done better
    std::string to_std_string(){
        std::stringstream ss;
        for(auto i = length - 1; i >= 0 ; i--){
            std::stringstream temp;
            std::string zeros;
            temp << std::hex << +mag[i]; // Integral promotion in case it is a u8
            while(temp.str().length() + zeros.length() != 2*sizeof(T) && i != length - 1)
                zeros += '0';
            ss << zeros + temp.str();
        }
        std::string temp = ss.str();
        std::transform(temp.begin(),temp.end(),temp.begin(),::toupper);

        auto it = temp.begin();
        while(it != temp.end()){
            if(*it == '0')
                temp.erase(it);
            else
                break;
        }

        return "0x" + temp;
    }

    BigInt<T> operator+(BigInt<T> &b){
        BigInt<T> r;
        add_schoolbook(r,*this,b);
        return r;
    }

    BigInt<T> operator>(BigInt<T> &b){
        if(this->length != b.length)
            return this->length > b.length;

        for(auto i = length - 1; i >= 0; i--)
            if(this->mag[i] != b->mag[i])
                return this->mag[i] > b->mag[i];

    }


public:
    // Removed usage of unique pointer c style arrays, because there is an overhead when accessing elements even when std::make_unique_for_overwrite was implemented to take control of the intilization process
    // It seems safe enough, at this point to use c style arrays, when at this point, everything is within bounds of the array no matter what.
//    std::unique_ptr<T[]> mag;
    T *mag;
    int length{};
    Prime prime = BigInt::Prime::P434;



    static constexpr auto P434_mag = BPrime::construct_prime<T,434>("0x2341F271773446CFC5FD681C520567BC65C783158AEA3FDC1767AE2FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF").mag;

    // Testing P751 prime.
    static constexpr auto P751_mag = BPrime::construct_prime<T,751>("0x6FE5D541F71C0E12909F97BADC668562B5045CB25748084E9867D6EBE876DA959B1A13F7CC76E3EC968549F878A8EEAFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF").mag;



};


#endif //SIDH_CPP_BIGINT_H
