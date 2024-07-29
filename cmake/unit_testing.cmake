#######################################################################
# Setup
#######################################################################

message( STATUS "Adding scion unit testing" )
enable_testing()

FetchContent_MakeAvailable( Catch2 )

function( add_cpp_test name source )

  set( test_name "scion.${name}.test" )
  add_executable( ${test_name} ${source} )
  add_test( NAME ${test_name} COMMAND ${test_name} )
  target_link_libraries( ${test_name} PRIVATE scion )
  target_link_libraries( ${test_name} PRIVATE Catch2::Catch2WithMain )

  file( GLOB resources "resources/*" )
  foreach( resource ${resources} )
    file( COPY "${resource}" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}" )
  endforeach()

endfunction()

#######################################################################
# Unit testing directories
#######################################################################

add_subdirectory( src/utility/IteratorView/test )

add_subdirectory( src/scion/verification/ranges/test )

add_subdirectory( src/scion/unionisation/unionise/test )

add_subdirectory( src/scion/integration/Histogram/test )
add_subdirectory( src/scion/integration/LinearLinear/test )
add_subdirectory( src/scion/integration/LinearLogarithmic/test )
add_subdirectory( src/scion/integration/LogarithmicLinear/test )
add_subdirectory( src/scion/integration/LogarithmicLogarithmic/test )
add_subdirectory( src/scion/integration/GaussLegendre/2/test )
add_subdirectory( src/scion/integration/GaussLegendre/4/test )
add_subdirectory( src/scion/integration/GaussLegendre/6/test )
add_subdirectory( src/scion/integration/GaussLegendre/7/test )
add_subdirectory( src/scion/integration/GaussLegendre/8/test )
add_subdirectory( src/scion/integration/GaussLegendre/10/test )
add_subdirectory( src/scion/integration/GaussLegendre/16/test )
add_subdirectory( src/scion/integration/GaussLegendre/32/test )
add_subdirectory( src/scion/integration/GaussLegendre/64/test )
add_subdirectory( src/scion/integration/GaussLobatto/2/test )
add_subdirectory( src/scion/integration/GaussLobatto/4/test )
add_subdirectory( src/scion/integration/GaussLobatto/6/test )
add_subdirectory( src/scion/integration/GaussLobatto/8/test )
add_subdirectory( src/scion/integration/GaussLobatto/10/test )
add_subdirectory( src/scion/integration/GaussLobatto/16/test )
add_subdirectory( src/scion/integration/GaussLobatto/32/test )
add_subdirectory( src/scion/integration/GaussLobatto/64/test )

add_subdirectory( src/scion/interpolation/Histogram/test )
add_subdirectory( src/scion/interpolation/LinearLinear/test )
add_subdirectory( src/scion/interpolation/LinearLogarithmic/test )
add_subdirectory( src/scion/interpolation/LogarithmicLinear/test )
add_subdirectory( src/scion/interpolation/LogarithmicLogarithmic/test )

add_subdirectory( src/scion/linearisation/ToleranceConvergence/test )
add_subdirectory( src/scion/linearisation/MidpointSplit/test )
add_subdirectory( src/scion/linearisation/Lineariser/test )

add_subdirectory( src/scion/math/chebyshev/test )
add_subdirectory( src/scion/math/compare/test )
add_subdirectory( src/scion/math/clenshaw/test )
add_subdirectory( src/scion/math/horner/test )
add_subdirectory( src/scion/math/legendre/test )
add_subdirectory( src/scion/math/newton/test )

add_subdirectory( src/scion/math/IntervalDomain/test )
add_subdirectory( src/scion/math/OpenDomain/test )
add_subdirectory( src/scion/math/LinearLinearTable/test )
add_subdirectory( src/scion/math/LinearLinearTableFunction/test )
add_subdirectory( src/scion/math/HistogramTable/test )
add_subdirectory( src/scion/math/LogLinearTable/test )
add_subdirectory( src/scion/math/LinearLogTable/test )
add_subdirectory( src/scion/math/LogLogTable/test )
add_subdirectory( src/scion/math/InterpolationTable/test )
add_subdirectory( src/scion/math/ChebyshevSeries/test )
add_subdirectory( src/scion/math/ChebyshevApproximation/test )
add_subdirectory( src/scion/math/LegendreSeries/test )
add_subdirectory( src/scion/math/PolynomialSeries/test )
add_subdirectory( src/scion/math/AnalyticalIntegrator/test )
