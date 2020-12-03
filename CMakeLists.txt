cmake_minimum_required(VERSION 3.16)
project(SIDH_CPP)

set(CMAKE_CXX_STANDARD 20)

include_directories(/usr/local/Cellar/gmp/6.2.1/include)
include_directories(" /usr/local/Cellar/gmp/6.2.1/lib")
include_directories("/usr/local/include")



add_executable(SIDH_CPP main.cpp BigInt.h BMath.h BPrime.h test.h)

set(GMP_DIR "/usr/local/Cellar/gmp/6.2.1")
include_directories(${PROJECT_NAME} ${GMP_DIR}/include)
target_link_libraries(${PROJECT_NAME}
        "${GMP_DIR}/lib/libgmp.a"
        "${GMP_DIR}/lib/libgmpxx.a"
        )