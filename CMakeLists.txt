cmake_minimum_required(VERSION 3.26)
project(TrabalhoAED)

set(CMAKE_CXX_STANDARD 17)

# List your source files for the executable
set(SOURCE_FILES
        library.cpp
        course.h
        class1.h
        student.h
        schedule.h
        student.cpp
        course.cpp
        class1.cpp
        interface.cpp
        interface.h
        testing1.cpp
)

file(COPY classes_per_uc.csv classes.csv DESTINATION ${CMAKE_BINARY_DIR})

# Define the executable target
add_executable(testing ${SOURCE_FILES})


