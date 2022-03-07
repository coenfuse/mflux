# This CMakeLists contain all the required build info for generating this target

# Adding directories that contain source files
add_subdirectory(include)
add_subdirectory(src)

# Setting up target
project("moda" VERSION 1.0.0)

# Setting up target specific options
option(MODA_BUILD_TESTS "Generate unit tests for ${PROJECT_NAME}" OFF)
option(MODA_BUILD_DOCS "Generate doxygen based docs for ${PROJECT_NAME}" OFF)

# Logging target build info
message(STATUS "Generating ${PROJECT_NAME} v${PROJECT_VERSION}")

# Generating target
add_library(${PROJECT_NAME} ${PROJECT_HDRS} ${PROJECT_SRCS})
add_library(${NAMESPACE}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

# Adding this target in a solution level folder
set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "modules")

# Grouping target's source files in appropriate filters
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/include/${PROJECT_NAME}" PREFIX "Header Files" FILES ${PROJECT_HDRS})
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/src" PREFIX "Source Files" FILES ${PROJECT_SRCS})

# Linking target with directories it is dependent on
target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")

# Linking target with its third-party dependencies
# ..

# Building unit tests for target if enabled
if(MODA_BUILD_TESTS OR BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()