#include <iostream>
#include "BigInt.h"
#include "BMath.h"

int main() {
    std::cout << "Hello, World!" << std::endl;

    // Tests Below
    unsigned long r;
    unsigned long c_o;
    BMath::ADDC(r,c_o,ULONG_MAX,12,0);
    std::cout << r << " " << c_o <<std::endl;

    BMath::SUBC(r,c_o,12,100,0);
    std::cout << r << " " << c_o <<std::endl;

    return 0;
}
