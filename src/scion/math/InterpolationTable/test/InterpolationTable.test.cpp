#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "scion/math/InterpolationTable.hpp"

// other includes

// convenience typedefs
using namespace njoy::scion;
template < typename X, typename Y = X > using LinearLinearTable = math::LinearLinearTable< X, Y >;
template < typename X, typename Y = X > using InterpolationTable = math::InterpolationTable< X, Y >;
template < typename X > using IntervalDomain = math::IntervalDomain< X >;
using InterpolationType = interpolation::InterpolationType;

SCENARIO( "InterpolationTable" ) {

  GIVEN( "data without a jump" ) {

    WHEN( "the data is given explicitly" ) {

      const std::vector< double > x = { 1., 2., 3., 4. };
      const std::vector< double > y = { 4., 3., 2., 1. };
      const std::vector< std::size_t > boundaries = { 1, 3 };
      const std::vector< InterpolationType > interpolants = {

        InterpolationType::LinearLinear,
        InterpolationType::LinearLog
      };

      InterpolationTable< double > chunk( std::move( x ), std::move( y ),
                                          std::move( boundaries ),
                                          std::move( interpolants ) );

      THEN( "a InterpolationTable can be constructed and members can be tested" ) {

        CHECK( 4 == chunk.numberPoints() );
        CHECK( 2 == chunk.numberRegions() );
        CHECK( 4 == chunk.x().size() );
        CHECK( 4 == chunk.y().size() );
        CHECK( 2 == chunk.boundaries().size() );
        CHECK( 2 == chunk.interpolants().size() );
        CHECK( 1. == Approx( chunk.x()[0] ) );
        CHECK( 2. == Approx( chunk.x()[1] ) );
        CHECK( 3. == Approx( chunk.x()[2] ) );
        CHECK( 4. == Approx( chunk.x()[3] ) );
        CHECK( 4. == Approx( chunk.y()[0] ) );
        CHECK( 3. == Approx( chunk.y()[1] ) );
        CHECK( 2. == Approx( chunk.y()[2] ) );
        CHECK( 1. == Approx( chunk.y()[3] ) );
        CHECK( 1 == chunk.boundaries()[0] );
        CHECK( 3 == chunk.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );
        CHECK( InterpolationType::LinearLog == chunk.interpolants()[1] );

        CHECK( true == std::holds_alternative< IntervalDomain< double > >( chunk.domain() ) );
      } // THEN

      THEN( "a InterpolationTable can be evaluated" ) {

        // values of x in the x grid
        CHECK( 4. == Approx( chunk( 1. ) ) );
        CHECK( 3. == Approx( chunk( 2. ) ) );
        CHECK( 2. == Approx( chunk( 3. ) ) );
        CHECK( 1. == Approx( chunk( 4. ) ) );

        // values of x outside the x grid
        CHECK( 0. == Approx( chunk( 0. ) ) );
        CHECK( 0. == Approx( chunk( 5. ) ) );

        // values of x inside the x grid (lin-lin piece)
        CHECK( 3.5 == Approx( chunk( 1.5 ) ) );

        // values of x inside the x grid (lin-log piece)
        CHECK( 2.449660287 == Approx( chunk( 2.5 ) ) );
        CHECK( 1.464163065 == Approx( chunk( 3.5 ) ) );
      } // THEN

      THEN( "a InterpolationTable can be linearised" ) {

        LinearLinearTable< double > linear = chunk.linearise();

        CHECK( 18 == linear.x().size() );
        CHECK( 18 == linear.y().size() );

        CHECK( 1.    == Approx( linear.x()[0] ) );
        CHECK( 2.    == Approx( linear.x()[1] ) );
        CHECK( 2.125 == Approx( linear.x()[2] ) );
        CHECK( 2.25  == Approx( linear.x()[3] ) );
        CHECK( 2.375 == Approx( linear.x()[4] ) );
        CHECK( 2.5   == Approx( linear.x()[5] ) );
        CHECK( 2.625 == Approx( linear.x()[6] ) );
        CHECK( 2.75  == Approx( linear.x()[7] ) );
        CHECK( 2.875 == Approx( linear.x()[8] ) );
        CHECK( 3.    == Approx( linear.x()[9] ) );
        CHECK( 3.125 == Approx( linear.x()[10] ) );
        CHECK( 3.25  == Approx( linear.x()[11] ) );
        CHECK( 3.375 == Approx( linear.x()[12] ) );
        CHECK( 3.5   == Approx( linear.x()[13] ) );
        CHECK( 3.625 == Approx( linear.x()[14] ) );
        CHECK( 3.75  == Approx( linear.x()[15] ) );
        CHECK( 3.875 == Approx( linear.x()[16] ) );
        CHECK( 4.    == Approx( linear.x()[17] ) );

        CHECK( 4.          == Approx( linear.y()[0] ) );
        CHECK( 3.          == Approx( linear.y()[1] ) );
        CHECK( 2.850481285 == Approx( linear.y()[2] ) );
        CHECK( 2.709511291 == Approx( linear.y()[3] ) );
        CHECK( 2.576165116 == Approx( linear.y()[4] ) );
        CHECK( 2.449660287 == Approx( linear.y()[5] ) );
        CHECK( 2.329328936 == Approx( linear.y()[6] ) );
        CHECK( 2.21459646  == Approx( linear.y()[7] ) );
        CHECK( 2.104964924 == Approx( linear.y()[8] ) );
        CHECK( 2.          == Approx( linear.y()[9] ) );
        CHECK( 1.858100318 == Approx( linear.y()[10] ) );
        CHECK( 1.721766786 == Approx( linear.y()[11] ) );
        CHECK( 1.59057916  == Approx( linear.y()[12] ) );
        CHECK( 1.464163065 == Approx( linear.y()[13] ) );
        CHECK( 1.34218355  == Approx( linear.y()[14] ) );
        CHECK( 1.224339739 == Approx( linear.y()[15] ) );
        CHECK( 1.110360364 == Approx( linear.y()[16] ) );
        CHECK( 1.          == Approx( linear.y()[17] ) );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "data with a jump" ) {

    WHEN( "the data is given explicitly" ) {

      const std::vector< double > x = { 1., 2., 2., 3., 4. };
      const std::vector< double > y = { 4., 3., 4., 3., 2. };
      const std::vector< std::size_t > boundaries = { 1, 4 };
      const std::vector< InterpolationType > interpolants = {

        InterpolationType::LinearLinear,
        InterpolationType::LinearLog
      };

      InterpolationTable< double > chunk( std::move( x ), std::move( y ),
                                          std::move( boundaries ),
                                          std::move( interpolants ) );

      THEN( "a InterpolationTable can be constructed and members can be tested" ) {

        CHECK( 5 == chunk.x().size() );
        CHECK( 5 == chunk.y().size() );
        CHECK( 2 == chunk.boundaries().size() );
        CHECK( 2 == chunk.interpolants().size() );
        CHECK( 1. == Approx( chunk.x()[0] ) );
        CHECK( 2. == Approx( chunk.x()[1] ) );
        CHECK( 2. == Approx( chunk.x()[2] ) );
        CHECK( 3. == Approx( chunk.x()[3] ) );
        CHECK( 4. == Approx( chunk.x()[4] ) );
        CHECK( 4. == Approx( chunk.y()[0] ) );
        CHECK( 3. == Approx( chunk.y()[1] ) );
        CHECK( 4. == Approx( chunk.y()[2] ) );
        CHECK( 3. == Approx( chunk.y()[3] ) );
        CHECK( 2. == Approx( chunk.y()[4] ) );
        CHECK( 1 == chunk.boundaries()[0] );
        CHECK( 4 == chunk.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );
        CHECK( InterpolationType::LinearLog == chunk.interpolants()[1] );

        CHECK( true == std::holds_alternative< IntervalDomain< double > >( chunk.domain() ) );
      } // THEN

      THEN( "a InterpolationTable can be evaluated" ) {

        // values of x in the x grid
        CHECK( 4. == Approx( chunk( 1. ) ) );
        CHECK( 4. == Approx( chunk( 2. ) ) );
        CHECK( 3. == Approx( chunk( 3. ) ) );
        CHECK( 2. == Approx( chunk( 4. ) ) );

        // values of x outside the x grid
        CHECK( 0. == Approx( chunk( 0. ) ) );
        CHECK( 0. == Approx( chunk( 5. ) ) );

        // values of x inside the x grid (lin-lin piece)
        CHECK( 3.5 == Approx( chunk( 1.5 ) ) );

        // values of x inside the x grid (lin-log piece)
        CHECK( 3.449660287 == Approx( chunk( 2.5 ) ) );
        CHECK( 2.464163065 == Approx( chunk( 3.5 ) ) );
      } // THEN

      THEN( "a InterpolationTable can be linearised" ) {

        LinearLinearTable< double > linear = chunk.linearise();

        CHECK( 12 == linear.x().size() );
        CHECK( 12 == linear.y().size() );

        CHECK( 1.    == Approx( linear.x()[0] ) );
        CHECK( 2.    == Approx( linear.x()[1] ) );
        CHECK( 2.    == Approx( linear.x()[2] ) );
        CHECK( 2.125 == Approx( linear.x()[3] ) );
        CHECK( 2.25  == Approx( linear.x()[4] ) );
        CHECK( 2.5   == Approx( linear.x()[5] ) );
        CHECK( 2.75  == Approx( linear.x()[6] ) );
        CHECK( 3.    == Approx( linear.x()[7] ) );
        CHECK( 3.25  == Approx( linear.x()[8] ) );
        CHECK( 3.5   == Approx( linear.x()[9] ) );
        CHECK( 3.75  == Approx( linear.x()[10] ) );
        CHECK( 4.    == Approx( linear.x()[11] ) );

        CHECK( 4.          == Approx( linear.y()[0] ) );
        CHECK( 3.          == Approx( linear.y()[1] ) );
        CHECK( 4.          == Approx( linear.y()[2] ) );
        CHECK( 3.850481285 == Approx( linear.y()[3] ) );
        CHECK( 3.709511291 == Approx( linear.y()[4] ) );
        CHECK( 3.449660287 == Approx( linear.y()[5] ) );
        CHECK( 3.21459646  == Approx( linear.y()[6] ) );
        CHECK( 3.          == Approx( linear.y()[7] ) );
        CHECK( 2.721766786 == Approx( linear.y()[8] ) );
        CHECK( 2.464163065 == Approx( linear.y()[9] ) );
        CHECK( 2.224339739 == Approx( linear.y()[10] ) );
        CHECK( 2.          == Approx( linear.y()[11] ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
