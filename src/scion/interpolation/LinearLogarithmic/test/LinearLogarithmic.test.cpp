#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "scion/interpolation/LinearLogarithmic.hpp"

// other includes

// convenience typedefs
using namespace njoy::scion;

SCENARIO( "LinearLogarithmic" ) {

  GIVEN( "LinearLogarithmic interpolation object" ) {

    WHEN( "interpolating an interval" ) {

      interpolation::LinearLogarithmic interpolator{};

      THEN( "the interpolation is performed correctly" ) {

        double xLeft = 1.0;
        double xRight = 2.0;
        double yLeft = 1.0;
        double yRight = 4.0;

        CHECK( 1.0 == Approx( interpolator( 1.0, xLeft, xRight, yLeft, yRight ) ) );
        CHECK( 2.75488750216347 == Approx( interpolator( 1.5, xLeft, xRight, yLeft, yRight ) ) );
        CHECK( 4.0 == Approx( interpolator( 2.0, xLeft, xRight, yLeft, yRight ) ) );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "linlog interpolation function" ) {

    WHEN( "interpolating an interval" ) {

      THEN( "the interpolation is performed correctly" ) {

        double xLeft = 1.0;
        double xRight = 2.0;
        double yLeft = 1.0;
        double yRight = 4.0;

        CHECK( 1.0 == Approx( interpolation::linlog( 1.0, xLeft, xRight, yLeft, yRight ) ) );
        CHECK( 2.75488750216347 == Approx( interpolation::linlog( 1.5, xLeft, xRight, yLeft, yRight ) ) );
        CHECK( 4.0 == Approx( interpolation::linlog( 2.0, xLeft, xRight, yLeft, yRight ) ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
