########################################################################
# Preamble
########################################################################

cmake_minimum_required( VERSION 3.14 )

set( subproject OFF )
if( DEFINED PROJECT_NAME )
  set( subproject ON )
endif()

project( scion
  VERSION 0.1.0
  LANGUAGES CXX
)

include( CTest )
include( CMakeDependentOption )
include( GNUInstallDirs )

########################################################################
# Project-wide setup
########################################################################

set( CMAKE_CXX_STANDARD 17 )
set( CMAKE_CXX_STANDARD_REQUIRED YES )

cmake_dependent_option(
  scion.tests
  "Build the scion unit tests and integrate with ctest" ON
  "BUILD_TESTING AND NOT ${subproject}" OFF
)
cmake_dependent_option(
  scion.python
  "Build scion python bindings" ON
  "NOT ${subproject}" OFF
)

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

add_library( scion INTERFACE )
add_library( njoy::scion ALIAS scion )
target_include_directories( scion
  INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/src>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)
target_link_libraries( scion
  INTERFACE
    eigen
    spdlog::spdlog
)

# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
# scion : python bindings
# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

if( scion.python )

  FetchContent_MakeAvailable( pybind11 )

  pybind11_add_module( scion.python
      python/src/scion.python.cpp
      python/src/interpolation.python.cpp
      python/src/interpolation/interpolation.python.cpp
      python/src/interpolation/InterpolationType.python.cpp
      python/src/integration.python.cpp
      python/src/integration/integration.python.cpp
      python/src/integration/GaussLegendre.python.cpp
      python/src/integration/GaussLobatto.python.cpp
      python/src/linearisation.python.cpp
      python/src/linearisation/MidpointSplit.python.cpp
      python/src/linearisation/ToleranceConvergence.python.cpp
      python/src/linearisation/Lineariser.python.cpp
      python/src/math.python.cpp
      python/src/math/clenshaw.python.cpp
      python/src/math/compare.python.cpp
      python/src/math/horner.python.cpp
      python/src/math/newton.python.cpp
      python/src/math/chebyshev.python.cpp
      python/src/math/legendre.python.cpp
      python/src/math/IntervalDomain.python.cpp
      python/src/math/OpenDomain.python.cpp
      python/src/math/LinearLinearTable.python.cpp
      python/src/math/HistogramTable.python.cpp
      python/src/math/LogLogTable.python.cpp
      python/src/math/LogLinearTable.python.cpp
      python/src/math/LinearLogTable.python.cpp
      python/src/math/InterpolationTable.python.cpp
      python/src/math/ChebyshevSeries.python.cpp
      python/src/math/ChebyshevApproximation.python.cpp
      python/src/math/LegendreSeries.python.cpp
      python/src/math/PolynomialSeries.python.cpp
      python/src/math/AnalyticalIntegrator.python.cpp
      )

  target_link_libraries( scion.python PRIVATE scion )
  target_include_directories( scion.python PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/python/src )
  target_compile_options( scion.python PRIVATE "-fvisibility=hidden" )
  set_target_properties( scion.python PROPERTIES OUTPUT_NAME scion )
  set_target_properties( scion.python PROPERTIES COMPILE_DEFINITIONS "PYBIND11" )
  set_target_properties( scion.python PROPERTIES POSITION_INDEPENDENT_CODE ON )

  message( STATUS "Building scion's python API" )

  list( APPEND SCION_PYTHONPATH ${CMAKE_CURRENT_BINARY_DIR} )

  include( cmake/unit_testing_python.cmake )

endif()

if( CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR )
  if( scion.tests )
    include( cmake/unit_testing.cmake )
  endif()
endif()
