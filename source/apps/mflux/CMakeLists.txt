# This CMakeLists contains all the required build info for generating this target

# Adding directories that contain source files
add_subdirectory(include)
add_subdirectory(src)

# Setting up target
project("mflux" VERSION 0.4.0.0 DESCRIPTION "A gateway application for data transfer between MQTT and InfluxDB")

# Setting up target specific options
option(PROJ_BUILD_TESTS "Generate unit tests for ${PROJECT_NAME}" OFF)
option(PROJ_BUILD_DOCS "Generate doxygen based docs for ${PROJECT_NAME}" OFF)

# Logging target build info
message(STATUS "Generating ${PROJECT_NAME} v${PROJECT_VERSION}")

# Generating target as a library
add_library(${PROJECT_NAME} ${PROJECT_HDRS} ${PROJECT_SRCS})

# Adding this target in a solution level folder
set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "apps")

# Grouping target's source files in appropriate filters
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/include" PREFIX "Header Files" FILES ${PROJECT_HDRS})
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/src" PREFIX "Source Files" FILES ${PROJECT_SRCS})

# Configuring target versioning
configure_file(config/app-config.h.in ${CMAKE_CURRENT_BINARY_DIR}/config/app-config.h @ONLY)
target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_BINARY_DIR}/config/")

# Including directories with target (PRIVATE / PUBLIC / INTERACE)
target_include_directories(${PROJECT_NAME} PUBLIC "include")
target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_SOURCE_DIR}/source/modules/errorcodes/include/")

# Linking target with its modules or library depdencies (PRIVATE / PUBLIC / INTERFACE)
target_link_libraries(${PROJECT_NAME} PUBLIC ${NAMESPACE}::moda)
target_link_libraries(${PROJECT_NAME} PRIVATE CLI11::CLI11)
target_link_libraries(${PROJECT_NAME} PUBLIC fmt::fmt-header-only)
target_link_libraries(${PROJECT_NAME} PRIVATE spdlog::spdlog_header_only)

# Creating an executable that links to its library equivalent that we made above.
# This is vital in creating a testing target for this target.
add_executable("${PROJECT_NAME}-main" "src/main.cpp")
target_link_libraries("${PROJECT_NAME}-main" PRIVATE ${PROJECT_NAME})

# Adding this built exe target to the same solution level folder
set_target_properties("${PROJECT_NAME}-main" PROPERTIES FOLDER "apps")

# Building unit tests for target if enabled
if(PROJECT_BUILD_TESTS OR BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()