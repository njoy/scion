#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "scion/math/LinearLinearTable.hpp"

// other includes
#include "utility/IteratorView.hpp"

// convenience typedefs
using namespace njoy::scion;
template < typename X, typename Y = X,
           typename XContainer = std::vector< X >,
           typename YContainer = std::vector< Y > >
using LinearLinearTable = math::LinearLinearTable< X, Y, XContainer, YContainer >;
template < typename X > using IntervalDomain = math::IntervalDomain< X >;
template < typename X > using OpenDomain = math::OpenDomain< X >;
using InterpolationType = interpolation::InterpolationType;

SCENARIO( "LinearLinearTable" ) {

  GIVEN( "tabulated data" ) {

    WHEN( "the data is given explicitly using vectors" ) {

      const std::vector< double > x = { 1., 2., 3., 4. };
      const std::vector< double > y = { 4., 3., 2., 1. };

      LinearLinearTable< double > chunk( std::move( x ), std::move( y ) );

      THEN( "a LinearLinearTable can be constructed and members can be tested" ) {

        CHECK( InterpolationType::LinearLinear == chunk.interpolation() );
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

      THEN( "a LinearLinearTable can be evaluated" ) {

        // values of x in the x grid
        CHECK( 4. == Approx( chunk( 1. ) ) );
        CHECK( 3. == Approx( chunk( 2. ) ) );
        CHECK( 2. == Approx( chunk( 3. ) ) );
        CHECK( 1. == Approx( chunk( 4. ) ) );

        // values of x outside the x grid
        CHECK( 0. == Approx( chunk( 0. ) ) );
        CHECK( 0. == Approx( chunk( 5. ) ) );

        // values of x inside the x grid
        CHECK( 3.5 == Approx( chunk( 1.5 ) ) );
        CHECK( 1.5 == Approx( chunk( 3.5 ) ) );
      } // THEN

      THEN( "a LinearLinearTable can be linearised" ) {

        auto linear = chunk.linearise();
        CHECK( linear.first == chunk.x() );
        CHECK( linear.second == chunk.y() );
      } // THEN

      THEN( "the domain can be tested" ) {

        CHECK( true == chunk.isInside( 1.0 ) );
        CHECK( true == chunk.isInside( 2.5 ) );
        CHECK( true == chunk.isInside( 4.0 ) );

        CHECK( false == chunk.isContained( 1.0 ) );
        CHECK( true == chunk.isContained( 2.5 ) );
        CHECK( false == chunk.isContained( 4.0 ) );

        CHECK( true == chunk.isSameDomain( IntervalDomain< double >( 1., 4. ) ) );
        CHECK( false == chunk.isSameDomain( IntervalDomain< double >( 0., 4. ) ) );
        CHECK( false == chunk.isSameDomain( OpenDomain< double >() ) );
      } // THEN
    } // WHEN

    WHEN( "the data is given explicitly using iterator views" ) {

      using View = njoy::utility::IteratorView< std::vector< double >::const_iterator >;

      const std::vector< double > xvalues= { 1., 2., 3., 4. };
      const std::vector< double > yvalues = { 4., 3., 2., 1. };

      View x = njoy::utility::make_view( xvalues );
      View y = njoy::utility::make_view( yvalues );

      LinearLinearTable< double, double, View, View > chunk( std::move( x ), std::move( y ) );

      THEN( "a LinearLinearTable can be constructed and members can be tested" ) {

        CHECK( InterpolationType::LinearLinear == chunk.interpolation() );
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
        CHECK( 4. == Approx( chunk( 1. ) ) );
        CHECK( 3. == Approx( chunk( 2. ) ) );
        CHECK( 2. == Approx( chunk( 3. ) ) );
        CHECK( 1. == Approx( chunk( 4. ) ) );

        // values of x outside the x grid
        CHECK( 0. == Approx( chunk( 0. ) ) );
        CHECK( 0. == Approx( chunk( 5. ) ) );

        // values of x inside the x grid
        CHECK( 3.5 == Approx( chunk( 1.5 ) ) );
        CHECK( 1.5 == Approx( chunk( 3.5 ) ) );
      } // THEN

      THEN( "a LinearLinearTable can be linearised" ) {

        auto linear = chunk.linearise();
        CHECK( linear.first == chunk.x() );
        CHECK( linear.second == chunk.y() );
      } // THEN

      THEN( "the domain can be tested" ) {

        CHECK( true == chunk.isInside( 1.0 ) );
        CHECK( true == chunk.isInside( 2.5 ) );
        CHECK( true == chunk.isInside( 4.0 ) );

        CHECK( false == chunk.isContained( 1.0 ) );
        CHECK( true == chunk.isContained( 2.5 ) );
        CHECK( false == chunk.isContained( 4.0 ) );

        CHECK( true == chunk.isSameDomain( IntervalDomain< double >( 1., 4. ) ) );
        CHECK( false == chunk.isSameDomain( IntervalDomain< double >( 0., 4. ) ) );
        CHECK( false == chunk.isSameDomain( OpenDomain< double >() ) );
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

    WHEN( "the x grid has a duplicate point" ) {

      std::vector< double > x = { 1., 2., 2., 4. };
      std::vector< double > y = { 4., 3., 2., 1. };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( LinearLinearTable< double >( std::move( x ), std::move( y ) ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
