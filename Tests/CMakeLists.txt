# Collect test sources
file(GLOB_RECURSE TEST_SOURCES "*.cpp" "*.h")

# Add the test executable
add_executable(runTests ${TEST_SOURCES})

# Link the test executable
target_link_libraries(runTests PRIVATE core_lib)

# Specify the include directories
target_include_directories(runTests PRIVATE ${PROJECT_SOURCE_DIR}/Include)
