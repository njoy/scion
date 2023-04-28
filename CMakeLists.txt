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
    INTERFACE Log
    INTERFACE catch-adapter
    INTERFACE eigen
    )

# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
# scion : python bindings
# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

if( scion.python )

  pybind11_add_module( scion.python
      python/src/scion.python.cpp
      python/src/interpolation.python.cpp
      python/src/interpolation/interpolation.python.cpp
      python/src/linearisation.python.cpp
      python/src/linearisation/MidpointSplit.python.cpp
      python/src/linearisation/ToleranceConvergence.python.cpp
      python/src/linearisation/Lineariser.python.cpp
      python/src/math.python.cpp
      python/src/math/clenshaw.python.cpp
      python/src/math/compare.python.cpp
      python/src/math/horner.python.cpp
      python/src/math/legendre.python.cpp
      python/src/math/IntervalDomain.python.cpp
      python/src/math/OpenDomain.python.cpp
      python/src/math/LinearLinearTable.python.cpp
      python/src/math/LogLogTable.python.cpp
      python/src/math/LogLinearTable.python.cpp
      python/src/math/LinearLogTable.python.cpp
      python/src/math/LegendreSeries.python.cpp
      python/src/math/PolynomialSeries.python.cpp
      )

  target_link_libraries( scion.python PRIVATE scion )
  target_include_directories( scion.python PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/python/src )
  target_compile_options( scion.python PRIVATE "-fvisibility=hidden" )
  set_target_properties( scion.python PROPERTIES OUTPUT_NAME scion )
  set_target_properties( scion.python PROPERTIES COMPILE_DEFINITIONS "PYBIND11" )
  set_target_properties( scion.python PROPERTIES POSITION_INDEPENDENT_CODE ON)

  message( STATUS "Building scion's python API" )

  list( APPEND SCION_PYTHONPATH ${CMAKE_CURRENT_BINARY_DIR} )

  include( cmake/unit_testing_python.cmake )

endif()

if( CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR )
  if( scion.tests )
    include( cmake/unit_testing.cmake )
  endif()
endif()
