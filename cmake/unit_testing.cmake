#######################################################################
# Setup
#######################################################################

message( STATUS "Adding codex unit testing" )
enable_testing()


#######################################################################
# Unit testing directories
#######################################################################

add_subdirectory( src/scion/interpolation/Histogram/test )
add_subdirectory( src/scion/interpolation/LinearLinear/test )
add_subdirectory( src/scion/interpolation/LinearLogarithmic/test )
add_subdirectory( src/scion/interpolation/LogarithmicLinear/test )
add_subdirectory( src/scion/interpolation/LogarithmicLogarithmic/test )

add_subdirectory( src/scion/linearisation/Lineariser/test )

add_subdirectory( src/scion/math/compare/test )
add_subdirectory( src/scion/math/clenshaw/test )
add_subdirectory( src/scion/math/horner/test )
add_subdirectory( src/scion/math/legendre/test )
add_subdirectory( src/scion/math/newton/test )

add_subdirectory( src/scion/math/IntervalDomain/test )
add_subdirectory( src/scion/math/OpenDomain/test )
add_subdirectory( src/scion/math/LegendreSeries/test )
add_subdirectory( src/scion/math/PolynomialSeries/test )
