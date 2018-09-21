cmake_minimum_required(VERSION 2.8)

set(PROJECTNAME ExamGenerator)
project(${PROJECTNAME})
message("==== Projectname: ${PROJECTNAME}")

set(CMAKE_CXX_FLAGS "-g -Wall -Wextra -Wpedantic")

find_package(Boost COMPONENTS system filesystem program_options REQUIRED)

include_directories(src)
include_directories(logger)
include_directories(examGen)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

message("==== Source dir: ${CMAKE_SOURCE_DIR}")

file(
    GLOB_RECURSE EXAMGENERATOR_SOURCES
    RELATIVE ${CMAKE_SOURCE_DIR}
    src/*.cpp
    src/*.h
    logger/*.cpp 
    logger/*.h 
    examGen/*.cpp
    examGen/*.h
)

message("==== ExamGenerator sources: ${EXAMGENERATOR_SOURCES}")

add_executable(ExamGenerator ${EXAMGENERATOR_SOURCES})
target_link_libraries(ExamGenerator Boost::program_options Boost::filesystem)
