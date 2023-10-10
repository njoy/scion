// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
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
template < typename X > using OpenDomain = math::OpenDomain< X >;
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
        CHECK_THAT( 1., WithinRel( chunk.x()[0] ) );
        CHECK_THAT( 2., WithinRel( chunk.x()[1] ) );
        CHECK_THAT( 3., WithinRel( chunk.x()[2] ) );
        CHECK_THAT( 4., WithinRel( chunk.x()[3] ) );
        CHECK_THAT( 4., WithinRel( chunk.y()[0] ) );
        CHECK_THAT( 3., WithinRel( chunk.y()[1] ) );
        CHECK_THAT( 2., WithinRel( chunk.y()[2] ) );
        CHECK_THAT( 1., WithinRel( chunk.y()[3] ) );

        CHECK( true == std::holds_alternative< IntervalDomain< double > >( chunk.domain() ) );
      } // THEN

      THEN( "a LogLogTable can be evaluated" ) {

        // values of x in the x grid
        CHECK_THAT( 4., WithinRel( chunk( 1. ) ) );
        CHECK_THAT( 3., WithinRel( chunk( 2. ) ) );
        CHECK_THAT( 2., WithinRel( chunk( 3. ) ) );
        CHECK_THAT( 1., WithinRel( chunk( 4. ) ) );

        // values of x outside the x grid
        CHECK_THAT( 0., WithinRel( chunk( 0. ) ) );
        CHECK_THAT( 0., WithinRel( chunk( 5. ) ) );

        // values of x inside the x grid
        CHECK_THAT( 3.380457774631770, WithinRel( chunk( 1.5 ) ) );
        CHECK_THAT( 2.4              , WithinRel( chunk( 2.5 ) ) );
        CHECK_THAT( 1.379516837537910, WithinRel( chunk( 3.5 ) ) );
      } // THEN

      THEN( "a LogLogTable can be linearised" ) {

        auto linear = chunk.linearise();

        CHECK( 34 == linear.first.size() );
        CHECK( 34 == linear.second.size() );

        CHECK_THAT( 1.    , WithinRel( linear.first[0] ) );
        CHECK_THAT( 1.0625, WithinRel( linear.first[1] ) );
        CHECK_THAT( 1.125 , WithinRel( linear.first[2] ) );
        CHECK_THAT( 1.25  , WithinRel( linear.first[3] ) );
        CHECK_THAT( 1.375 , WithinRel( linear.first[4] ) );
        CHECK_THAT( 1.5   , WithinRel( linear.first[5] ) );
        CHECK_THAT( 1.625 , WithinRel( linear.first[6] ) );
        CHECK_THAT( 1.75	, WithinRel( linear.first[7] ) );
        CHECK_THAT( 1.875 , WithinRel( linear.first[8] ) );
        CHECK_THAT( 2.    , WithinRel( linear.first[9] ) );
        CHECK_THAT( 2.125 , WithinRel( linear.first[10] ) );
        CHECK_THAT( 2.25	, WithinRel( linear.first[11] ) );
        CHECK_THAT( 2.375 , WithinRel( linear.first[12] ) );
        CHECK_THAT( 2.5	  , WithinRel( linear.first[13] ) );
        CHECK_THAT( 2.625 , WithinRel( linear.first[14] ) );
        CHECK_THAT( 2.75  , WithinRel( linear.first[15] ) );
        CHECK_THAT( 2.875 , WithinRel( linear.first[16] ) );
        CHECK_THAT( 3.    , WithinRel( linear.first[17] ) );
        CHECK_THAT( 3.0625, WithinRel( linear.first[18] ) );
        CHECK_THAT( 3.125 , WithinRel( linear.first[19] ) );
        CHECK_THAT( 3.1875, WithinRel( linear.first[20] ) );
        CHECK_THAT( 3.25  , WithinRel( linear.first[21] ) );
        CHECK_THAT( 3.3125, WithinRel( linear.first[22] ) );
        CHECK_THAT( 3.375 , WithinRel( linear.first[23] ) );
        CHECK_THAT( 3.4375, WithinRel( linear.first[24] ) );
        CHECK_THAT( 3.5   , WithinRel( linear.first[25] ) );
        CHECK_THAT( 3.5625, WithinRel( linear.first[26] ) );
        CHECK_THAT( 3.625 , WithinRel( linear.first[27] ) );
        CHECK_THAT( 3.6875, WithinRel( linear.first[28] ) );
        CHECK_THAT( 3.75  , WithinRel( linear.first[29] ) );
        CHECK_THAT( 3.8125, WithinRel( linear.first[30] ) );
        CHECK_THAT( 3.875 , WithinRel( linear.first[31] ) );
        CHECK_THAT( 3.9375, WithinRel( linear.first[32] ) );
        CHECK_THAT( 4.    , WithinRel( linear.first[33] ) );

        CHECK_THAT( 4.              , WithinRel( linear.second[0] ) );
        CHECK_THAT( 3.90060968219886, WithinRel( linear.second[1] ) );
        CHECK_THAT( 3.80916492202280, WithinRel( linear.second[2] ) );
        CHECK_THAT( 3.64618501493277, WithinRel( linear.second[3] ) );
        CHECK_THAT( 3.50476727724719, WithinRel( linear.second[4] ) );
        CHECK_THAT( 3.38045777463177, WithinRel( linear.second[5] ) );
        CHECK_THAT( 3.27000139455183, WithinRel( linear.second[6] ) );
        CHECK_THAT( 3.17095506211775, WithinRel( linear.second[7] ) );
        CHECK_THAT( 3.08144362036884, WithinRel( linear.second[8] ) );
        CHECK_THAT( 3.              , WithinRel( linear.second[9] ) );
        CHECK_THAT( 2.82352941176471, WithinRel( linear.second[10] ) );
        CHECK_THAT( 2.66666666666667, WithinRel( linear.second[11] ) );
        CHECK_THAT( 2.52631578947368, WithinRel( linear.second[12] ) );
        CHECK_THAT( 2.4             , WithinRel( linear.second[13] ) );
        CHECK_THAT( 2.28571428571429, WithinRel( linear.second[14] ) );
        CHECK_THAT( 2.18181818181818, WithinRel( linear.second[15] ) );
        CHECK_THAT( 2.08695652173913, WithinRel( linear.second[16] ) );
        CHECK_THAT( 2.              , WithinRel( linear.second[17] ) );
        CHECK_THAT( 1.90306670505059, WithinRel( linear.second[18] ) );
        CHECK_THAT( 1.81264991535569, WithinRel( linear.second[19] ) );
        CHECK_THAT( 1.72819403587833, WithinRel( linear.second[20] ) );
        CHECK_THAT( 1.64920047955189, WithinRel( linear.second[21] ) );
        CHECK_THAT( 1.57522086581409, WithinRel( linear.second[22] ) );
        CHECK_THAT( 1.50585114003178, WithinRel( linear.second[23] ) );
        CHECK_THAT( 1.44072647484858, WithinRel( linear.second[24] ) );
        CHECK_THAT( 1.37951683753791, WithinRel( linear.second[25] ) );
        CHECK_THAT( 1.32192312633766, WithinRel( linear.second[26] ) );
        CHECK_THAT( 1.26767379428859, WithinRel( linear.second[27] ) );
        CHECK_THAT( 1.21652189193419, WithinRel( linear.second[28] ) );
        CHECK_THAT( 1.16824247087599, WithinRel( linear.second[29] ) );
        CHECK_THAT( 1.12263029902043, WithinRel( linear.second[30] ) );
        CHECK_THAT( 1.07949784572851, WithinRel( linear.second[31] ) );
        CHECK_THAT( 1.03867350124975, WithinRel( linear.second[32] ) );
        CHECK_THAT( 1.              , WithinRel( linear.second[33] ) );
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

      LogLogTable< double, double, View, View > chunk( std::move( x ), std::move( y ) );

      THEN( "a LogLogTable can be constructed and members can be tested" ) {

        CHECK( InterpolationType::LogLog == chunk.interpolation() );
        CHECK( 4 == chunk.x().size() );
        CHECK( 4 == chunk.y().size() );
        CHECK_THAT( 1., WithinRel( chunk.x()[0] ) );
        CHECK_THAT( 2., WithinRel( chunk.x()[1] ) );
        CHECK_THAT( 3., WithinRel( chunk.x()[2] ) );
        CHECK_THAT( 4., WithinRel( chunk.x()[3] ) );
        CHECK_THAT( 4., WithinRel( chunk.y()[0] ) );
        CHECK_THAT( 3., WithinRel( chunk.y()[1] ) );
        CHECK_THAT( 2., WithinRel( chunk.y()[2] ) );
        CHECK_THAT( 1., WithinRel( chunk.y()[3] ) );

        CHECK( true == std::holds_alternative< IntervalDomain< double > >( chunk.domain() ) );
      } // THEN

      THEN( "a LogLogTable can be evaluated" ) {

        // values of x in the x grid
        CHECK_THAT( 4., WithinRel( chunk( 1. ) ) );
        CHECK_THAT( 3., WithinRel( chunk( 2. ) ) );
        CHECK_THAT( 2., WithinRel( chunk( 3. ) ) );
        CHECK_THAT( 1., WithinRel( chunk( 4. ) ) );

        // values of x outside the x grid
        CHECK_THAT( 0., WithinRel( chunk( 0. ) ) );
        CHECK_THAT( 0., WithinRel( chunk( 5. ) ) );

        // values of x inside the x grid
        CHECK_THAT( 3.380457774631770, WithinRel( chunk( 1.5 ) ) );
        CHECK_THAT( 2.4              , WithinRel( chunk( 2.5 ) ) );
        CHECK_THAT( 1.379516837537910, WithinRel( chunk( 3.5 ) ) );
      } // THEN

      THEN( "a LogLogTable can be linearised" ) {

        auto linear = chunk.linearise();

        CHECK( 34 == linear.first.size() );
        CHECK( 34 == linear.second.size() );

        CHECK_THAT( 1.    , WithinRel( linear.first[0] ) );
        CHECK_THAT( 1.0625, WithinRel( linear.first[1] ) );
        CHECK_THAT( 1.125 , WithinRel( linear.first[2] ) );
        CHECK_THAT( 1.25  , WithinRel( linear.first[3] ) );
        CHECK_THAT( 1.375 , WithinRel( linear.first[4] ) );
        CHECK_THAT( 1.5   , WithinRel( linear.first[5] ) );
        CHECK_THAT( 1.625 , WithinRel( linear.first[6] ) );
        CHECK_THAT( 1.75  , WithinRel( linear.first[7] ) );
        CHECK_THAT( 1.875 , WithinRel( linear.first[8] ) );
        CHECK_THAT( 2.    , WithinRel( linear.first[9] ) );
        CHECK_THAT( 2.125 , WithinRel( linear.first[10] ) );
        CHECK_THAT( 2.25	, WithinRel( linear.first[11] ) );
        CHECK_THAT( 2.375 , WithinRel( linear.first[12] ) );
        CHECK_THAT( 2.5	  , WithinRel( linear.first[13] ) );
        CHECK_THAT( 2.625 , WithinRel( linear.first[14] ) );
        CHECK_THAT( 2.75  , WithinRel( linear.first[15] ) );
        CHECK_THAT( 2.875 , WithinRel( linear.first[16] ) );
        CHECK_THAT( 3.    , WithinRel( linear.first[17] ) );
        CHECK_THAT( 3.0625, WithinRel( linear.first[18] ) );
        CHECK_THAT( 3.125 , WithinRel( linear.first[19] ) );
        CHECK_THAT( 3.1875, WithinRel( linear.first[20] ) );
        CHECK_THAT( 3.25  , WithinRel( linear.first[21] ) );
        CHECK_THAT( 3.3125, WithinRel( linear.first[22] ) );
        CHECK_THAT( 3.375 , WithinRel( linear.first[23] ) );
        CHECK_THAT( 3.4375, WithinRel( linear.first[24] ) );
        CHECK_THAT( 3.5   , WithinRel( linear.first[25] ) );
        CHECK_THAT( 3.5625, WithinRel( linear.first[26] ) );
        CHECK_THAT( 3.625 , WithinRel( linear.first[27] ) );
        CHECK_THAT( 3.6875, WithinRel( linear.first[28] ) );
        CHECK_THAT( 3.75  , WithinRel( linear.first[29] ) );
        CHECK_THAT( 3.8125, WithinRel( linear.first[30] ) );
        CHECK_THAT( 3.875 , WithinRel( linear.first[31] ) );
        CHECK_THAT( 3.9375, WithinRel( linear.first[32] ) );
        CHECK_THAT( 4.    , WithinRel( linear.first[33] ) );

        CHECK_THAT( 4.              , WithinRel( linear.second[0] ) );
        CHECK_THAT( 3.90060968219886, WithinRel( linear.second[1] ) );
        CHECK_THAT( 3.80916492202280, WithinRel( linear.second[2] ) );
        CHECK_THAT( 3.64618501493277, WithinRel( linear.second[3] ) );
        CHECK_THAT( 3.50476727724719, WithinRel( linear.second[4] ) );
        CHECK_THAT( 3.38045777463177, WithinRel( linear.second[5] ) );
        CHECK_THAT( 3.27000139455183, WithinRel( linear.second[6] ) );
        CHECK_THAT( 3.17095506211775, WithinRel( linear.second[7] ) );
        CHECK_THAT( 3.08144362036884, WithinRel( linear.second[8] ) );
        CHECK_THAT( 3.              , WithinRel( linear.second[9] ) );
        CHECK_THAT( 2.82352941176471, WithinRel( linear.second[10] ) );
        CHECK_THAT( 2.66666666666667, WithinRel( linear.second[11] ) );
        CHECK_THAT( 2.52631578947368, WithinRel( linear.second[12] ) );
        CHECK_THAT( 2.4             , WithinRel( linear.second[13] ) );
        CHECK_THAT( 2.28571428571429, WithinRel( linear.second[14] ) );
        CHECK_THAT( 2.18181818181818, WithinRel( linear.second[15] ) );
        CHECK_THAT( 2.08695652173913, WithinRel( linear.second[16] ) );
        CHECK_THAT( 2.              , WithinRel( linear.second[17] ) );
        CHECK_THAT( 1.90306670505059, WithinRel( linear.second[18] ) );
        CHECK_THAT( 1.81264991535569, WithinRel( linear.second[19] ) );
        CHECK_THAT( 1.72819403587833, WithinRel( linear.second[20] ) );
        CHECK_THAT( 1.64920047955189, WithinRel( linear.second[21] ) );
        CHECK_THAT( 1.57522086581409, WithinRel( linear.second[22] ) );
        CHECK_THAT( 1.50585114003178, WithinRel( linear.second[23] ) );
        CHECK_THAT( 1.44072647484858, WithinRel( linear.second[24] ) );
        CHECK_THAT( 1.37951683753791, WithinRel( linear.second[25] ) );
        CHECK_THAT( 1.32192312633766, WithinRel( linear.second[26] ) );
        CHECK_THAT( 1.26767379428859, WithinRel( linear.second[27] ) );
        CHECK_THAT( 1.21652189193419, WithinRel( linear.second[28] ) );
        CHECK_THAT( 1.16824247087599, WithinRel( linear.second[29] ) );
        CHECK_THAT( 1.12263029902043, WithinRel( linear.second[30] ) );
        CHECK_THAT( 1.07949784572851, WithinRel( linear.second[31] ) );
        CHECK_THAT( 1.03867350124975, WithinRel( linear.second[32] ) );
        CHECK_THAT( 1.              , WithinRel( linear.second[33] ) );
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
