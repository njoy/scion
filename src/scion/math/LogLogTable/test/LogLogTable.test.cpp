#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "scion/math/LogLogTable.hpp"

// other includes
#include "scion/linearisation/ToleranceConvergence.hpp"

// convenience typedefs
using namespace njoy::scion;
template < typename X, typename Y = X > using LinearLinearTable = math::LinearLinearTable< X, Y >;
template < typename X, typename Y = X > using LogLogTable = math::LogLogTable< X, Y >;
template < typename X > using IntervalDomain = math::IntervalDomain< X >;

SCENARIO( "LogLogTable" ) {

  GIVEN( "tabulated data" ) {

    WHEN( "the data is given explicitly" ) {

      std::vector< double > x = { 1., 2., 3., 4. };
      std::vector< double > y = { 4., 3., 2., 1. };

      LogLogTable< double > chunk( std::move( x ), std::move( y ) );

      THEN( "a LogLogTable can be constructed and members can be tested" ) {

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

      THEN( "a LogLogTable can be evaluated" ) {

        // values of x in the x grid
        CHECK( 4. == Approx( chunk.evaluate( 1. ) ) );
        CHECK( 3. == Approx( chunk.evaluate( 2. ) ) );
        CHECK( 2. == Approx( chunk.evaluate( 3. ) ) );
        CHECK( 1. == Approx( chunk.evaluate( 4. ) ) );

        // values of x outside the x grid
        CHECK( 0. == Approx( chunk.evaluate( 0. ) ) );
        CHECK( 0. == Approx( chunk.evaluate( 5. ) ) );

        // values of x inside the x grid
        CHECK( 3.380457775 == Approx( chunk.evaluate( 1.5 ) ) );
        CHECK( 1.379516838 == Approx( chunk.evaluate( 3.5 ) ) );
      } // THEN

      THEN( "a LogLogTable can be linearised" ) {

        LinearLinearTable< double > linear = chunk.linearise();

        CHECK( 34 == linear.x().size() );
        CHECK( 34 == linear.y().size() );

        CHECK( 1.     == Approx( linear.x()[0] ) );
        CHECK( 1.0625 == Approx( linear.x()[1] ) );
        CHECK( 1.125  == Approx( linear.x()[2] ) );
        CHECK( 1.25   == Approx( linear.x()[3] ) );
        CHECK( 1.375  == Approx( linear.x()[4] ) );
        CHECK( 1.5    == Approx( linear.x()[5] ) );
        CHECK( 1.625  == Approx( linear.x()[6] ) );
        CHECK( 1.75	  == Approx( linear.x()[7] ) );
        CHECK( 1.875  == Approx( linear.x()[8] ) );
        CHECK( 2.     == Approx( linear.x()[9] ) );
        CHECK( 2.125  == Approx( linear.x()[10] ) );
        CHECK( 2.25	  == Approx( linear.x()[11] ) );
        CHECK( 2.375  == Approx( linear.x()[12] ) );
        CHECK( 2.5	  == Approx( linear.x()[13] ) );
        CHECK( 2.625  == Approx( linear.x()[14] ) );
        CHECK( 2.75   == Approx( linear.x()[15] ) );
        CHECK( 2.875  == Approx( linear.x()[16] ) );
        CHECK( 3.     == Approx( linear.x()[17] ) );
        CHECK( 3.0625 == Approx( linear.x()[18] ) );
        CHECK( 3.125  == Approx( linear.x()[19] ) );
        CHECK( 3.1875 == Approx( linear.x()[20] ) );
        CHECK( 3.25   == Approx( linear.x()[21] ) );
        CHECK( 3.3125 == Approx( linear.x()[22] ) );
        CHECK( 3.375  == Approx( linear.x()[23] ) );
        CHECK( 3.4375 == Approx( linear.x()[24] ) );
        CHECK( 3.5    == Approx( linear.x()[25] ) );
        CHECK( 3.5625 == Approx( linear.x()[26] ) );
        CHECK( 3.625  == Approx( linear.x()[27] ) );
        CHECK( 3.6875 == Approx( linear.x()[28] ) );
        CHECK( 3.75   == Approx( linear.x()[29] ) );
        CHECK( 3.8125 == Approx( linear.x()[30] ) );
        CHECK( 3.875  == Approx( linear.x()[31] ) );
        CHECK( 3.9375 == Approx( linear.x()[32] ) );
        CHECK( 4.     == Approx( linear.x()[33] ) );

        CHECK( 4.          == Approx( linear.y()[0] ) );
        CHECK( 3.900609682 == Approx( linear.y()[1] ) );
        CHECK( 3.809164922 == Approx( linear.y()[2] ) );
        CHECK( 3.646185015 == Approx( linear.y()[3] ) );
        CHECK( 3.504767277 == Approx( linear.y()[4] ) );
        CHECK( 3.380457775 == Approx( linear.y()[5] ) );
        CHECK( 3.270001395 == Approx( linear.y()[6] ) );
        CHECK( 3.170955062 == Approx( linear.y()[7] ) );
        CHECK( 3.08144362  == Approx( linear.y()[8] ) );
        CHECK( 3.          == Approx( linear.y()[9] ) );
        CHECK( 2.823529412 == Approx( linear.y()[10] ) );
        CHECK( 2.666666667 == Approx( linear.y()[11] ) );
        CHECK( 2.526315789 == Approx( linear.y()[12] ) );
        CHECK( 2.4         == Approx( linear.y()[13] ) );
        CHECK( 2.285714286 == Approx( linear.y()[14] ) );
        CHECK( 2.181818182 == Approx( linear.y()[15] ) );
        CHECK( 2.086956522 == Approx( linear.y()[16] ) );
        CHECK( 2.          == Approx( linear.y()[17] ) );
        CHECK( 1.903066705 == Approx( linear.y()[18] ) );
        CHECK( 1.812649915 == Approx( linear.y()[19] ) );
        CHECK( 1.728194036 == Approx( linear.y()[20] ) );
        CHECK( 1.64920048  == Approx( linear.y()[21] ) );
        CHECK( 1.575220866 == Approx( linear.y()[22] ) );
        CHECK( 1.50585114  == Approx( linear.y()[23] ) );
        CHECK( 1.440726475 == Approx( linear.y()[24] ) );
        CHECK( 1.379516838 == Approx( linear.y()[25] ) );
        CHECK( 1.321923126 == Approx( linear.y()[26] ) );
        CHECK( 1.267673794 == Approx( linear.y()[27] ) );
        CHECK( 1.216521892 == Approx( linear.y()[28] ) );
        CHECK( 1.168242471 == Approx( linear.y()[29] ) );
        CHECK( 1.122630299 == Approx( linear.y()[30] ) );
        CHECK( 1.079497846 == Approx( linear.y()[31] ) );
        CHECK( 1.038673501 == Approx( linear.y()[32] ) );
        CHECK( 1.          == Approx( linear.y()[33] ) );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "invalid data for a LogLogTable object" ) {

    WHEN( "there are not enough values in the x or y grid" ) {

      std::vector< double > empty = {};
      std::vector< double > one = { 1. };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( LogLogTable< double >( empty, empty ) );
        CHECK_THROWS( LogLogTable< double >( one, one ) );
      } // THEN
    } // WHEN

    WHEN( "the x and y grid do not have the same number of points" ) {

      std::vector< double > x = { 1., 2., 3., 4. };
      std::vector< double > y = { 4., 3., 2. };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( LogLogTable< double >( std::move( x ), std::move( y ) ) );
      } // THEN
    } // WHEN

    WHEN( "the x grid is not sorted" ) {

      std::vector< double > x = { 1., 3., 2., 4. };
      std::vector< double > y = { 4., 3., 2., 1. };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( LogLogTable< double >( std::move( x ), std::move( y ) ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
