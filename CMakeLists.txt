cmake_minimum_required(VERSION 3.23)
project(lift C)

set(CMAKE_C_STANDARD 99)

add_executable(lift main.c adv_alg.c display.c main.h menu.c find_lift.c move_lift.c debugmalloc.h low_calc.c file_manager.c)
