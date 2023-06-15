// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "scion/linearisation/Lineariser.hpp"

// other includes
#include <cmath>
#include "scion/linearisation/ToleranceConvergence.hpp"
#include "scion/linearisation/MidpointSplit.hpp"

// convenience typedefs
using namespace njoy::scion;

SCENARIO( "Lineariser" ) {

  GIVEN( "valid data for linearisation" ) {

    // y = f(x) = exp(x)
    auto functor = [] ( double x ) { return std::exp( x ); };

    // split a panel using the midpoint
    linearisation::MidpointSplit< double > split;

    // convergence tolerance < 25%
    linearisation::ToleranceConvergence< double > convergence( 0.25 );

    WHEN( "the minimal grid is used" ) {

      std::vector< double > grid = { 0., 10. };

      THEN( "the function can be linearised" ) {

        std::vector< double > x;
        std::vector< double > y;

        linearisation::Lineariser linearise( x, y );
        linearise( grid.begin(), grid.end(), functor, convergence, split );

        CHECK( 9 == x.size() );
        CHECK( 9 == y.size() );

        CHECK_THAT(  0.0 , WithinRel( x[0] ) );
        CHECK_THAT(  1.25, WithinRel( x[1] ) );
        CHECK_THAT(  2.5 , WithinRel( x[2] ) );
        CHECK_THAT(  3.75, WithinRel( x[3] ) );
        CHECK_THAT(  5.0 , WithinRel( x[4] ) );
        CHECK_THAT(  6.25, WithinRel( x[5] ) );
        CHECK_THAT(  7.5 , WithinRel( x[6] ) );
        CHECK_THAT(  8.75, WithinRel( x[7] ) );
        CHECK_THAT( 10.0 , WithinRel( x[8] ) );

        CHECK_THAT( std::exp( 0.0  ), WithinRel( y[0] ) );
        CHECK_THAT( std::exp( 1.25 ), WithinRel( y[1] ) );
        CHECK_THAT( std::exp( 2.5  ), WithinRel( y[2] ) );
        CHECK_THAT( std::exp( 3.75 ), WithinRel( y[3] ) );
        CHECK_THAT( std::exp( 5.0  ), WithinRel( y[4] ) );
        CHECK_THAT( std::exp( 6.25 ), WithinRel( y[5] ) );
        CHECK_THAT( std::exp( 7.5  ), WithinRel( y[6] ) );
        CHECK_THAT( std::exp( 8.75 ), WithinRel( y[7] ) );
        CHECK_THAT( std::exp(10.0  ), WithinRel( y[8] ) );
      } // THEN
    } // WHEN

    WHEN( "an extended grid is used" ) {

      std::vector< double > grid = { 0., 2., 4., 6., 8., 10. };

      THEN( "the function can be linearised" ) {

        std::vector< double > x;
        std::vector< double > y;

        linearisation::Lineariser linearise( x, y );
        linearise( grid.begin(), grid.end(), functor, convergence, split );

        CHECK( 11 == x.size() );
        CHECK( 11 == y.size() );

        CHECK_THAT(  0.0, WithinRel( x[ 0] ) );
        CHECK_THAT(  1.0, WithinRel( x[ 1] ) );
        CHECK_THAT(  2.0, WithinRel( x[ 2] ) );
        CHECK_THAT(  3.0, WithinRel( x[ 3] ) );
        CHECK_THAT(  4.0, WithinRel( x[ 4] ) );
        CHECK_THAT(  5.0, WithinRel( x[ 5] ) );
        CHECK_THAT(  6.0, WithinRel( x[ 6] ) );
        CHECK_THAT(  7.0, WithinRel( x[ 7] ) );
        CHECK_THAT(  8.0, WithinRel( x[ 8] ) );
        CHECK_THAT(  9.0, WithinRel( x[ 9] ) );
        CHECK_THAT( 10.0, WithinRel( x[10] ) );

        CHECK_THAT( 1.0             , WithinRel( y[ 0] ) );
        CHECK_THAT( std::exp(  1.0 ), WithinRel( y[ 1] ) );
        CHECK_THAT( std::exp(  2.0 ), WithinRel( y[ 2] ) );
        CHECK_THAT( std::exp(  3.0 ), WithinRel( y[ 3] ) );
        CHECK_THAT( std::exp(  4.0 ), WithinRel( y[ 4] ) );
        CHECK_THAT( std::exp(  5.0 ), WithinRel( y[ 5] ) );
        CHECK_THAT( std::exp(  6.0 ), WithinRel( y[ 6] ) );
        CHECK_THAT( std::exp(  7.0 ), WithinRel( y[ 7] ) );
        CHECK_THAT( std::exp(  8.0 ), WithinRel( y[ 8] ) );
        CHECK_THAT( std::exp(  9.0 ), WithinRel( y[ 9] ) );
        CHECK_THAT( std::exp( 10.0 ), WithinRel( y[10] ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
