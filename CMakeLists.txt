cmake_minimum_required(VERSION 3.12)
project(ectest C)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -pedantic -Wall -Wextra -Werror -g -Wno-unused")

include_directories(src)

add_executable(ectest
        src/ectest.h
        test/tmptest.c
        test/tmptestrunner.c)
