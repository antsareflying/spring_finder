cmake_minimum_required(VERSION 3.29)
project(spring_finder C)

set(CMAKE_C_STANDARD 17)

add_executable(spring_finder main.c
        mesh_rw.c
        spring_finder.h)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Wpedantic")