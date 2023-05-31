#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "scion/math/LogLogTable.hpp"

// other includes
#include "utility/IteratorView.hpp"

// convenience typedefs
using namespace njoy::scion;
template < typename X, typename Y = X,
           typename XContainer = std::vector< X >,
           typename YContainer = std::vector< Y > >
using LogLogTable = math::LogLogTable< X, Y, XContainer, YContainer >;
template < typename X > using IntervalDomain = math::IntervalDomain< X >;
using InterpolationType = interpolation::InterpolationType;

SCENARIO( "LogLogTable" ) {

  GIVEN( "tabulated data" ) {

    WHEN( "the data is given explicitly using vectors" ) {

      std::vector< double > x = { 1., 2., 3., 4. };
      std::vector< double > y = { 4., 3., 2., 1. };

      LogLogTable< double > chunk( std::move( x ), std::move( y ) );

      THEN( "a LogLogTable can be constructed and members can be tested" ) {

        CHECK( InterpolationType::LogLog == chunk.interpolation() );
        CHECK( 4 == chunk.numberPoints() );
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
        CHECK( 4. == Approx( chunk( 1. ) ) );
        CHECK( 3. == Approx( chunk( 2. ) ) );
        CHECK( 2. == Approx( chunk( 3. ) ) );
        CHECK( 1. == Approx( chunk( 4. ) ) );

        // values of x outside the x grid
        CHECK( 0. == Approx( chunk( 0. ) ) );
        CHECK( 0. == Approx( chunk( 5. ) ) );

        // values of x inside the x grid
        CHECK( 3.380457775 == Approx( chunk( 1.5 ) ) );
        CHECK( 1.379516838 == Approx( chunk( 3.5 ) ) );
      } // THEN

      THEN( "a LogLogTable can be linearised" ) {

        auto linear = chunk.linearise();

        CHECK( 34 == linear.first.size() );
        CHECK( 34 == linear.second.size() );

        CHECK( 1.     == Approx( linear.first[0] ) );
        CHECK( 1.0625 == Approx( linear.first[1] ) );
        CHECK( 1.125  == Approx( linear.first[2] ) );
        CHECK( 1.25   == Approx( linear.first[3] ) );
        CHECK( 1.375  == Approx( linear.first[4] ) );
        CHECK( 1.5    == Approx( linear.first[5] ) );
        CHECK( 1.625  == Approx( linear.first[6] ) );
        CHECK( 1.75	  == Approx( linear.first[7] ) );
        CHECK( 1.875  == Approx( linear.first[8] ) );
        CHECK( 2.     == Approx( linear.first[9] ) );
        CHECK( 2.125  == Approx( linear.first[10] ) );
        CHECK( 2.25	  == Approx( linear.first[11] ) );
        CHECK( 2.375  == Approx( linear.first[12] ) );
        CHECK( 2.5	  == Approx( linear.first[13] ) );
        CHECK( 2.625  == Approx( linear.first[14] ) );
        CHECK( 2.75   == Approx( linear.first[15] ) );
        CHECK( 2.875  == Approx( linear.first[16] ) );
        CHECK( 3.     == Approx( linear.first[17] ) );
        CHECK( 3.0625 == Approx( linear.first[18] ) );
        CHECK( 3.125  == Approx( linear.first[19] ) );
        CHECK( 3.1875 == Approx( linear.first[20] ) );
        CHECK( 3.25   == Approx( linear.first[21] ) );
        CHECK( 3.3125 == Approx( linear.first[22] ) );
        CHECK( 3.375  == Approx( linear.first[23] ) );
        CHECK( 3.4375 == Approx( linear.first[24] ) );
        CHECK( 3.5    == Approx( linear.first[25] ) );
        CHECK( 3.5625 == Approx( linear.first[26] ) );
        CHECK( 3.625  == Approx( linear.first[27] ) );
        CHECK( 3.6875 == Approx( linear.first[28] ) );
        CHECK( 3.75   == Approx( linear.first[29] ) );
        CHECK( 3.8125 == Approx( linear.first[30] ) );
        CHECK( 3.875  == Approx( linear.first[31] ) );
        CHECK( 3.9375 == Approx( linear.first[32] ) );
        CHECK( 4.     == Approx( linear.first[33] ) );

        CHECK( 4.          == Approx( linear.second[0] ) );
        CHECK( 3.900609682 == Approx( linear.second[1] ) );
        CHECK( 3.809164922 == Approx( linear.second[2] ) );
        CHECK( 3.646185015 == Approx( linear.second[3] ) );
        CHECK( 3.504767277 == Approx( linear.second[4] ) );
        CHECK( 3.380457775 == Approx( linear.second[5] ) );
        CHECK( 3.270001395 == Approx( linear.second[6] ) );
        CHECK( 3.170955062 == Approx( linear.second[7] ) );
        CHECK( 3.08144362  == Approx( linear.second[8] ) );
        CHECK( 3.          == Approx( linear.second[9] ) );
        CHECK( 2.823529412 == Approx( linear.second[10] ) );
        CHECK( 2.666666667 == Approx( linear.second[11] ) );
        CHECK( 2.526315789 == Approx( linear.second[12] ) );
        CHECK( 2.4         == Approx( linear.second[13] ) );
        CHECK( 2.285714286 == Approx( linear.second[14] ) );
        CHECK( 2.181818182 == Approx( linear.second[15] ) );
        CHECK( 2.086956522 == Approx( linear.second[16] ) );
        CHECK( 2.          == Approx( linear.second[17] ) );
        CHECK( 1.903066705 == Approx( linear.second[18] ) );
        CHECK( 1.812649915 == Approx( linear.second[19] ) );
        CHECK( 1.728194036 == Approx( linear.second[20] ) );
        CHECK( 1.64920048  == Approx( linear.second[21] ) );
        CHECK( 1.575220866 == Approx( linear.second[22] ) );
        CHECK( 1.50585114  == Approx( linear.second[23] ) );
        CHECK( 1.440726475 == Approx( linear.second[24] ) );
        CHECK( 1.379516838 == Approx( linear.second[25] ) );
        CHECK( 1.321923126 == Approx( linear.second[26] ) );
        CHECK( 1.267673794 == Approx( linear.second[27] ) );
        CHECK( 1.216521892 == Approx( linear.second[28] ) );
        CHECK( 1.168242471 == Approx( linear.second[29] ) );
        CHECK( 1.122630299 == Approx( linear.second[30] ) );
        CHECK( 1.079497846 == Approx( linear.second[31] ) );
        CHECK( 1.038673501 == Approx( linear.second[32] ) );
        CHECK( 1.          == Approx( linear.second[33] ) );
      } // THEN
    } // WHEN

    WHEN( "the data is given explicitly using iterator views" ) {

      using View = njoy::utility::IteratorView< std::vector< double >::const_iterator >;

      const std::vector< double > xvalues= { 1., 2., 3., 4. };
      const std::vector< double > yvalues = { 4., 3., 2., 1. };

      View x = njoy::utility::make_view( xvalues );
      View y = njoy::utility::make_view( yvalues );

      LogLogTable< double, double, View, View > chunk( std::move( x ), std::move( y ) );

      THEN( "a LogLogTable can be constructed and members can be tested" ) {

        CHECK( InterpolationType::LogLog == chunk.interpolation() );
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
        CHECK( 4. == Approx( chunk( 1. ) ) );
        CHECK( 3. == Approx( chunk( 2. ) ) );
        CHECK( 2. == Approx( chunk( 3. ) ) );
        CHECK( 1. == Approx( chunk( 4. ) ) );

        // values of x outside the x grid
        CHECK( 0. == Approx( chunk( 0. ) ) );
        CHECK( 0. == Approx( chunk( 5. ) ) );

        // values of x inside the x grid
        CHECK( 3.380457775 == Approx( chunk( 1.5 ) ) );
        CHECK( 1.379516838 == Approx( chunk( 3.5 ) ) );
      } // THEN

      THEN( "a LogLogTable can be linearised" ) {

        auto linear = chunk.linearise();

        CHECK( 34 == linear.first.size() );
        CHECK( 34 == linear.second.size() );

        CHECK( 1.     == Approx( linear.first[0] ) );
        CHECK( 1.0625 == Approx( linear.first[1] ) );
        CHECK( 1.125  == Approx( linear.first[2] ) );
        CHECK( 1.25   == Approx( linear.first[3] ) );
        CHECK( 1.375  == Approx( linear.first[4] ) );
        CHECK( 1.5    == Approx( linear.first[5] ) );
        CHECK( 1.625  == Approx( linear.first[6] ) );
        CHECK( 1.75	  == Approx( linear.first[7] ) );
        CHECK( 1.875  == Approx( linear.first[8] ) );
        CHECK( 2.     == Approx( linear.first[9] ) );
        CHECK( 2.125  == Approx( linear.first[10] ) );
        CHECK( 2.25	  == Approx( linear.first[11] ) );
        CHECK( 2.375  == Approx( linear.first[12] ) );
        CHECK( 2.5	  == Approx( linear.first[13] ) );
        CHECK( 2.625  == Approx( linear.first[14] ) );
        CHECK( 2.75   == Approx( linear.first[15] ) );
        CHECK( 2.875  == Approx( linear.first[16] ) );
        CHECK( 3.     == Approx( linear.first[17] ) );
        CHECK( 3.0625 == Approx( linear.first[18] ) );
        CHECK( 3.125  == Approx( linear.first[19] ) );
        CHECK( 3.1875 == Approx( linear.first[20] ) );
        CHECK( 3.25   == Approx( linear.first[21] ) );
        CHECK( 3.3125 == Approx( linear.first[22] ) );
        CHECK( 3.375  == Approx( linear.first[23] ) );
        CHECK( 3.4375 == Approx( linear.first[24] ) );
        CHECK( 3.5    == Approx( linear.first[25] ) );
        CHECK( 3.5625 == Approx( linear.first[26] ) );
        CHECK( 3.625  == Approx( linear.first[27] ) );
        CHECK( 3.6875 == Approx( linear.first[28] ) );
        CHECK( 3.75   == Approx( linear.first[29] ) );
        CHECK( 3.8125 == Approx( linear.first[30] ) );
        CHECK( 3.875  == Approx( linear.first[31] ) );
        CHECK( 3.9375 == Approx( linear.first[32] ) );
        CHECK( 4.     == Approx( linear.first[33] ) );

        CHECK( 4.          == Approx( linear.second[0] ) );
        CHECK( 3.900609682 == Approx( linear.second[1] ) );
        CHECK( 3.809164922 == Approx( linear.second[2] ) );
        CHECK( 3.646185015 == Approx( linear.second[3] ) );
        CHECK( 3.504767277 == Approx( linear.second[4] ) );
        CHECK( 3.380457775 == Approx( linear.second[5] ) );
        CHECK( 3.270001395 == Approx( linear.second[6] ) );
        CHECK( 3.170955062 == Approx( linear.second[7] ) );
        CHECK( 3.08144362  == Approx( linear.second[8] ) );
        CHECK( 3.          == Approx( linear.second[9] ) );
        CHECK( 2.823529412 == Approx( linear.second[10] ) );
        CHECK( 2.666666667 == Approx( linear.second[11] ) );
        CHECK( 2.526315789 == Approx( linear.second[12] ) );
        CHECK( 2.4         == Approx( linear.second[13] ) );
        CHECK( 2.285714286 == Approx( linear.second[14] ) );
        CHECK( 2.181818182 == Approx( linear.second[15] ) );
        CHECK( 2.086956522 == Approx( linear.second[16] ) );
        CHECK( 2.          == Approx( linear.second[17] ) );
        CHECK( 1.903066705 == Approx( linear.second[18] ) );
        CHECK( 1.812649915 == Approx( linear.second[19] ) );
        CHECK( 1.728194036 == Approx( linear.second[20] ) );
        CHECK( 1.64920048  == Approx( linear.second[21] ) );
        CHECK( 1.575220866 == Approx( linear.second[22] ) );
        CHECK( 1.50585114  == Approx( linear.second[23] ) );
        CHECK( 1.440726475 == Approx( linear.second[24] ) );
        CHECK( 1.379516838 == Approx( linear.second[25] ) );
        CHECK( 1.321923126 == Approx( linear.second[26] ) );
        CHECK( 1.267673794 == Approx( linear.second[27] ) );
        CHECK( 1.216521892 == Approx( linear.second[28] ) );
        CHECK( 1.168242471 == Approx( linear.second[29] ) );
        CHECK( 1.122630299 == Approx( linear.second[30] ) );
        CHECK( 1.079497846 == Approx( linear.second[31] ) );
        CHECK( 1.038673501 == Approx( linear.second[32] ) );
        CHECK( 1.          == Approx( linear.second[33] ) );
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

    WHEN( "the x grid has a duplicate point" ) {

      std::vector< double > x = { 1., 2., 2., 4. };
      std::vector< double > y = { 4., 3., 2., 1. };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( LogLogTable< double >( std::move( x ), std::move( y ) ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
