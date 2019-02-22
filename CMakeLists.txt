cmake_minimum_required(VERSION 3.12)
project(TestC__)

set(CMAKE_CXX_STANDARD 17)

add_executable(mainTest main.cpp main.cpp ClassDefine.h myVector.h referVector.h myList.h Dpll.h)
add_executable(Test test.cpp test.cpp)