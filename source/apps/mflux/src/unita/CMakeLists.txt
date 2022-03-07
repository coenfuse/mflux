# In this CMakeLists we add all the source files that are
# required with the unit 'unita'. All the source files
# for the current unit are listed here, which are then
# access by the target-wide source list to make up the
# target includes. The target-wide source list references
# to this local list by its variable that is defined below
# as MODULE_SRCS. 
# One can change it according to the name of this variable
# to anything according to the requirment, but the user
# need to make sure the exact same variable name is used in
# the target-wide source list one-directory above.
# To keep up with simple convention, user is recommended to
# use the following pattern for naming a unit source list:
# <folder_name>_SRCS

# In cross-platform applications, a repository might contain
# many cross-platform files in it. But during application's
# compilation, only a selected files might get used according
# to the platform the application is building for.

# To help up with that issue, the source of a unit
# can be categorized into two types:
#  1. PLATFORM_INDEPENDENT_FILES: Files needed on all platforms
#  2. PLATFORM_DEPENDENT_FILES: Files needed only on specific platforms
# There usage is explained below



# The following list contains all the files that must be
# included in compilation for all the platforms. This list
# can be empty given that the PLATFORM_DEPENDENT_FILES list 
# is not empty.
list(APPEND PLATFORM_INDEPENDENT_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/unita.cpp
    # ..
)



# The following list contains all the files that must be
# only included in compilation if the target build platform
# is Windows. This list can be empty.
if(WIN32)
    list(APPEND PLATFORM_DEPENDENT_FILES
        # ${CMAKE_CURRENT_SOURCE_DIR}/<filename>
        # ..
    )
endif()

# The following list contains all the files that must be
# only included in compilation if the target build platform
# is UNIX-like. This list can be empty.
if(UNIX)
    list(APPEND PLATFORM_DEPENDENT_FILES
        # ${CMAKE_CURRENT_SOURCE_DIR}/<filename>
        # ..
    )
endif()

# Add a new check for custom platform here
# ...



# Here we combine both platform dependent and independent
# files into a single list. Don't change anything here,
# except the variable value.
set(UNITA_SRCS
    ${PLATFORM_INDEPENDENT_FILES}
    ${PLATFORM_DEPENDENT_FILES}

    # Here we also include this CMakeLists.txt itself so that
    # it is available right in IDE for editing. This is 
    # optional and can be removed.
    ${CMAKE_CURRENT_SOURCE_DIR}/CMakeLists.txt
PARENT_SCOPE)