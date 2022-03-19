# This CMakeLists contain all the required build info for generating this target

# Adding directories that contain source files
set(PROJECT_HDRS "include/configurator/configurator.h")
set(PROJECT_SRCS "src/configurator.cpp")

# Setting up target
project("configurator" VERSION 1.2.0)

# Setting up target specific options
# option(CONF_BUILD_TESTS "Generate unit tests for ${PROJECT_NAME}" OFF)
# option(CONF_BUILD_DOCS "Generate doxygen based docs for ${PROJECT_NAME}" OFF)

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
target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_SOURCE_DIR}/source/modules/errorcodes/include/")
target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_SOURCE_DIR}/source/thirdparty/nlohmann-json/include/")

# Linking target with modules it is dependent on
target_link_libraries(${PROJECT_NAME} PUBLIC ${NAMESPACE}::mqtt)

# Linking target with its third-party dependencies
target_link_libraries(${PROJECT_NAME} PRIVATE spdlog::spdlog_header_only)

# Building unit tests for target if enabled
# if(CONF_BUILD_TESTS OR BUILD_TESTS)
#     enable_testing()
#     add_subdirectory(tests)
# endif()