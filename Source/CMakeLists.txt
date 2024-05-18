# Collect source files
file(GLOB_RECURSE SOURCE_FILES "*.cpp")

# Create a library called "core_lib"
add_library(core_lib ${SOURCE_FILES})

# Specify include directories
target_include_directories(core_lib PUBLIC ${PROJECT_SOURCE_DIR}/Include)
