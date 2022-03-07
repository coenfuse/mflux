# The following CMake set named as PROJECT_SRCS will contain
# all the source (.c/cc/cpp) files that are included in its 
# target i.e, defined one directory above. PROJECT_SRCS is
# declared in a PARENT_SCOPE so that it is accessible during
# target build.

# To keep the structure logically scalable and easy to manage,
# it is recommended to further group the source files into
# appropriate folders. One can then then choose the usage of
# files that are included in target build from right here
# without having to remove the original files from repository.

# Adding a new group of source files is as simple as adding two
# lines,
# add_subdirectory(<folder_name>)
# list(APPEND ALL_SRCS ${NAME_OF_SOURCE_GROUP})

add_subdirectory(unita)
list(APPEND ALL_SRCS ${UNITA_SRCS})

add_subdirectory(unitb)
list(APPEND ALL_SRCS ${UNITB_SRCS})

# ..

# The following is the actual declaration of PROJECT_HDRS,
# recommended to keep it as it is.

set(PROJECT_SRCS
    
    # Here we also include this CMakeLists.txt itself so that
    # it is available right in IDE for editing. This is 
    # optional and can be removed.
    ${CMAKE_CURRENT_SOURCE_DIR}/CMakeLists.txt
    
    # Contains list of all the header files that are included
    ${ALL_SRCS}

PARENT_SCOPE)