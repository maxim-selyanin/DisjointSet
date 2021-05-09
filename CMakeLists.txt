cmake_minimum_required(VERSION 3.15)
project(DisjointSet)

set(CMAKE_CXX_STANDARD 17)

add_executable(DisjointSet main.cpp pch.h common.cpp common.h edge.h stack_massive.h core.cpp core.h disjoint_set.h)