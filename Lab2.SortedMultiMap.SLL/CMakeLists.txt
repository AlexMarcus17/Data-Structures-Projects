cmake_minimum_required(VERSION 3.27)
project(proj2ds)

set(CMAKE_CXX_STANDARD 17)

add_executable(proj2ds
        App.cpp
        ExtendedTest.cpp
        ShortTest.cpp
        SMMIterator.cpp
        SortedMultiMap.cpp)
