#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "scion/math/LinearLogTable.hpp"

// other includes
#include "utility/IteratorView.hpp"

// convenience typedefs
using namespace njoy::scion;
template < typename X, typename Y = X > using LinearLinearTable = math::LinearLinearTable< X, Y >;
template < typename X, typename Y = X,
           typename XContainer = std::vector< X >,
           typename YContainer = std::vector< Y > >
using LinearLogTable = math::LinearLogTable< X, Y, XContainer, YContainer >;
template < typename X > using IntervalDomain = math::IntervalDomain< X >;
using InterpolationType = interpolation::InterpolationType;

SCENARIO( "LinearLogTable" ) {

  GIVEN( "tabulated data" ) {

    WHEN( "the data is given explicitly using vectors" ) {

      std::vector< double > x = { 1., 2., 3., 4. };
      std::vector< double > y = { 4., 3., 2., 1. };

      LinearLogTable< double > chunk( std::move( x ), std::move( y ) );

      THEN( "a LinearLogTable can be constructed and members can be tested" ) {

        CHECK( InterpolationType::LinearLog == chunk.interpolation() );
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

      THEN( "a LinearLogTable can be evaluated" ) {

        // values of x in the x grid
        CHECK( 4. == Approx( chunk( 1. ) ) );
        CHECK( 3. == Approx( chunk( 2. ) ) );
        CHECK( 2. == Approx( chunk( 3. ) ) );
        CHECK( 1. == Approx( chunk( 4. ) ) );

        // values of x outside the x grid
        CHECK( 0. == Approx( chunk( 0. ) ) );
        CHECK( 0. == Approx( chunk( 5. ) ) );

        // values of x inside the x grid
        CHECK( 3.415037499 == Approx( chunk( 1.5 ) ) );
        CHECK( 1.464163065 == Approx( chunk( 3.5 ) ) );
      } // THEN

      THEN( "a LinearLogTable can be linearised" ) {

        LinearLinearTable< double > linear = chunk.linearise();

        CHECK( 25 == linear.x().size() );
        CHECK( 25 == linear.y().size() );

        CHECK( 1.    == Approx( linear.x()[0] ) );
        CHECK( 1.125 == Approx( linear.x()[1] ) );
        CHECK( 1.25  == Approx( linear.x()[2] ) );
        CHECK( 1.375 == Approx( linear.x()[3] ) );
        CHECK( 1.5   == Approx( linear.x()[4] ) );
        CHECK( 1.625 == Approx( linear.x()[5] ) );
        CHECK( 1.75  == Approx( linear.x()[6] ) );
        CHECK( 1.875 == Approx( linear.x()[7] ) );
        CHECK( 2     == Approx( linear.x()[8] ) );
        CHECK( 2.125 == Approx( linear.x()[9] ) );
        CHECK( 2.25  == Approx( linear.x()[10] ) );
        CHECK( 2.375 == Approx( linear.x()[11] ) );
        CHECK( 2.5   == Approx( linear.x()[12] ) );
        CHECK( 2.625 == Approx( linear.x()[13] ) );
        CHECK( 2.75  == Approx( linear.x()[14] ) );
        CHECK( 2.875 == Approx( linear.x()[15] ) );
        CHECK( 3.    == Approx( linear.x()[16] ) );
        CHECK( 3.125 == Approx( linear.x()[17] ) );
        CHECK( 3.25  == Approx( linear.x()[18] ) );
        CHECK( 3.375 == Approx( linear.x()[19] ) );
        CHECK( 3.5   == Approx( linear.x()[20] ) );
        CHECK( 3.625 == Approx( linear.x()[21] ) );
        CHECK( 3.75  == Approx( linear.x()[22] ) );
        CHECK( 3.875 == Approx( linear.x()[23] ) );
        CHECK( 4.    == Approx( linear.x()[24] ) );

        CHECK( 4.          == Approx( linear.y()[0] ) );
        CHECK( 3.830074999 == Approx( linear.y()[1] ) );
        CHECK( 3.678071905 == Approx( linear.y()[2] ) );
        CHECK( 3.540568381 == Approx( linear.y()[3] ) );
        CHECK( 3.415037499 == Approx( linear.y()[4] ) );
        CHECK( 3.299560282 == Approx( linear.y()[5] ) );
        CHECK( 3.192645078 == Approx( linear.y()[6] ) );
        CHECK( 3.093109404 == Approx( linear.y()[7] ) );
        CHECK( 3.          == Approx( linear.y()[8] ) );
        CHECK( 2.850481285 == Approx( linear.y()[9] ) );
        CHECK( 2.709511291 == Approx( linear.y()[10] ) );
        CHECK( 2.576165116 == Approx( linear.y()[11] ) );
        CHECK( 2.449660287 == Approx( linear.y()[12] ) );
        CHECK( 2.329328936 == Approx( linear.y()[13] ) );
        CHECK( 2.21459646  == Approx( linear.y()[14] ) );
        CHECK( 2.104964924 == Approx( linear.y()[15] ) );
        CHECK( 2.          == Approx( linear.y()[16] ) );
        CHECK( 1.858100318 == Approx( linear.y()[17] ) );
        CHECK( 1.721766786 == Approx( linear.y()[18] ) );
        CHECK( 1.59057916  == Approx( linear.y()[19] ) );
        CHECK( 1.464163065 == Approx( linear.y()[20] ) );
        CHECK( 1.34218355  == Approx( linear.y()[21] ) );
        CHECK( 1.224339739 == Approx( linear.y()[22] ) );
        CHECK( 1.110360364 == Approx( linear.y()[23] ) );
        CHECK( 1.          == Approx( linear.y()[24] ) );
      } // THEN
    } // WHEN

    WHEN( "the data is given explicitly using iterator views" ) {

      using View = njoy::utility::IteratorView< std::vector< double >::const_iterator >;

      const std::vector< double > xvalues= { 1., 2., 3., 4. };
      const std::vector< double > yvalues = { 4., 3., 2., 1. };

      View x = njoy::utility::make_view( xvalues );
      View y = njoy::utility::make_view( yvalues );

      LinearLogTable< double, double, View, View > chunk( std::move( x ), std::move( y ) );

      THEN( "a LinearLogTable can be constructed and members can be tested" ) {

        CHECK( InterpolationType::LinearLog == chunk.interpolation() );
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

      THEN( "a LinearLogTable can be evaluated" ) {

        // values of x in the x grid
        CHECK( 4. == Approx( chunk( 1. ) ) );
        CHECK( 3. == Approx( chunk( 2. ) ) );
        CHECK( 2. == Approx( chunk( 3. ) ) );
        CHECK( 1. == Approx( chunk( 4. ) ) );

        // values of x outside the x grid
        CHECK( 0. == Approx( chunk( 0. ) ) );
        CHECK( 0. == Approx( chunk( 5. ) ) );

        // values of x inside the x grid
        CHECK( 3.415037499 == Approx( chunk( 1.5 ) ) );
        CHECK( 1.464163065 == Approx( chunk( 3.5 ) ) );
      } // THEN

      THEN( "a LinearLogTable can be linearised" ) {

        LinearLinearTable< double > linear = chunk.linearise();

        CHECK( 25 == linear.x().size() );
        CHECK( 25 == linear.y().size() );

        CHECK( 1.    == Approx( linear.x()[0] ) );
        CHECK( 1.125 == Approx( linear.x()[1] ) );
        CHECK( 1.25  == Approx( linear.x()[2] ) );
        CHECK( 1.375 == Approx( linear.x()[3] ) );
        CHECK( 1.5   == Approx( linear.x()[4] ) );
        CHECK( 1.625 == Approx( linear.x()[5] ) );
        CHECK( 1.75  == Approx( linear.x()[6] ) );
        CHECK( 1.875 == Approx( linear.x()[7] ) );
        CHECK( 2     == Approx( linear.x()[8] ) );
        CHECK( 2.125 == Approx( linear.x()[9] ) );
        CHECK( 2.25  == Approx( linear.x()[10] ) );
        CHECK( 2.375 == Approx( linear.x()[11] ) );
        CHECK( 2.5   == Approx( linear.x()[12] ) );
        CHECK( 2.625 == Approx( linear.x()[13] ) );
        CHECK( 2.75  == Approx( linear.x()[14] ) );
        CHECK( 2.875 == Approx( linear.x()[15] ) );
        CHECK( 3.    == Approx( linear.x()[16] ) );
        CHECK( 3.125 == Approx( linear.x()[17] ) );
        CHECK( 3.25  == Approx( linear.x()[18] ) );
        CHECK( 3.375 == Approx( linear.x()[19] ) );
        CHECK( 3.5   == Approx( linear.x()[20] ) );
        CHECK( 3.625 == Approx( linear.x()[21] ) );
        CHECK( 3.75  == Approx( linear.x()[22] ) );
        CHECK( 3.875 == Approx( linear.x()[23] ) );
        CHECK( 4.    == Approx( linear.x()[24] ) );

        CHECK( 4.          == Approx( linear.y()[0] ) );
        CHECK( 3.830074999 == Approx( linear.y()[1] ) );
        CHECK( 3.678071905 == Approx( linear.y()[2] ) );
        CHECK( 3.540568381 == Approx( linear.y()[3] ) );
        CHECK( 3.415037499 == Approx( linear.y()[4] ) );
        CHECK( 3.299560282 == Approx( linear.y()[5] ) );
        CHECK( 3.192645078 == Approx( linear.y()[6] ) );
        CHECK( 3.093109404 == Approx( linear.y()[7] ) );
        CHECK( 3.          == Approx( linear.y()[8] ) );
        CHECK( 2.850481285 == Approx( linear.y()[9] ) );
        CHECK( 2.709511291 == Approx( linear.y()[10] ) );
        CHECK( 2.576165116 == Approx( linear.y()[11] ) );
        CHECK( 2.449660287 == Approx( linear.y()[12] ) );
        CHECK( 2.329328936 == Approx( linear.y()[13] ) );
        CHECK( 2.21459646  == Approx( linear.y()[14] ) );
        CHECK( 2.104964924 == Approx( linear.y()[15] ) );
        CHECK( 2.          == Approx( linear.y()[16] ) );
        CHECK( 1.858100318 == Approx( linear.y()[17] ) );
        CHECK( 1.721766786 == Approx( linear.y()[18] ) );
        CHECK( 1.59057916  == Approx( linear.y()[19] ) );
        CHECK( 1.464163065 == Approx( linear.y()[20] ) );
        CHECK( 1.34218355  == Approx( linear.y()[21] ) );
        CHECK( 1.224339739 == Approx( linear.y()[22] ) );
        CHECK( 1.110360364 == Approx( linear.y()[23] ) );
        CHECK( 1.          == Approx( linear.y()[24] ) );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "invalid data for a LinearLogTable object" ) {

    WHEN( "there are not enough values in the x or y grid" ) {

      std::vector< double > empty = {};
      std::vector< double > one = { 1. };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( LinearLogTable< double >( empty, empty ) );
        CHECK_THROWS( LinearLogTable< double >( one, one ) );
      } // THEN
    } // WHEN

    WHEN( "the x and y grid do not have the same number of points" ) {

      std::vector< double > x = { 1., 2., 3., 4. };
      std::vector< double > y = { 4., 3., 2. };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( LinearLogTable< double >( std::move( x ), std::move( y ) ) );
      } // THEN
    } // WHEN

    WHEN( "the x grid is not sorted" ) {

      std::vector< double > x = { 1., 3., 2., 4. };
      std::vector< double > y = { 4., 3., 2., 1. };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( LinearLogTable< double >( std::move( x ), std::move( y ) ) );
      } // THEN
    } // WHEN

    WHEN( "the x grid has a duplicate point" ) {

      std::vector< double > x = { 1., 2., 2., 4. };
      std::vector< double > y = { 4., 3., 2., 1. };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( LinearLogTable< double >( std::move( x ), std::move( y ) ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
