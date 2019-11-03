cmake_minimum_required(VERSION 3.12)
project(CMA)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-O3 -Wall -Wextra")

add_executable(CMA main.cpp specialmatrix.cpp matrix.cpp ludecomposition.cpp
        symmetricmatrix.cpp ldltdecomposition.cpp tridiagonalmatrix.cpp)