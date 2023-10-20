cmake_minimum_required(VERSION 3.26)
project(TrabalhoAED)

set(CMAKE_CXX_STANDARD 17)

add_library(TrabalhoAED library.cpp
        course.h
        class1.h
        student.h
        time.h
        student.cpp
        course.cpp
        class1.cpp
        interface.cpp
        interface.h
)
