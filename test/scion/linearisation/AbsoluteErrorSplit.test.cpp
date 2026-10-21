// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "scion/linearisation/AbsoluteErrorSplit.hpp"

// other includes
#include <cmath>

// convenience typedefs
using namespace Catch;
using namespace njoy::scion;

SCENARIO( "AbsoluteErrorSplit" ) {

  GIVEN( "a function" ) {

    auto first = [] ( double x ) { return std::exp( x ); };
    auto second = [] ( double x ) { return std::exp( x ); };

    double xLeft = 0.;
    double xRight = 2.;
    double yLeft = std::exp( xLeft );
    double yRight = std::exp( xRight );

    using First = decltype( first );
    using Second = decltype( second );
    linearisation::AbsoluteErrorSplit< double, First, Second > chunk( first, second );

    WHEN( "panels are split" ) {

      THEN( "the correct value is returned" ) {

        double slope = ( yRight - yLeft ) / ( xRight - xLeft );
        CHECK_THAT( std::log( slope ), WithinRel( chunk( xLeft, xRight, yLeft, yRight ) ) );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "a function for which newton diverges" ) {

    auto first = [] ( double x ) { return 1.; };
    auto second = [] ( double ) { return 0.; };

    double xLeft = 0.;
    double xRight = 1.;
    double yLeft = 0.;
    double yRight = 1.;

    using First = decltype( first );
    using Second = decltype( second );
    linearisation::AbsoluteErrorSplit< double, First, Second > chunk( first, second );

    WHEN( "panels are split" ) {

      THEN( "the midpoint is returned" ) {

        CHECK_THAT( 0.5, WithinRel( chunk( xLeft, xRight, yLeft, yRight ) ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
