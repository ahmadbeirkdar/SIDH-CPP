#include "test.h"
#include <cassert>
int main() {

    objectBenchmark();
    addTests();
    primeConstructorTest();
    subTests();
    mulTests();
    compareTests();
//    customTests();
//std::cout << BMath::FromHex<int>("FF");
    return 0;
}
