#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "scion/interpolation/Histogram.hpp"

// other includes

// convenience typedefs
using namespace njoy::scion;

SCENARIO( "Histogram" ) {

  GIVEN( "Histogram interpolation object" ) {

    WHEN( "interpolating an interval" ) {

      interpolation::Histogram interpolator{};

      THEN( "the interpolation is performed correctly" ) {

        double xLeft = 0.0;
        double xRight = 1.0;
        double yLeft = 0.0;
        double yRight = 1.0;

        CHECK( 0.0 == Approx( interpolator( 0.0, xLeft, xRight, yLeft, yRight ) ) );
        CHECK( 0.0 == Approx( interpolator( 0.5, xLeft, xRight, yLeft, yRight ) ) );
        CHECK( 0.0 == Approx( interpolator( 1.0, xLeft, xRight, yLeft, yRight ) ) );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "histogram interpolation function" ) {

    WHEN( "interpolating an interval" ) {

      THEN( "the interpolation is performed correctly" ) {

        double xLeft = 0.0;
        double xRight = 1.0;
        double yLeft = 0.0;
        double yRight = 1.0;

        CHECK( 0.0 == Approx( interpolation::histogram( 0.0, xLeft, xRight, yLeft, yRight ) ) );
        CHECK( 0.0 == Approx( interpolation::histogram( 0.5, xLeft, xRight, yLeft, yRight ) ) );
        CHECK( 0.0 == Approx( interpolation::histogram( 1.0, xLeft, xRight, yLeft, yRight ) ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
