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

    std::cout << sizeof(unsigned long) << std::endl;

//    std::cout << BigInt<unsigned int>::P434_mag

    std::cout << "P343 mag in as unsigned long 'words': " << std::endl;
    auto temp = BigInt<unsigned long>::P434_mag;
    for(auto i : temp)
        std::cout << i << std::endl;

    std::cout << "P343 mag in as unsigned int 'words': " << std::endl;
    auto temp1 = BigInt<unsigned int>::P434_mag;
    for(auto i : temp1)
        std::cout << i << std::endl;



    return 0;
}
