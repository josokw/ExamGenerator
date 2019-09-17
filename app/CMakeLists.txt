cmake_minimum_required(VERSION 2.8)

set(PROJECTNAME ExamGenerator)
project(${PROJECTNAME})
message("==== Projectname: ${PROJECTNAME}")

set(CMAKE_CXX_FLAGS "-std=c++17 -g -Wall -Wextra -Wpedantic -Wold-style-cast \
    -Winit-self -Wno-unused -Wshadow \
    -Wno-parentheses -Wlogical-op -Wredundant-decls \
    -Wcast-align -Wsign-promo -Wmissing-include-dirs \
    -Woverloaded-virtual -Wctor-dtor-privacy")

find_package(Boost COMPONENTS system filesystem program_options REQUIRED)

include_directories(src)
include_directories(logger)
include_directories(examGen)
include_directories(examGenC)
include_directories(examGenLogic)
include_directories(parser)
include_directories(src/hcExam)
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
    examGenC/*.cpp
    examGenC/*.h 
    examGenLogic/*.cpp
    examGenLogic/*.h
    parser/*.cpp 
    parser/*.h 
    src/hcExam/*.cpp
    src/hcExam/*.h
)

message("==== ExamGenerator sources: ${EXAMGENERATOR_SOURCES}")

add_executable(ExamGenerator ${EXAMGENERATOR_SOURCES})
target_link_libraries(ExamGenerator Boost::program_options Boost::filesystem)
