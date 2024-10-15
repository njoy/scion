########################################################################
# Preamble
########################################################################

cmake_minimum_required( VERSION 3.27 )

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
  "NOT ${subproject} OR DEFINED require.scion.python " OFF
)

option( scion.installation "Install ACEtk" ON )

########################################################################
# Dependencies
########################################################################

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/.cmake)
include( cmake/dependencies.cmake )

########################################################################
# Project targets
########################################################################

string( CONCAT prefix
  "$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/src>"
  "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
)

# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
# scion : library
# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

add_library( scion INTERFACE )
add_library( njoy::scion ALIAS scion )

target_include_directories( scion INTERFACE ${prefix} )

target_link_libraries( scion
  INTERFACE
    eigen
    njoy::tools
)

# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
# scion : python bindings
# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

if( scion.python )

  pybind11_add_module( scion.python
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/scion.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/interpolation.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/interpolation/interpolation.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/interpolation/InterpolationType.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/integration.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/integration/integration.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/integration/GaussLegendre.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/integration/GaussLobatto.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/linearisation.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/linearisation/MidpointSplit.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/linearisation/ToleranceConvergence.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/linearisation/Lineariser.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/math.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/math/clenshaw.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/math/compare.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/math/horner.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/math/newton.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/math/chebyshev.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/math/legendre.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/math/IntervalDomain.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/math/OpenDomain.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/math/LinearLinearTable.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/math/HistogramTable.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/math/LogLogTable.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/math/LogLinearTable.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/math/LinearLogTable.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/math/InterpolationTable.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/math/ChebyshevSeries.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/math/ChebyshevApproximation.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/math/LegendreSeries.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/math/PolynomialSeries.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/math/AnalyticalIntegrator.python.cpp
      )
  add_library( njoy::scion.python ALIAS scion.python )

  target_link_libraries( scion.python PRIVATE scion )
  target_include_directories( scion.python PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/python/src )
  target_compile_options( scion.python PRIVATE -fvisibility=hidden )
  set_target_properties( scion.python PROPERTIES OUTPUT_NAME scion )
  set_target_properties( scion.python PROPERTIES COMPILE_DEFINITIONS "PYBIND11" )
  set_target_properties( scion.python PROPERTIES POSITION_INDEPENDENT_CODE ON )

  message( STATUS "Building scion's python API" )

  set( scion_PYTHONPATH "${CMAKE_CURRENT_BINARY_DIR}" )

  if( scion.tests )
    include( cmake/unit_testing_python.cmake )
  endif()

endif()

if( scion.tests )
  include( cmake/unit_testing.cmake )
endif()

#######################################################################
# Installation
#######################################################################

if(scion.installation)
    include(CMakePackageConfigHelpers)

    install(TARGETS scion EXPORT scion-targets
      ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
      LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
      RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
    )

    install(EXPORT scion-targets
      FILE "scion-targets.cmake"
      NAMESPACE njoy::
      DESTINATION share/cmake/scion
    )

    install(DIRECTORY src/
      DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
      FILES_MATCHING PATTERN "*.hpp"
      PATTERN "*test*" EXCLUDE
    )

    string(TOLOWER scion lowercasePackageName)

    write_basic_package_version_file("${lowercasePackageName}-config-version.cmake"
      VERSION ${PROJECT_VERSION}
      COMPATIBILITY AnyNewerVersion)

    configure_package_config_file(
      ${CMAKE_CURRENT_SOURCE_DIR}/cmake/${lowercasePackageName}-config.cmake.in
      ${PROJECT_BINARY_DIR}/${lowercasePackageName}-config.cmake
      INSTALL_DESTINATION share/cmake/scion
    )

    install(FILES
      "${PROJECT_BINARY_DIR}/${lowercasePackageName}-config.cmake"
      "${PROJECT_BINARY_DIR}/${lowercasePackageName}-config-version.cmake"
      DESTINATION share/cmake/scion
    )

    if(NOT subproject)
      set(CPACK_PACKAGE_VENDOR "Los Alamos National Laboratory")
      set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
      include(CPack)
    endif()
endif()
