########################################################################
# Preamble
########################################################################
cmake_minimum_required( VERSION 3.14 )
project( scion LANGUAGES CXX )

########################################################################
# Project-wide setup
########################################################################

set( CMAKE_CXX_STANDARD 17 )
set( CMAKE_CXX_STANDARD_REQUIRED YES )

option( scion.tests "Build the scion unit tests" OFF )
option( scion.python "Build scion python bindings" ON )
option( strict_compile
    "Treat all warnings as errors." ON
    )

# Compile flags
set( common_flags "-Wall" "-Wextra" "-Wpedantic" )
set( strict_flags "-Werror" )
set( release_flags "-O3" )
set( debug_flags "-O0" "-g" )


########################################################################
# Dependencies
########################################################################

set( REPOSITORIES "release"
    CACHE STRING
    "Options for where to fetch repositories: develop, release, local"
    )

message( STATUS "Using ${REPOSITORIES} repositories" )

if( REPOSITORIES STREQUAL "develop" )
    include( cmake/develop_dependencies.cmake )

elseif( REPOSITORIES STREQUAL "release" )
    include( cmake/release_dependencies.cmake )

elseif( REPOSITORIES STREQUAL "local" )
    include( cmake/local_dependencies.cmake )

endif()


########################################################################
# Project targets
########################################################################

# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
# scion : library
# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

include_directories( src/ )

add_library( scion INTERFACE )
target_include_directories( scion INTERFACE src/ )
target_link_libraries( scion
    INTERFACE tools
    INTERFACE Catch2
    )

# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
# scion : python bindings
# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

if( scion.python )

  pybind11_add_module( scion.python
      python/src/scion.python.cpp
      )

  target_link_libraries( scion.python PRIVATE scion )
  target_include_directories( scion.python PRIVATE python/src )
  target_compile_options( scion.python PRIVATE "-fvisibility=hidden" )
  set_target_properties( scion.python PROPERTIES OUTPUT_NAME scion )
  set_target_properties( scion.python PROPERTIES COMPILE_DEFINITIONS "PYBIND11" )
  set_target_properties( scion.python PROPERTIES POSITION_INDEPENDENT_CODE ON)

endif()

#######################################################################
# Top-level Only
#######################################################################

if( CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR )

    if( scion.tests )
        include( cmake/unit_testing.cmake )
    endif()

endif()
