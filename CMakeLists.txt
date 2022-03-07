# Setting global cmake config an options
cmake_minimum_required(VERSION 3.22 FATAL_ERROR)
message(STATUS "Using CMake v${CMAKE_VERSION}")

# Setting global workspace properties
project("mflux" VERSION 0.3.0.0)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER ".cmake")

# Setting up global namespace that will be used in module aliases
set(NAMESPACE "felidae" CACHE INTERNAL "")

# Setting global code properties
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
message(STATUS "Using CXX_STANDARD ${CMAKE_CXX_STANDARD}")

# Logging global generation info
message(STATUS "Generating ${PROJECT_NAME} v${PROJECT_VERSION}")

# Setting default global options
option(BUILD_TESTS "Generate unit tests for all apps and modules in this workspace" OFF)
option(BUILD_DOCS "Generate doxygen based documentation for supported app and modules in this workspace" OFF)

# Perform critical checks before initiating build
if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
    message(FATAL_ERROR "In-source build not allowed")
endif()

# Add custom CMake utilities
include("${CMAKE_SOURCE_DIR}/tools/cmake/utils.cmake")

# Add custom CMake modules
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/tools/cmake/modules/")

# Enabling root level listing for workspace wide unit tests
enable_testing()

# Add subdirectory to source
add_subdirectory(source)