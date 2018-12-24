cmake_minimum_required(VERSION 3.10)
project(Automaton)

set(CMAKE_CXX_STANDARD 17)

add_executable(Automaton Sources/main.cpp Sources/Function.cpp Sources/Transition.cpp Sources/Automaton.cpp  Sources/FuncTransition.cpp Sources/DeterAutomaton.cpp)
