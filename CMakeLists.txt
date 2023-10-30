cmake_minimum_required(VERSION 3.26)
project(TrabalhoAED)

set(CMAKE_CXX_STANDARD 17)

set( CMAKE_BUILD_TYPE_TMP "${CMAKE_BUILD_TYPE}" )
set( CMAKE_BUILD_TYPE "Release" )
add_subdirectory(googletest)
include_directories(googletest/googletest/include)
include_directories(googletest/googlemock/include)
add_subdirectory(benchmark)
include_directories(benchmark/include)
set( CMAKE_BUILD_TYPE ${CMAKE_BUILD_TYPE_TMP} )

add_executable(googletest Tests/gtest.cpp Source_files/student.cpp Source_files/interface.cpp Source_files/class1.cpp Source_files/course.cpp Source_files/schedule.cpp
        Source_files/course_class_request.cpp Source_files/course_request.cpp Source_files/sorting_options.cpp Source_files/testing1.cpp)

target_link_libraries(googletest gtest gtest_main benchmark benchmark_main)

# List your source files for the executable
set(SOURCE_FILES
        Source_files/course.h
        Source_files/class1.h
        Source_files/student.h
        Source_files/schedule.h
        Source_files/student.cpp
        Source_files/course.cpp
        Source_files/class1.cpp
        Source_files/interface.cpp
        Source_files/interface.h
        Source_files/testing1.cpp
        Source_files/schedule_system.cpp
        Source_files/schedule_system.h
        Source_files/course_request.cpp
        Source_files/course_request.h
        Source_files/course_class_request.cpp
        Source_files/course_class_request.h
        Source_files/schedule.cpp
        Source_files/sorting_options.cpp
        Source_files/sorting_options.h
)

file(COPY Data_files/classes_per_uc.csv Data_files/classes.csv Data_files/students_classes.csv DESTINATION ${CMAKE_BINARY_DIR})

# Define the executable target
add_executable(testing1 ${SOURCE_FILES})


