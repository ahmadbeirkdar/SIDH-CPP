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
concept is_u_int = std::is_unsigned<T>::value && std::is_integral<T>::value;

template <is_u_int T>
class BigInt {
public:
    enum Prime {P434};

    BigInt()=default;
    constexpr explicit BigInt(T *mag, BigInt::Prime prime = BigInt::Prime::P434)
            : mag(mag), prime(prime),length(sizeof(mag)/mag[0]) {};

    constexpr explicit BigInt(std::string_view num, BigInt::Prime prime = BigInt::Prime::P434)
            : prime(prime) {
        positive = (num.at(0) != '-');
        int firstL = (num.length() - (positive ? 2 : 3))%(2*sizeof(T)) == 0 ? 2*sizeof(T) :  (num.length() - (positive ? 2 : 3))%(2*sizeof(T));
        length = positive ? std::ceil((num.length() - 2.0)/(2.0*sizeof(T))) : std::ceil((num.length() - 3.0)/(2.0*sizeof(T)));
        mag = DTS::make_unique_for_overwrite<T[]>(length);

        auto j = positive ? 2 : 3;
        for(auto i = length - 1; i >= 0 ;i--){
            mag[i] = BMath::FromHex<T>(num.substr(j,firstL));
            j += firstL;
            firstL = 2*sizeof(T);
        }
    };

    constexpr auto add_schoolbook(BigInt& r,BigInt& a, BigInt &b, bool skipChecks = false) -> void {
        // No need to check prime, because it is not meant to be for modular arithmetic, rather just a test implementation of
//        if (a.prime != b.prime != r.prime)
//            throw std::runtime_error("BigInt: To use the add_schoolbook method, both BigInts must have the same prime.");

        if((!skipChecks) && (!a.positive && b.positive)){
            sub_schoolbook(r,b,a,true);
            return;
        }
        else if((!skipChecks) && (a.positive && !b.positive)){
            sub_schoolbook(r,a,b,true);
            return;
        }
        else if(!skipChecks && !a.positive && !b.positive)
            r.positive = false;
        else if(!skipChecks)
            r.positive = true;

        T c_i = 0;
        T c_o = 0;
        BigInt<T>* min = (a.length < b.length) ? &a : &b;
        BigInt<T>* max = (a.length < b.length) ? &b : &a;

        if(min->length == 0){
            r.length = max->length;
            r.mag = DTS::make_unique_for_overwrite<T[]>(r.length);
            r.positive = min->positive;
            for(auto i = 0; i < r.length; i++)
                r.mag[i] = max->mag[i];
            return;
        }

        r.length = max->length;
        r.mag = DTS::make_unique_for_overwrite<T[]>(r.length + 1);
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

    constexpr auto sub_schoolbook(BigInt& r,BigInt& a, BigInt &b,bool skipChecks = false) -> void {
        BigInt<T>* x;
        BigInt<T>* y;
        if((!skipChecks) && !a.positive && b.positive){
            r.positive = false;
            add_schoolbook(r,a,b,true);
            return;
        }
        else if((!skipChecks) && a.positive && !b.positive){
            add_schoolbook(r,a,b,true);
            return;
        }
        else if((!skipChecks) && !a.positive && !b.positive){
            x = &b;y = &a;
        }
        else{
            x = &a;y = &b;
        }

        if(b > a || (skipChecks && greaterThan(b,a,true))){
            r.positive = false;
            std::swap(x,y);
        }

        T c_i = 0;
        T c_o = 0;
        size_t minL = (x->length < y->length) ? x->length : y->length;
        size_t maxL = (x->length > y->length) ? x->length : y->length;
        r.length = maxL;
        r.mag = DTS::make_unique_for_overwrite<T[]>(r.length);

        for(auto i = 0; i < minL; i++){
            BMath::SUBC<T>(r.mag[i],c_o,x->mag[i],y->mag[i],c_i);
//            std::cout << +r.mag[i] << " "<< +x->mag[i] << " " << +y->mag[i] << ((c_o == 1) ? " CARRY OUT": "  ") << ((c_i == 1) ? " CARRY IN": "  ") << std::endl; // DEBUGGING
            c_i = c_o;
        }
        for(auto i = minL; i < maxL ; i++){
            BMath::SUBC<T>(r.mag[i],c_o,((x->length == maxL) ? x->mag[i] : 0),((y->length == maxL) ? y->mag[i] : 0),c_i);
            c_i = c_o;
        }

        if(c_i == 1)
            r.positive = false;


    };

    constexpr auto multiply(BigInt& r,const BigInt& a,const BigInt &b) -> void {
        if(a.length == 0 || b.length == 0){
            r.length = 0;
            r.mag = DTS::make_unique_for_overwrite<T[]>(1);
            r.mag[0] = 0;
            return;
        }

        T c_o = 0;
        T c_i = 0;
        T ans = 0;
        T t1 = 0;
        T t2 = 0;

        r.length = a.length + b.length;
        r.mag = DTS::make_unique_for_overwrite<T[]>(r.length + 1);
        r.positive = (a.positive && b.positive) || (!a.positive && !b.positive);

        for(auto i = 0; i < b.length; i++){
            BMath::MULC<T>(ans,c_o,a.mag[0],b.mag[i],c_i);
            r.mag[i] = ans;
            c_i = c_o;
        }
        r.mag[b.length] = c_i;

        for(auto i = 1; i < a.length; i++){
            c_i = 0;
            for(auto j = 0; j < b.length; j++){
                BMath::MULC<T>(ans,c_o,a.mag[i],b.mag[j],c_i);
                t1 = c_o;
                BMath::ADDC<T>(r.mag[i+j],c_o,r.mag[i+j],ans,0);
                t2 = c_o;
                BMath::ADDC<T>(c_i,c_o,t1,t2,0);
            }
            r.mag[i+b.length] = c_i;
        }

    }

//    void kartsuba(BigInt& r,const BigInt& a,const BigInt &b){
//        size_t m = std::floor(std::min(a.length,b.length)/2.0);
//
//    }

    constexpr auto greaterThan(BigInt<T> &a,BigInt<T> &b, bool magOnly = false) -> bool {
        if(a.length != b.length && (magOnly || (a.positive && b.positive)))
            return a.length > b.length;
        else if(!magOnly && a.positive && !b.positive)
            return true;
        else if(!magOnly && !a.positive && b.positive)
            return false;
        else if(!magOnly && !a.positive && !b.positive && a.length != b.length)
            return a.length < b.length;
        else if(!magOnly && !a.positive && !b.positive && a.length == b.length){
            for(auto i = length - 1; i >= 0; i--)
                if(a.mag[i] != b.mag[i])
                    return a.mag[i] < b.mag[i];
        }
        else {
            for(auto i = length - 1; i >= 0; i--)
                if(a.mag[i] != b.mag[i])
                    return a.mag[i] > b.mag[i];
        }

        return false;
    }

    // Dumb and enfficent meant for debugging, will be done better
    auto to_std_string() -> std::string {
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

        return (this->positive ? "0x" : "-0x") + temp;
    }

    constexpr auto operator+(BigInt<T> &b) -> BigInt<T>{
        BigInt<T> r;
        add_schoolbook(r,*this,b);
        return r;
    }

    constexpr auto operator-(BigInt<T> &b) -> BigInt<T>{
        BigInt<T> r;
        sub_schoolbook(r,*this,b);
        return r;
    }
    constexpr auto operator*(BigInt<T> &b) -> BigInt<T>{
        BigInt<T> r;
        multiply(r,*this,b);
        return r;
    }

    constexpr auto operator>(BigInt<T> &b) -> bool {
        return greaterThan(*this,b);
    }


public:
    std::unique_ptr<T[]> mag;
    bool positive = true;
    ssize_t length = 0;
    Prime prime = BigInt::Prime::P434;



    static constexpr auto P434_mag = BPrime::construct_prime<T,434>("0x2341F271773446CFC5FD681C520567BC65C783158AEA3FDC1767AE2FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF").mag;
    // Testing P751 prime.
    static constexpr auto P751_mag = BPrime::construct_prime<T,751>("0x6FE5D541F71C0E12909F97BADC668562B5045CB25748084E9867D6EBE876DA959B1A13F7CC76E3EC968549F878A8EEAFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF").mag;



};


#endif //SIDH_CPP_BIGINT_H
