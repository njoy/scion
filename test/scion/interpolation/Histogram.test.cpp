// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "scion/interpolation/Histogram.hpp"

// other includes

// convenience typedefs
using namespace njoy::scion;

SCENARIO( "Histogram" ) {

  GIVEN( "Histogram interpolation object" ) {

    WHEN( "interpolating an x,y interval" ) {

      interpolation::Histogram interpolator{};

      THEN( "the interpolation is performed correctly" ) {

        double xLeft = 1.0;
        double xRight = 2.0;
        double yLeft = 1.0;
        double yRight = 4.0;

        CHECK_THAT( 1., WithinRel( interpolator( 1.0, xLeft, xRight, yLeft, yRight ) ) );
        CHECK_THAT( 1., WithinRel( interpolator( 1.5, xLeft, xRight, yLeft, yRight ) ) );
        CHECK_THAT( 1., WithinRel( interpolator( 2.0, xLeft, xRight, yLeft, yRight ) ) );
      } // THEN
    } // WHEN

    WHEN( "interpolating an x,f(y) interval" ) {

      interpolation::Histogram interpolator{};

      THEN( "the interpolation is performed correctly" ) {

        double xLeft = 1.0;
        double xRight = 2.0;
        auto fLeft = [] ( double y ) { return y; };
        auto fRight = [] ( double y ) { return - y; };

        CHECK_THAT(  0.0, WithinRel( interpolator( 1.0,  0.0, xLeft, xRight, fLeft, fRight ) ) );
        CHECK_THAT(  0.0, WithinRel( interpolator( 1.5,  0.0, xLeft, xRight, fLeft, fRight ) ) );
        CHECK_THAT(  0.0, WithinRel( interpolator( 2.0,  0.0, xLeft, xRight, fLeft, fRight ) ) );
        CHECK_THAT(  1.0, WithinRel( interpolator( 1.0,  1.0, xLeft, xRight, fLeft, fRight ) ) );
        CHECK_THAT(  1.0, WithinRel( interpolator( 1.5,  1.0, xLeft, xRight, fLeft, fRight ) ) );
        CHECK_THAT(  1.0, WithinRel( interpolator( 2.0,  1.0, xLeft, xRight, fLeft, fRight ) ) );
        CHECK_THAT( -1.0, WithinRel( interpolator( 1.0, -1.0, xLeft, xRight, fLeft, fRight ) ) );
        CHECK_THAT( -1.0, WithinRel( interpolator( 1.5, -1.0, xLeft, xRight, fLeft, fRight ) ) );
        CHECK_THAT( -1.0, WithinRel( interpolator( 2.0, -1.0, xLeft, xRight, fLeft, fRight ) ) );
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

        CHECK_THAT( 1., WithinRel( interpolation::histogram( 1.0, xLeft, xRight, yLeft, yRight ) ) );
        CHECK_THAT( 1., WithinRel( interpolation::histogram( 1.5, xLeft, xRight, yLeft, yRight ) ) );
        CHECK_THAT( 1., WithinRel( interpolation::histogram( 2.0, xLeft, xRight, yLeft, yRight ) ) );
      } // THEN
    } // WHEN

    WHEN( "interpolating an x,y interval" ) {

      THEN( "the interpolation is performed correctly" ) {

        double xLeft = 1.0;
        double xRight = 2.0;
        auto fLeft = [] ( double y ) { return y; };
        auto fRight = [] ( double y ) { return - y; };

        CHECK_THAT(  0.0, WithinRel( interpolation::histogram( 1.0,  0.0, xLeft, xRight, fLeft, fRight ) ) );
        CHECK_THAT(  0.0, WithinRel( interpolation::histogram( 1.5,  0.0, xLeft, xRight, fLeft, fRight ) ) );
        CHECK_THAT(  0.0, WithinRel( interpolation::histogram( 2.0,  0.0, xLeft, xRight, fLeft, fRight ) ) );
        CHECK_THAT(  1.0, WithinRel( interpolation::histogram( 1.0,  1.0, xLeft, xRight, fLeft, fRight ) ) );
        CHECK_THAT(  1.0, WithinRel( interpolation::histogram( 1.5,  1.0, xLeft, xRight, fLeft, fRight ) ) );
        CHECK_THAT(  1.0, WithinRel( interpolation::histogram( 2.0,  1.0, xLeft, xRight, fLeft, fRight ) ) );
        CHECK_THAT( -1.0, WithinRel( interpolation::histogram( 1.0, -1.0, xLeft, xRight, fLeft, fRight ) ) );
        CHECK_THAT( -1.0, WithinRel( interpolation::histogram( 1.5, -1.0, xLeft, xRight, fLeft, fRight ) ) );
        CHECK_THAT( -1.0, WithinRel( interpolation::histogram( 2.0, -1.0, xLeft, xRight, fLeft, fRight ) ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
