// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "scion/linearisation/RelativeErrorSplit.hpp"

// other includes
#include <cmath>

// convenience typedefs
using namespace Catch;
using namespace njoy::scion;

SCENARIO( "RelativeErrorSplit" ) {

  GIVEN( "a function" ) {

    auto function = [] ( double x ) { return std::exp( x ); };
    auto first = [] ( double x ) { return std::exp( x ); };
    auto second = [] ( double x ) { return std::exp( x ); };

    double xLeft = 0.;
    double xRight = 2.;
    double yLeft = std::exp( xLeft );
    double yRight = std::exp( xRight );

    using Function = decltype( function );
    using First = decltype( first );
    using Second = decltype( second );
    linearisation::RelativeErrorSplit< double, Function, First, Second > chunk( function, first, second );

    WHEN( "the panel is split" ) {

      THEN( "the correct value is returned" ) {

        double slope = ( yRight - yLeft ) / ( xRight - xLeft );
        double intercept = yLeft - slope * xLeft;
        CHECK_THAT( ( slope - intercept ) / slope, WithinRel( chunk( xLeft, xRight, yLeft, yRight ) ) );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "a function for which newton diverges" ) {

    auto function = [] ( double x ) { return x; };
    auto first = [] ( double x ) { return 1.; };
    auto second = [] ( double ) { return 0.; };

    double xLeft = 0.;
    double xRight = 1.;
    double yLeft = 0.;
    double yRight = 1.;

    using Function = decltype( function );
    using First = decltype( first );
    using Second = decltype( second );
    linearisation::RelativeErrorSplit< double, Function, First, Second > chunk( function, first, second );

    WHEN( "panels are split" ) {

      THEN( "the midpoint is returned" ) {

        CHECK_THAT( 0.5, WithinRel( chunk( xLeft, xRight, yLeft, yRight ) ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
