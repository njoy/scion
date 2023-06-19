#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "scion/interpolation/LogarithmicLinear.hpp"

// other includes

// convenience typedefs
using namespace njoy::scion;

SCENARIO( "LogarithmicLinear" ) {

  GIVEN( "LogarithmicLinear interpolation object" ) {

    WHEN( "interpolating an interval" ) {

      interpolation::LogarithmicLinear interpolator{};

      THEN( "the interpolation is performed correctly" ) {

        double xLeft = 1.0;
        double xRight = 2.0;
        double yLeft = 1.0;
        double yRight = 4.0;

        CHECK( 1.0 == Approx( interpolator( 1.0, xLeft, xRight, yLeft, yRight ) ) );
        CHECK( 2.0 == Approx( interpolator( 1.5, xLeft, xRight, yLeft, yRight ) ) );
        CHECK( 4.0 == Approx( interpolator( 2.0, xLeft, xRight, yLeft, yRight ) ) );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "loglin interpolation function" ) {

    WHEN( "interpolating an interval" ) {

      THEN( "the interpolation is performed correctly" ) {

        double xLeft = 1.0;
        double xRight = 2.0;
        double yLeft = 1.0;
        double yRight = 4.0;

        CHECK( 1.0 == Approx( interpolation::loglin( 1.0, xLeft, xRight, yLeft, yRight ) ) );
        CHECK( 2.0 == Approx( interpolation::loglin( 1.5, xLeft, xRight, yLeft, yRight ) ) );
        CHECK( 4.0 == Approx( interpolation::loglin( 2.0, xLeft, xRight, yLeft, yRight ) ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
