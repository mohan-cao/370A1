cmake_minimum_required(VERSION 3.8)
project(370A1)

set(CMAKE_C_STANDARD 99)
file(GLOB SOURCES Part3/OSA1.3.c Part3/littleThread.h)
add_executable(370A1 ${SOURCES})