cmake_minimum_required(VERSION 3.10)

project(
    minigrep
    VERSION 1.0
    LANGUAGES CXX
)

include_directories(include)

add_executable(
    minigrep 
    minigrep.cpp
    include/args.cpp
    include/args.h
)
