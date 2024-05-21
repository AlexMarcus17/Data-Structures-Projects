cmake_minimum_required(VERSION 3.27)
project(untitled)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "/Users/User/Qt")

find_package(Qt5 COMPONENTS
        Core
        REQUIRED)

add_executable(untitled main.cpp)
target_link_libraries(untitled
        Qt5::Core
)

