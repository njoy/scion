// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "scion/integration/FirstMomentLogarithmicLogarithmic.hpp"
#include "scion/integration.hpp"

// other includes
#include <iostream>
#include <iomanip>
// convenience typedefs
using namespace njoy::scion;

SCENARIO( "FirstMomentLogarithmicLogarithmic" ) {

  GIVEN( "FirstMomentLogarithmicLogarithmic integration object" ) {

    WHEN( "integrating an interval" ) {

      integration::FirstMomentLogarithmicLogarithmic integrator{};

      THEN( "the integration is performed correctly" ) {

        double xLeft = 1.0;
        double xRight = 2.0;
        double yLeft = 1.0;
        double yRight = 4.0;

        // both y values are the same
        CHECK_THAT( 1.5, WithinRel( integrator( xLeft, xRight, yLeft, yLeft ) ) );

        // the y values are different
        // this value was calculated using Wolfram Alpha using this command:
        // "integrate x exp( ln(4) (x-1) ) dx between 1 and 2"
        // it was verified using Gauss-Legendre 64 quadrature as well
        CHECK_THAT( 3.75, WithinRel( integrator( xLeft, xRight, yLeft, yRight ) ) );
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
        CHECK_THAT( 1.5, WithinRel( integration::firstMomentLogLog( xLeft, xRight, yLeft, yLeft ) ) );

        // the y values are different
        // this value was calculated using Wolfram Alpha using this command:
        // "integrate x exp( ln(4) (x-1) ) dx between 1 and 2"
        // it was verified using Gauss-Legendre 64 quadrature as well
        CHECK_THAT( 3.75, WithinRel( integration::firstMomentLogLog( xLeft, xRight, yLeft, yRight ) ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
