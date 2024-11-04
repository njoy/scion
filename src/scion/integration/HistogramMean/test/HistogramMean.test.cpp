// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "scion/integration/HistogramMean.hpp"

// other includes

// convenience typedefs
using namespace njoy::scion;

SCENARIO( "HistogramMean" ) {

  GIVEN( "HistogramMean integration object" ) {

    WHEN( "integrating an interval" ) {

      integration::HistogramMean integrator{};

      THEN( "the integration is performed correctly" ) {

        double xLeft = 1.0;
        double xRight = 2.0;
        double yLeft = 1.0;
        double yRight = 4.0;

        // both y values are the same
        CHECK_THAT( 1.5, WithinRel( integrator( xLeft, xRight, yLeft, yLeft ) ) );

        // the y values are different
        CHECK_THAT( 1.5, WithinRel( integrator( xLeft, xRight, yLeft, yRight ) ) );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "linlin integration function" ) {

    WHEN( "integrating an interval" ) {

      THEN( "the integration is performed correctly" ) {

        double xLeft = 1.0;
        double xRight = 2.0;
        double yLeft = 1.0;
        double yRight = 4.0;

        // both y values are the same
        CHECK_THAT( 1.5, WithinRel( integration::histogramMean( xLeft, xRight, yLeft, yLeft ) ) );

        // the y values are different
        CHECK_THAT( 1.5, WithinRel( integration::histogramMean( xLeft, xRight, yLeft, yRight ) ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
