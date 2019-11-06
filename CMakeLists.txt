cmake_minimum_required(VERSION 3.12)
project(CMA)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-O3 -Wall -Wextra")

add_executable(CMA main.cpp task_1/special_matrix.cpp matrix.cpp task_2/lu_decomposition.cpp
        task_3/symmetric_matrix.cpp task_3/ldlt_decomposition.cpp task_4/tridiagonal_matrix.cpp
        task_3/lu_and_ldlt_speed_test.cpp task_1/special_matrix_speed_test.cpp task_5/relaxation.cpp
        task_5/relaxation_explorer.cpp)