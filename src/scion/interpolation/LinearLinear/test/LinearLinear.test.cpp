#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "scion/interpolation/LinearLinear.hpp"

// other includes

// convenience typedefs
using namespace njoy::scion;

SCENARIO( "LinearLinear" ) {

  GIVEN( "LinearLinear interpolation object" ) {

    WHEN( "interpolating an interval" ) {

      linearisation::LinearLinear interpolator{};

      THEN( "the interpolation is performed correctly" ) {

        double xLeft = 0.0;
        double xRight = 1.0;
        double yLeft = 0.0;
        double yRight = 1.0;

        CHECK( 0.0 == Approx( interpolator( 0.0, xLeft, xRight, yLeft, yRight ) ) );
        CHECK( 0.5 == Approx( interpolator( 0.5, xLeft, xRight, yLeft, yRight ) ) );
        CHECK( 1.0 == Approx( interpolator( 1.0, xLeft, xRight, yLeft, yRight ) ) );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "linlin interpolation function" ) {

    WHEN( "interpolating an interval" ) {

      THEN( "the interpolation is performed correctly" ) {

        double xLeft = 0.0;
        double xRight = 1.0;
        double yLeft = 0.0;
        double yRight = 1.0;

        CHECK( 0.0 == Approx( linearisation::linlin( 0.0, xLeft, xRight, yLeft, yRight ) ) );
        CHECK( 0.5 == Approx( linearisation::linlin( 0.5, xLeft, xRight, yLeft, yRight ) ) );
        CHECK( 1.0 == Approx( linearisation::linlin( 1.0, xLeft, xRight, yLeft, yRight ) ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
