cmake_minimum_required(VERSION 3.27)
project(RunExecutable VERSION 1.0 DESCRIPTION "Advanced Programming Group Project" LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_BUILD_TYPE "Release")

# Include the subdirectories
add_subdirectory(Source)
add_subdirectory(Tests)

# Add the executable
add_executable(${PROJECT_NAME} Source/main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE core_lib)
