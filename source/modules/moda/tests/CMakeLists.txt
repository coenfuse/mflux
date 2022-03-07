# Storing the name of the target this target will be testing
set(SUSPECT ${PROJECT_NAME})

# Enabling testing in this directory so that it can be indexed by ctest
enable_testing()

# Setting up the testing target with a name derived from suspect's name
project("${SUSPECT}-utest" VERSION 1.1.0)

# Logging
message(STATUS "Generating ${PROJECT_NAME} v${PROJECT_VERSION}")

# Generating target
add_executable(${PROJECT_NAME} main.test.cpp)

# Adding to appropriate folder
set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "tests/modules/${SUSPECT}")

# Linking target with its third-party dependencies (PRIVATE / PUBLIC / INTERFACE)
target_link_libraries(${PROJECT_NAME} PRIVATE doctest::doctest)

# Linking this target with the target it is testing
# Here we are linking our test target with <suspect>.lib and not <suspect>-main.exe
target_link_libraries(${PROJECT_NAME} PRIVATE ${SUSPECT})

# Adding this targe to tests list so that it can be found by ctest
add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})

# Setting test properties (if any)
set_tests_properties(${PROJECT_NAME} PROPERTIES LABELS "ALL")