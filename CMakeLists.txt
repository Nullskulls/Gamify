cmake_minimum_required(VERSION 3.10)
project(minesweeper)

set(CMAKE_C_STANDARD 11)

add_executable(minesweeper
        Source/main.c
        Source/game.c
        Source/draw.c
)
