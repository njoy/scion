#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "scion/math/LinearLinearTable.hpp"

// other includes
#include "scion/linearisation/ToleranceConvergence.hpp"

// convenience typedefs
using namespace njoy::scion;
template < typename X, typename Y = X > using LinearLinearTable = math::LinearLinearTable< X, Y >;
template < typename X > using IntervalDomain = math::IntervalDomain< X >;

SCENARIO( "LinearLinearTable" ) {

  GIVEN( "tabulated data" ) {

    WHEN( "the data is given explicitly" ) {

      std::vector< double > x = { 1., 2., 3., 4. };
      std::vector< double > y = { 4., 3., 2., 1. };

      LinearLinearTable< double > chunk( std::move( x ), std::move( y ) );

      THEN( "a LinearLinearTable can be constructed and members can be tested" ) {

        CHECK( 4 == chunk.x().size() );
        CHECK( 4 == chunk.y().size() );
        CHECK( 1. == Approx( chunk.x()[0] ) );
        CHECK( 2. == Approx( chunk.x()[1] ) );
        CHECK( 3. == Approx( chunk.x()[2] ) );
        CHECK( 4. == Approx( chunk.x()[3] ) );
        CHECK( 4. == Approx( chunk.y()[0] ) );
        CHECK( 3. == Approx( chunk.y()[1] ) );
        CHECK( 2. == Approx( chunk.y()[2] ) );
        CHECK( 1. == Approx( chunk.y()[3] ) );

        CHECK( true == std::holds_alternative< IntervalDomain< double > >( chunk.domain() ) );
      } // THEN

      THEN( "a LinearLinearTable can be evaluated" ) {

        // values of x in the x grid
        CHECK( 4. == Approx( chunk.evaluate( 1. ) ) );
        CHECK( 3. == Approx( chunk.evaluate( 2. ) ) );
        CHECK( 2. == Approx( chunk.evaluate( 3. ) ) );
        CHECK( 1. == Approx( chunk.evaluate( 4. ) ) );

        // values of x outside the x grid
        CHECK( 0. == Approx( chunk.evaluate( 0. ) ) );
        CHECK( 0. == Approx( chunk.evaluate( 5. ) ) );

        // values of x inside the x grid
        CHECK( 3.5 == Approx( chunk.evaluate( 1.5 ) ) );
        CHECK( 1.5 == Approx( chunk.evaluate( 3.5 ) ) );
      } // THEN

      THEN( "a LinearLinearTable can be linearised" ) {

        LinearLinearTable< double > linear = chunk.linearise();
        CHECK( linear.x() == chunk.x() );
        CHECK( linear.y() == chunk.y() );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "invalid data for a LinearLinearTable object" ) {

    WHEN( "there are not enough values in the x or y grid" ) {

      std::vector< double > empty = {};
      std::vector< double > one = { 1. };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( LinearLinearTable< double >( empty, empty ) );
        CHECK_THROWS( LinearLinearTable< double >( one, one ) );
      } // THEN
    } // WHEN

    WHEN( "the x and y grid do not have the same number of points" ) {

      std::vector< double > x = { 1., 2., 3., 4. };
      std::vector< double > y = { 4., 3., 2. };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( LinearLinearTable< double >( std::move( x ), std::move( y ) ) );
      } // THEN
    } // WHEN

    WHEN( "the x grid is not sorted" ) {

      std::vector< double > x = { 1., 3., 2., 4. };
      std::vector< double > y = { 4., 3., 2., 1. };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( LinearLinearTable< double >( std::move( x ), std::move( y ) ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
