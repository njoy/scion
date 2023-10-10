// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
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

        CHECK_THAT( 1.0, WithinRel( interpolator( 1.0, xLeft, xRight, yLeft, yRight ) ) );
        CHECK_THAT( 2.5, WithinRel( interpolator( 1.5, xLeft, xRight, yLeft, yRight ) ) );
        CHECK_THAT( 4.0, WithinRel( interpolator( 2.0, xLeft, xRight, yLeft, yRight ) ) );
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

        CHECK_THAT( 1.0, WithinRel( interpolation::linlin( 1.0, xLeft, xRight, yLeft, yRight ) ) );
        CHECK_THAT( 2.5, WithinRel( interpolation::linlin( 1.5, xLeft, xRight, yLeft, yRight ) ) );
        CHECK_THAT( 4.0, WithinRel( interpolation::linlin( 2.0, xLeft, xRight, yLeft, yRight ) ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
