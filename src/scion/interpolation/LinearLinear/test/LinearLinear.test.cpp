#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "scion/interpolation/LinearLinear.hpp"

// other includes

// convenience typedefs
using namespace njoy::scion;

SCENARIO( "LinearLinear" ) {

  GIVEN( "LinearLinear interpolation object" ) {

    WHEN( "interpolating an interval" ) {

      interpolation::LinearLinear interpolator{};

      THEN( "the interpolation is performed correctly" ) {

        double xLeft = 1.0;
        double xRight = 2.0;
        double yLeft = 1.0;
        double yRight = 4.0;

        CHECK( 1.0 == Approx( interpolator( 1.0, xLeft, xRight, yLeft, yRight ) ) );
        CHECK( 2.5 == Approx( interpolator( 1.5, xLeft, xRight, yLeft, yRight ) ) );
        CHECK( 4.0 == Approx( interpolator( 2.0, xLeft, xRight, yLeft, yRight ) ) );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "linlin interpolation function" ) {

    WHEN( "interpolating an interval" ) {

      THEN( "the interpolation is performed correctly" ) {

        double xLeft = 1.0;
        double xRight = 2.0;
        double yLeft = 1.0;
        double yRight = 4.0;

        CHECK( 1.0 == Approx( interpolation::linlin( 1.0, xLeft, xRight, yLeft, yRight ) ) );
        CHECK( 2.5 == Approx( interpolation::linlin( 1.5, xLeft, xRight, yLeft, yRight ) ) );
        CHECK( 4.0 == Approx( interpolation::linlin( 2.0, xLeft, xRight, yLeft, yRight ) ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
