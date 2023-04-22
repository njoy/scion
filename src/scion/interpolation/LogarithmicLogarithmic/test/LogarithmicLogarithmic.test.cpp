#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "scion/interpolation/LogarithmicLogarithmic.hpp"

// other includes

// convenience typedefs
using namespace njoy::scion;

SCENARIO( "LogarithmicLogarithmic" ) {

  GIVEN( "LogarithmicLogarithmic interpolation object" ) {

    WHEN( "interpolating an interval" ) {

      interpolation::LogarithmicLogarithmic interpolator{};

      THEN( "the interpolation is performed correctly" ) {

        double xLeft = 1.0;
        double xRight = 2.0;
        double yLeft = 1.0;
        double yRight = 4.0;

        CHECK( 1.0 == Approx( interpolator( 1.0, xLeft, xRight, yLeft, yRight ) ) );
        CHECK( 2.25 == Approx( interpolator( 1.5, xLeft, xRight, yLeft, yRight ) ) );
        CHECK( 4.0 == Approx( interpolator( 2.0, xLeft, xRight, yLeft, yRight ) ) );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "loglog interpolation function" ) {

    WHEN( "interpolating an interval" ) {

      THEN( "the interpolation is performed correctly" ) {

        double xLeft = 1.0;
        double xRight = 2.0;
        double yLeft = 1.0;
        double yRight = 4.0;

        CHECK( 1.0 == Approx( interpolation::loglog( 1.0, xLeft, xRight, yLeft, yRight ) ) );
        CHECK( 2.25 == Approx( interpolation::loglog( 1.5, xLeft, xRight, yLeft, yRight ) ) );
        CHECK( 4.0 == Approx( interpolation::loglog( 2.0, xLeft, xRight, yLeft, yRight ) ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
