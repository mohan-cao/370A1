cmake_minimum_required(VERSION 3.8)
project(370A1)

set(CMAKE_C_STANDARD 99)
file(GLOB SOURCES Part1/OSA1.1.c Part1/littleThread.h)
add_executable(370A1 ${SOURCES})