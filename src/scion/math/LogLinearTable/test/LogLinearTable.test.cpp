#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "scion/math/LogLinearTable.hpp"

// other includes
#include "utility/IteratorView.hpp"

// convenience typedefs
using namespace njoy::scion;
template < typename X, typename Y = X > using LinearLinearTable = math::LinearLinearTable< X, Y >;
template < typename X, typename Y = X,
           typename XContainer = std::vector< X >,
           typename YContainer = std::vector< Y > >
using LogLinearTable = math::LogLinearTable< X, Y, XContainer, YContainer >;
template < typename X > using IntervalDomain = math::IntervalDomain< X >;
using InterpolationType = interpolation::InterpolationType;

SCENARIO( "LogLinearTable" ) {

  GIVEN( "tabulated data" ) {

    WHEN( "the data is given explicitly using vectors" ) {

      std::vector< double > x = { 1., 2., 3., 4. };
      std::vector< double > y = { 4., 3., 2., 1. };

      LogLinearTable< double > chunk( std::move( x ), std::move( y ) );

      THEN( "a LogLinearTable can be constructed and members can be tested" ) {

        CHECK( InterpolationType::LogLinear == chunk.interpolation() );
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

      THEN( "a LogLinearTable can be evaluated" ) {

        // values of x in the x grid
        CHECK( 4. == Approx( chunk.evaluate( 1. ) ) );
        CHECK( 3. == Approx( chunk.evaluate( 2. ) ) );
        CHECK( 2. == Approx( chunk.evaluate( 3. ) ) );
        CHECK( 1. == Approx( chunk.evaluate( 4. ) ) );

        // values of x outside the x grid
        CHECK( 0. == Approx( chunk.evaluate( 0. ) ) );
        CHECK( 0. == Approx( chunk.evaluate( 5. ) ) );

        // values of x inside the x grid
        CHECK( 3.464101615 == Approx( chunk.evaluate( 1.5 ) ) );
        CHECK( 1.414213562 == Approx( chunk.evaluate( 3.5 ) ) );
      } // THEN

      THEN( "a LogLinearTable can be linearised" ) {

        LinearLinearTable< double > linear = chunk.linearise();

        CHECK( 21 == linear.x().size() );
        CHECK( 21 == linear.y().size() );

        CHECK( 1.    == Approx( linear.x()[0] ) );
        CHECK( 1.25  == Approx( linear.x()[1] ) );
        CHECK( 1.5   == Approx( linear.x()[2] ) );
        CHECK( 1.75  == Approx( linear.x()[3] ) );
        CHECK( 2     == Approx( linear.x()[4] ) );
        CHECK( 2.125 == Approx( linear.x()[5] ) );
        CHECK( 2.25  == Approx( linear.x()[6] ) );
        CHECK( 2.375 == Approx( linear.x()[7] ) );
        CHECK( 2.5   == Approx( linear.x()[8] ) );
        CHECK( 2.625 == Approx( linear.x()[9] ) );
        CHECK( 2.75  == Approx( linear.x()[10] ) );
        CHECK( 2.875 == Approx( linear.x()[11] ) );
        CHECK( 3.    == Approx( linear.x()[12] ) );
        CHECK( 3.125 == Approx( linear.x()[13] ) );
        CHECK( 3.25  == Approx( linear.x()[14] ) );
        CHECK( 3.375 == Approx( linear.x()[15] ) );
        CHECK( 3.5   == Approx( linear.x()[16] ) );
        CHECK( 3.625 == Approx( linear.x()[17] ) );
        CHECK( 3.75  == Approx( linear.x()[18] ) );
        CHECK( 3.875 == Approx( linear.x()[19] ) );
        CHECK( 4.     == Approx( linear.x()[20] ) );

        CHECK( 4.          == Approx( linear.y()[0] ) );
        CHECK( 3.722419436 == Approx( linear.y()[1] ) );
        CHECK( 3.464101615 == Approx( linear.y()[2] ) );
        CHECK( 3.223709795 == Approx( linear.y()[3] ) );
        CHECK( 3           == Approx( linear.y()[4] ) );
        CHECK( 2.851739475 == Approx( linear.y()[5] ) );
        CHECK( 2.710806011 == Approx( linear.y()[6] ) );
        CHECK( 2.576837503 == Approx( linear.y()[7] ) );
        CHECK( 2.449489743 == Approx( linear.y()[8] ) );
        CHECK( 2.328435531 == Approx( linear.y()[9] ) );
        CHECK( 2.213363839 == Approx( linear.y()[10] ) );
        CHECK( 2.103979011 == Approx( linear.y()[11] ) );
        CHECK( 2.          == Approx( linear.y()[12] ) );
        CHECK( 1.834008086 == Approx( linear.y()[13] ) );
        CHECK( 1.681792831 == Approx( linear.y()[14] ) );
        CHECK( 1.542210825 == Approx( linear.y()[15] ) );
        CHECK( 1.414213562 == Approx( linear.y()[16] ) );
        CHECK( 1.296839555 == Approx( linear.y()[17] ) );
        CHECK( 1.189207115 == Approx( linear.y()[18] ) );
        CHECK( 1.090507733 == Approx( linear.y()[19] ) );
        CHECK( 1.          == Approx( linear.y()[20] ) );
      } // THEN
    } // WHEN

    WHEN( "the data is given explicitly using iterator views" ) {

      using View = njoy::utility::IteratorView< std::vector< double >::const_iterator >;

      const std::vector< double > xvalues= { 1., 2., 3., 4. };
      const std::vector< double > yvalues = { 4., 3., 2., 1. };

      View x = njoy::utility::make_view( xvalues );
      View y = njoy::utility::make_view( yvalues );

      LogLinearTable< double, double, View, View > chunk( std::move( x ), std::move( y ) );

      THEN( "a LogLinearTable can be constructed and members can be tested" ) {

        CHECK( InterpolationType::LogLinear == chunk.interpolation() );
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

      THEN( "a LogLinearTable can be evaluated" ) {

        // values of x in the x grid
        CHECK( 4. == Approx( chunk.evaluate( 1. ) ) );
        CHECK( 3. == Approx( chunk.evaluate( 2. ) ) );
        CHECK( 2. == Approx( chunk.evaluate( 3. ) ) );
        CHECK( 1. == Approx( chunk.evaluate( 4. ) ) );

        // values of x outside the x grid
        CHECK( 0. == Approx( chunk.evaluate( 0. ) ) );
        CHECK( 0. == Approx( chunk.evaluate( 5. ) ) );

        // values of x inside the x grid
        CHECK( 3.464101615 == Approx( chunk.evaluate( 1.5 ) ) );
        CHECK( 1.414213562 == Approx( chunk.evaluate( 3.5 ) ) );
      } // THEN

      THEN( "a LogLinearTable can be linearised" ) {

        LinearLinearTable< double > linear = chunk.linearise();

        CHECK( 21 == linear.x().size() );
        CHECK( 21 == linear.y().size() );

        CHECK( 1.    == Approx( linear.x()[0] ) );
        CHECK( 1.25  == Approx( linear.x()[1] ) );
        CHECK( 1.5   == Approx( linear.x()[2] ) );
        CHECK( 1.75  == Approx( linear.x()[3] ) );
        CHECK( 2     == Approx( linear.x()[4] ) );
        CHECK( 2.125 == Approx( linear.x()[5] ) );
        CHECK( 2.25  == Approx( linear.x()[6] ) );
        CHECK( 2.375 == Approx( linear.x()[7] ) );
        CHECK( 2.5   == Approx( linear.x()[8] ) );
        CHECK( 2.625 == Approx( linear.x()[9] ) );
        CHECK( 2.75  == Approx( linear.x()[10] ) );
        CHECK( 2.875 == Approx( linear.x()[11] ) );
        CHECK( 3.    == Approx( linear.x()[12] ) );
        CHECK( 3.125 == Approx( linear.x()[13] ) );
        CHECK( 3.25  == Approx( linear.x()[14] ) );
        CHECK( 3.375 == Approx( linear.x()[15] ) );
        CHECK( 3.5   == Approx( linear.x()[16] ) );
        CHECK( 3.625 == Approx( linear.x()[17] ) );
        CHECK( 3.75  == Approx( linear.x()[18] ) );
        CHECK( 3.875 == Approx( linear.x()[19] ) );
        CHECK( 4.     == Approx( linear.x()[20] ) );

        CHECK( 4.          == Approx( linear.y()[0] ) );
        CHECK( 3.722419436 == Approx( linear.y()[1] ) );
        CHECK( 3.464101615 == Approx( linear.y()[2] ) );
        CHECK( 3.223709795 == Approx( linear.y()[3] ) );
        CHECK( 3           == Approx( linear.y()[4] ) );
        CHECK( 2.851739475 == Approx( linear.y()[5] ) );
        CHECK( 2.710806011 == Approx( linear.y()[6] ) );
        CHECK( 2.576837503 == Approx( linear.y()[7] ) );
        CHECK( 2.449489743 == Approx( linear.y()[8] ) );
        CHECK( 2.328435531 == Approx( linear.y()[9] ) );
        CHECK( 2.213363839 == Approx( linear.y()[10] ) );
        CHECK( 2.103979011 == Approx( linear.y()[11] ) );
        CHECK( 2.          == Approx( linear.y()[12] ) );
        CHECK( 1.834008086 == Approx( linear.y()[13] ) );
        CHECK( 1.681792831 == Approx( linear.y()[14] ) );
        CHECK( 1.542210825 == Approx( linear.y()[15] ) );
        CHECK( 1.414213562 == Approx( linear.y()[16] ) );
        CHECK( 1.296839555 == Approx( linear.y()[17] ) );
        CHECK( 1.189207115 == Approx( linear.y()[18] ) );
        CHECK( 1.090507733 == Approx( linear.y()[19] ) );
        CHECK( 1.          == Approx( linear.y()[20] ) );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "invalid data for a LogLinearTable object" ) {

    WHEN( "there are not enough values in the x or y grid" ) {

      std::vector< double > empty = {};
      std::vector< double > one = { 1. };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( LogLinearTable< double >( empty, empty ) );
        CHECK_THROWS( LogLinearTable< double >( one, one ) );
      } // THEN
    } // WHEN

    WHEN( "the x and y grid do not have the same number of points" ) {

      std::vector< double > x = { 1., 2., 3., 4. };
      std::vector< double > y = { 4., 3., 2. };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( LogLinearTable< double >( std::move( x ), std::move( y ) ) );
      } // THEN
    } // WHEN

    WHEN( "the x grid is not sorted" ) {

      std::vector< double > x = { 1., 3., 2., 4. };
      std::vector< double > y = { 4., 3., 2., 1. };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( LogLinearTable< double >( std::move( x ), std::move( y ) ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
