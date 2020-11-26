#include <iostream>
#include "BigInt.h"
#include "BMath.h"

int main() {
    std::cout << "Hello, World!" << std::endl;

    // Tests Below
    unsigned int r;
    unsigned int c_o;
    BMath::ADDC<unsigned int>(r,c_o,UINT_MAX,12,0);
    std::cout << r << " " << c_o <<std::endl;

    BMath::SUBC<unsigned int>(r,c_o,12,100,0);
    std::cout << r << " " << c_o <<std::endl;

    return 0;
}
