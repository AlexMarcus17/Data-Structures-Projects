cmake_minimum_required(VERSION 3.27)
project(proj1ds)

set(CMAKE_CXX_STANDARD 17)

add_executable(proj1ds
        App.cpp
        Bag.cpp
        BagIterator.cpp
        ExtendedTest.cpp
        ShortTest.cpp)
