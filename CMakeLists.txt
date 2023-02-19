cmake_minimum_required(VERSION 3.21)
project(Lab3 C)

set(CMAKE_C_STANDARD 99)

set(CMAKE_C_FLAGS -pthread)

add_executable(CalTrain caltrain-runner.c caltrain.c caltrain.h)
