cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(BigMPI C)

find_package(MPI)
if(MPI_FOUND)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${MPI_COMPILE_FLAGS}")
    include_directories(${MPI_INCLUDE_PATH})
else()
    message(FATAL_ERROR "-- This example requires MP, but CMake could not find any MPI installation, check $PATH")
endif()


add_executable(test_type_contig.x  test_type_contig.c)
add_executable(type_contiguous_x.x type_contiguous_x.c)
