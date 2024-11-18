cmake_minimum_required(VERSION 3.29)
project(Prepro-Syllo C)

set(CMAKE_C_STANDARD 11)

add_executable(Prepro-Syllo main.c
        interface.c
        save.c
        traitement.c
        traitement.h)
