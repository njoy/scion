// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
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

        CHECK_THAT( 1., WithinRel( interpolator( 1.0, xLeft, xRight, yLeft, yRight ) ) );
        CHECK_THAT( 2., WithinRel( interpolator( 1.5, xLeft, xRight, yLeft, yRight ) ) );
        CHECK_THAT( 4., WithinRel( interpolator( 2.0, xLeft, xRight, yLeft, yRight ) ) );
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

        CHECK_THAT( 1., WithinRel( interpolation::loglin( 1.0, xLeft, xRight, yLeft, yRight ) ) );
        CHECK_THAT( 2., WithinRel( interpolation::loglin( 1.5, xLeft, xRight, yLeft, yRight ) ) );
        CHECK_THAT( 4., WithinRel( interpolation::loglin( 2.0, xLeft, xRight, yLeft, yRight ) ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
