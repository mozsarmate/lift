cmake_minimum_required(VERSION 3.23)
project(lift C)

set(CMAKE_C_STANDARD 99)

add_executable(lift main.c adv_alg.c display.c main.h)
