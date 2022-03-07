# The following CMake set named as PROJECT_HDRS will contain
# all the header (.h/hpp) files that are included in its 
# target i.e, defined one directory above. PROJECT_HDRS is
# declared in a PARENT_SCOPE so that it is accessible during
# target build.

# To keep the structure logically scalable and easy to manage,
# it is recommended to further group the header files into
# appropriate folders. One can then then choose the usage of
# files that are included in target build from right here
# without having to remove the original files from repository.

# Adding a new group of header files is as simple as adding two
# lines,
# add_subdirectory(<folder_name>)
# list(APPEND ALL_HDRS ${NAME_OF_HEADER_GROUP})

add_subdirectory(mflux)
list(APPEND ALL_HDRS ${MFLUX_HDRS})

# ..

# The following is the actual declaration of PROJECT_HDRS,
# recommended to keep it as it is.

set(PROJECT_HDRS
    
    # Here we also include this CMakeLists.txt itself so that it is available
    # right in IDE for editing. This is optional and can be removed.
    ${CMAKE_CURRENT_SOURCE_DIR}/CMakeLists.txt
    
    # Contains list of all the header files that are included
    ${ALL_HDRS}

PARENT_SCOPE)