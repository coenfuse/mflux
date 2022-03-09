# The following is the actual declaration of PROJECT_HDRS,
# recommended to keep it as it is.

set(PROJECT_HDRS
    
    # Here we also include this CMakeLists.txt itself so that it is available
    # right in IDE for editing. This is optional and can be removed.
    ${CMAKE_CURRENT_SOURCE_DIR}/CMakeLists.txt
    
    # List of all the header files that are included
    ${CMAKE_CURRENT_SOURCE_DIR}/core/core.h
    ${CMAKE_CURRENT_SOURCE_DIR}/engine/engine.h
    ${CMAKE_CURRENT_SOURCE_DIR}/mflux/mflux.h

PARENT_SCOPE)