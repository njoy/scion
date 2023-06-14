#include <catch2/catch_test_macros.hpp>

// what we are testing
#include "scion/linearisation/ToleranceConvergence.hpp"

// other includes

// convenience typedefs
using namespace Catch;
using namespace njoy::scion;

SCENARIO( "ToleranceConvergence" ) {

  GIVEN( "the default tolerance and threshold are used" ) {

    double xLeft = 0.;
    double xRight = 2.;
    double yLeft = 1.;
    double yRight = 3.;

    linearisation::ToleranceConvergence< double > chunk;

    WHEN( "values are compared" ) {

      THEN( "the values are compared correctly" ) {

        CHECK( false == chunk( 1.000, 2., xLeft, xRight, yLeft, yRight ) );
        CHECK( false == chunk( 1.900, 2., xLeft, xRight, yLeft, yRight ) );
        CHECK( false == chunk( 1.990, 2., xLeft, xRight, yLeft, yRight ) );
        CHECK( true == chunk( 1.999, 2., xLeft, xRight, yLeft, yRight ) );
        CHECK( true == chunk( 2.000, 2., xLeft, xRight, yLeft, yRight ) );
        CHECK( true == chunk( 2.001, 2., xLeft, xRight, yLeft, yRight ) );
        CHECK( false == chunk( 2.010, 2., xLeft, xRight, yLeft, yRight ) );
        CHECK( false == chunk( 2.100, 2., xLeft, xRight, yLeft, yRight ) );
        CHECK( false == chunk( 3.000, 2., xLeft, xRight, yLeft, yRight ) );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "a user defined tolerance and default threshold" ) {

    double xLeft = 0.;
    double xRight = 2.;
    double yLeft = 1.;
    double yRight = 3.;

    linearisation::ToleranceConvergence< double > chunk( 0.01 );

    WHEN( "values are compared" ) {

      THEN( "the values are compared correctly" ) {

        CHECK( false == chunk( 1.000, 2., xLeft, xRight, yLeft, yRight ) );
        CHECK( false == chunk( 1.900, 2., xLeft, xRight, yLeft, yRight ) );
        CHECK( true == chunk( 1.990, 2., xLeft, xRight, yLeft, yRight ) );
        CHECK( true == chunk( 1.999, 2., xLeft, xRight, yLeft, yRight ) );
        CHECK( true == chunk( 2.000, 2., xLeft, xRight, yLeft, yRight ) );
        CHECK( true == chunk( 2.001, 2., xLeft, xRight, yLeft, yRight ) );
        CHECK( true == chunk( 2.010, 2., xLeft, xRight, yLeft, yRight ) );
        CHECK( false == chunk( 2.100, 2., xLeft, xRight, yLeft, yRight ) );
        CHECK( false == chunk( 3.000, 2., xLeft, xRight, yLeft, yRight ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
