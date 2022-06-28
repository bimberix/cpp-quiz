cmake_minimum_required(VERSION 3.16)
project(CppQuiz)

set (CMAKE_CXX_COMPILER "g++")
set (CMAKE_CXX_FLAGS "-std=c++2a -fpermissive")

set (CMAKE_EXPORT_COMPILE_COMMANDS ON)


add_executable(cppquiz
    src/main.cpp
    )

target_include_directories(cppquiz PUBLIC
    inc/
    )
