cmake_minimum_required(VERSION 3.20)
project(CS)

set(CMAKE_CXX_STANDARD 14)

add_executable(CS main.cpp
        include/Tree.h
        src/Tree.cpp
        include/BlackScholes.h
        src/BlackScholes.cpp generateData.cpp include/generateData.h)
