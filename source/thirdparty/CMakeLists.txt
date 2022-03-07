# This CMakeLists will only contain add_subdirectories that refer to build of third party
# libraries that are used in this workspace

# Enable or disable existing ones by commenting them out
if(NOT TARGET cli11)
    add_subdirectory(cli11)
endif()

if(NOT TARGET doctest_with_main)
    add_subdirectory(doctest)
    set_target_properties("doctest_with_main" PROPERTIES FOLDER "thirdparty")
endif()

if(NOT TARGET fmt)
    add_subdirectory(fmt)
    set_target_properties("fmt" PROPERTIES FOLDER "thirdparty")
endif()