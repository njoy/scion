#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>

// what we are testing
#include "scion/interpolation/Histogram.hpp"

// other includes

// convenience typedefs
using namespace Catch;
using namespace njoy::scion;

SCENARIO( "Histogram" ) {

  GIVEN( "Histogram interpolation object" ) {

    WHEN( "interpolating an interval" ) {

      interpolation::Histogram interpolator{};

      THEN( "the interpolation is performed correctly" ) {

        double xLeft = 1.0;
        double xRight = 2.0;
        double yLeft = 1.0;
        double yRight = 4.0;

        CHECK( 1.0 == Approx( interpolator( 1.0, xLeft, xRight, yLeft, yRight ) ) );
        CHECK( 1.0 == Approx( interpolator( 1.5, xLeft, xRight, yLeft, yRight ) ) );
        CHECK( 1.0 == Approx( interpolator( 2.0, xLeft, xRight, yLeft, yRight ) ) );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "histogram interpolation function" ) {

    WHEN( "interpolating an interval" ) {

      THEN( "the interpolation is performed correctly" ) {

        double xLeft = 1.0;
        double xRight = 2.0;
        double yLeft = 1.0;
        double yRight = 4.0;

        CHECK( 1.0 == Approx( interpolation::histogram( 1.0, xLeft, xRight, yLeft, yRight ) ) );
        CHECK( 1.0 == Approx( interpolation::histogram( 1.5, xLeft, xRight, yLeft, yRight ) ) );
        CHECK( 1.0 == Approx( interpolation::histogram( 2.0, xLeft, xRight, yLeft, yRight ) ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
