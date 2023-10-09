#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "scion/math/LogLinearTable.hpp"

// other includes
#include "utility/IteratorView.hpp"

// convenience typedefs
using namespace njoy::scion;
template < typename X, typename Y = X,
           typename XContainer = std::vector< X >,
           typename YContainer = std::vector< Y > >
using LogLinearTable = math::LogLinearTable< X, Y, XContainer, YContainer >;
template < typename X > using IntervalDomain = math::IntervalDomain< X >;
template < typename X > using OpenDomain = math::OpenDomain< X >;
using InterpolationType = interpolation::InterpolationType;

SCENARIO( "LogLinearTable" ) {

  GIVEN( "tabulated data" ) {

    WHEN( "the data is given explicitly using vectors" ) {

      std::vector< double > x = { 1., 2., 3., 4. };
      std::vector< double > y = { 4., 3., 2., 1. };

      LogLinearTable< double > chunk( std::move( x ), std::move( y ) );

      THEN( "a LogLinearTable can be constructed and members can be tested" ) {

        CHECK( InterpolationType::LogLinear == chunk.interpolation() );
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

      THEN( "a LogLinearTable can be evaluated" ) {

        // values of x in the x grid
        CHECK( 4. == Approx( chunk( 1. ) ) );
        CHECK( 3. == Approx( chunk( 2. ) ) );
        CHECK( 2. == Approx( chunk( 3. ) ) );
        CHECK( 1. == Approx( chunk( 4. ) ) );

        // values of x outside the x grid
        CHECK( 0. == Approx( chunk( 0. ) ) );
        CHECK( 0. == Approx( chunk( 5. ) ) );

        // values of x inside the x grid
        CHECK( 3.464101615 == Approx( chunk( 1.5 ) ) );
        CHECK( 1.414213562 == Approx( chunk( 3.5 ) ) );
      } // THEN

      THEN( "a LogLinearTable can be linearised" ) {

        auto linear = chunk.linearise();

        CHECK( 21 == linear.first.size() );
        CHECK( 21 == linear.second.size() );

        CHECK( 1.    == Approx( linear.first[0] ) );
        CHECK( 1.25  == Approx( linear.first[1] ) );
        CHECK( 1.5   == Approx( linear.first[2] ) );
        CHECK( 1.75  == Approx( linear.first[3] ) );
        CHECK( 2     == Approx( linear.first[4] ) );
        CHECK( 2.125 == Approx( linear.first[5] ) );
        CHECK( 2.25  == Approx( linear.first[6] ) );
        CHECK( 2.375 == Approx( linear.first[7] ) );
        CHECK( 2.5   == Approx( linear.first[8] ) );
        CHECK( 2.625 == Approx( linear.first[9] ) );
        CHECK( 2.75  == Approx( linear.first[10] ) );
        CHECK( 2.875 == Approx( linear.first[11] ) );
        CHECK( 3.    == Approx( linear.first[12] ) );
        CHECK( 3.125 == Approx( linear.first[13] ) );
        CHECK( 3.25  == Approx( linear.first[14] ) );
        CHECK( 3.375 == Approx( linear.first[15] ) );
        CHECK( 3.5   == Approx( linear.first[16] ) );
        CHECK( 3.625 == Approx( linear.first[17] ) );
        CHECK( 3.75  == Approx( linear.first[18] ) );
        CHECK( 3.875 == Approx( linear.first[19] ) );
        CHECK( 4.    == Approx( linear.first[20] ) );

        CHECK( 4.          == Approx( linear.second[0] ) );
        CHECK( 3.722419436 == Approx( linear.second[1] ) );
        CHECK( 3.464101615 == Approx( linear.second[2] ) );
        CHECK( 3.223709795 == Approx( linear.second[3] ) );
        CHECK( 3           == Approx( linear.second[4] ) );
        CHECK( 2.851739475 == Approx( linear.second[5] ) );
        CHECK( 2.710806011 == Approx( linear.second[6] ) );
        CHECK( 2.576837503 == Approx( linear.second[7] ) );
        CHECK( 2.449489743 == Approx( linear.second[8] ) );
        CHECK( 2.328435531 == Approx( linear.second[9] ) );
        CHECK( 2.213363839 == Approx( linear.second[10] ) );
        CHECK( 2.103979011 == Approx( linear.second[11] ) );
        CHECK( 2.          == Approx( linear.second[12] ) );
        CHECK( 1.834008086 == Approx( linear.second[13] ) );
        CHECK( 1.681792831 == Approx( linear.second[14] ) );
        CHECK( 1.542210825 == Approx( linear.second[15] ) );
        CHECK( 1.414213562 == Approx( linear.second[16] ) );
        CHECK( 1.296839555 == Approx( linear.second[17] ) );
        CHECK( 1.189207115 == Approx( linear.second[18] ) );
        CHECK( 1.090507733 == Approx( linear.second[19] ) );
        CHECK( 1.          == Approx( linear.second[20] ) );
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
        CHECK( 4. == Approx( chunk( 1. ) ) );
        CHECK( 3. == Approx( chunk( 2. ) ) );
        CHECK( 2. == Approx( chunk( 3. ) ) );
        CHECK( 1. == Approx( chunk( 4. ) ) );

        // values of x outside the x grid
        CHECK( 0. == Approx( chunk( 0. ) ) );
        CHECK( 0. == Approx( chunk( 5. ) ) );

        // values of x inside the x grid
        CHECK( 3.464101615 == Approx( chunk( 1.5 ) ) );
        CHECK( 1.414213562 == Approx( chunk( 3.5 ) ) );
      } // THEN

      THEN( "a LogLinearTable can be linearised" ) {

        auto linear = chunk.linearise();

        CHECK( 21 == linear.first.size() );
        CHECK( 21 == linear.second.size() );

        CHECK( 1.    == Approx( linear.first[0] ) );
        CHECK( 1.25  == Approx( linear.first[1] ) );
        CHECK( 1.5   == Approx( linear.first[2] ) );
        CHECK( 1.75  == Approx( linear.first[3] ) );
        CHECK( 2     == Approx( linear.first[4] ) );
        CHECK( 2.125 == Approx( linear.first[5] ) );
        CHECK( 2.25  == Approx( linear.first[6] ) );
        CHECK( 2.375 == Approx( linear.first[7] ) );
        CHECK( 2.5   == Approx( linear.first[8] ) );
        CHECK( 2.625 == Approx( linear.first[9] ) );
        CHECK( 2.75  == Approx( linear.first[10] ) );
        CHECK( 2.875 == Approx( linear.first[11] ) );
        CHECK( 3.    == Approx( linear.first[12] ) );
        CHECK( 3.125 == Approx( linear.first[13] ) );
        CHECK( 3.25  == Approx( linear.first[14] ) );
        CHECK( 3.375 == Approx( linear.first[15] ) );
        CHECK( 3.5   == Approx( linear.first[16] ) );
        CHECK( 3.625 == Approx( linear.first[17] ) );
        CHECK( 3.75  == Approx( linear.first[18] ) );
        CHECK( 3.875 == Approx( linear.first[19] ) );
        CHECK( 4.    == Approx( linear.first[20] ) );

        CHECK( 4.          == Approx( linear.second[0] ) );
        CHECK( 3.722419436 == Approx( linear.second[1] ) );
        CHECK( 3.464101615 == Approx( linear.second[2] ) );
        CHECK( 3.223709795 == Approx( linear.second[3] ) );
        CHECK( 3           == Approx( linear.second[4] ) );
        CHECK( 2.851739475 == Approx( linear.second[5] ) );
        CHECK( 2.710806011 == Approx( linear.second[6] ) );
        CHECK( 2.576837503 == Approx( linear.second[7] ) );
        CHECK( 2.449489743 == Approx( linear.second[8] ) );
        CHECK( 2.328435531 == Approx( linear.second[9] ) );
        CHECK( 2.213363839 == Approx( linear.second[10] ) );
        CHECK( 2.103979011 == Approx( linear.second[11] ) );
        CHECK( 2.          == Approx( linear.second[12] ) );
        CHECK( 1.834008086 == Approx( linear.second[13] ) );
        CHECK( 1.681792831 == Approx( linear.second[14] ) );
        CHECK( 1.542210825 == Approx( linear.second[15] ) );
        CHECK( 1.414213562 == Approx( linear.second[16] ) );
        CHECK( 1.296839555 == Approx( linear.second[17] ) );
        CHECK( 1.189207115 == Approx( linear.second[18] ) );
        CHECK( 1.090507733 == Approx( linear.second[19] ) );
        CHECK( 1.          == Approx( linear.second[20] ) );
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

    WHEN( "the x grid has a duplicate point" ) {

      std::vector< double > x = { 1., 2., 2., 4. };
      std::vector< double > y = { 4., 3., 2., 1. };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( LogLinearTable< double >( std::move( x ), std::move( y ) ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
