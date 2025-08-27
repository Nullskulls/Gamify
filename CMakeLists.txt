cmake_minimum_required(VERSION 3.10)
project(minesweeper)

set(CMAKE_C_STANDARD 11)

add_executable(minesweeper
        Source/main.c
        Source/game.c
        Source/draw.c
        Source/handlers.c
        Source/hangman/game.c
        Source/hangman/draw.c
)

target_include_directories(minesweeper PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/Source
)
