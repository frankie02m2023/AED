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
        Source_files/sorting_options.cpp Source_files/request.cpp )

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
        Source_files/schedule_system.cpp
        Source_files/schedule_system.h
        Source_files/schedule.cpp
        Source_files/sorting_options.cpp
        Source_files/sorting_options.h
        Source_files/request.cpp
        Source_files/request.h
        Source_files/main.cpp
)

file(COPY Data_files/classes_per_uc.csv Data_files/classes.csv Data_files/students_classes.csv DESTINATION ${CMAKE_BINARY_DIR})

# Define the executable target
add_executable(testing1 ${SOURCE_FILES})

# Doxygen Build
find_package(Doxygen)
if(DOXYGEN_FOUND)
    set(BUILD_DOC_DIR "${CMAKE_SOURCE_DIR}/docs/output")
    if(NOT EXISTS "${BUILD_DOC_DIR}")
        file(MAKE_DIRECTORY "${BUILD_DOC_DIR}")
    endif()
    set(DOXYGEN_IN "${CMAKE_CURRENT_SOURCE_DIR}/docs/doxyfile")
    set(DOXYGEN_OUT "${CMAKE_CURRENT_BINARY_DIR}/doxyfile")
    configure_file("${DOXYGEN_IN}" "${DOXYGEN_OUT}" @ONLY)
    message("Doxygen build started")
    add_custom_target(Doxygen ALL
            COMMAND "${DOXYGEN_EXECUTABLE}" "${DOXYGEN_OUT}"
            WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
            COMMENT "Generating API documentation with Doxygen"
            VERBATIM)
else(DOXYGEN_FOUND)
    message("Doxygen needs to be installed to generate the documentation.")
endif(DOXYGEN_FOUND)



