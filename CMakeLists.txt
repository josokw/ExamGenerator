cmake_minimum_required(VERSION 2.8)

set(PROJECTNAME ExamGenerator)
project($(PROJECTNAME))

set(CMAKE_CXX_FLAGS "-g -Wall -Wextra")

find_package(Boost COMPONENTS system filesystem program_options REQUIRED)

include_directories(src)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

file(
    GLOB_RECURSE EXAMGENERATOR_SOURCES
    RELATIVE $(CMAKE_SOURCE_DIR)
    src/*.cpp
    src/*.h
)

message(${EXAMGENERATOR_SOURCES})

add_executable(ExamGenerator ${EXAMGENERATOR_SOURCES})
target_link_libraries(ExamGenerator Boost::program_options Boost::filesystem)
