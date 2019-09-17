cmake_minimum_required(VERSION 2.8)

set(PROJECTNAME ExamGeneratorTest)
project(${PROJECTNAME})
message("==== Projectname: ${PROJECTNAME}")

set(CMAKE_CXX_FLAGS "-std=c++17 -g -Wall -Wextra -Wpedantic -Wold-style-cast \
    -Winit-self -Wno-unused -Wshadow \
    -Wno-parentheses -Wlogical-op -Wredundant-decls \
    -Wcast-align -Wsign-promo -Wmissing-include-dirs \
    -Woverloaded-virtual -Wctor-dtor-privacy")

find_package(Boost COMPONENTS system filesystem program_options REQUIRED)

include_directories(src)
include_directories(src/hcExam)
include_directories(../app/logger)
include_directories(../app/examGen)
include_directories(../app/examGenC)
include_directories(../app/examGenLogic)
include_directories(../app/parser)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

message("==== Source dir: ${CMAKE_SOURCE_DIR}")

file(
    GLOB_RECURSE EXAMGENERATORTEST_SOURCES
    RELATIVE ${CMAKE_SOURCE_DIR}
    src/*.cpp
    src/*.h
    ../app/logger/*.cpp 
    ../app/logger/*.h 
    ../app/examGen/*.cpp
    ../app/examGen/*.h
    ../app/examGenC/*.cpp
    ../app/examGenC/*.h 
    ../app/examGenLogic/*.cpp
    ../app/examGenLogic/*.h
    ../app/parser/*.cpp 
    ../app/parser/*.h 
    src/hcExam/*.cpp
    src/hcExam/*.h
)

message("==== ExamGeneratorTest sources: ${EXAMGENERATOR_SOURCES}")

add_executable(ExamGeneratorTest ${EXAMGENERATORTEST_SOURCES})
target_link_libraries(ExamGeneratorTest Boost::program_options Boost::filesystem)
