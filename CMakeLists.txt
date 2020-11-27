cmake_minimum_required(VERSION 3.16)
project(SIDH_CPP)

set(CMAKE_CXX_STANDARD 20)

add_executable(SIDH_CPP main.cpp BigInt.cpp BigInt.h BMath.cpp BMath.h BPrime.h)