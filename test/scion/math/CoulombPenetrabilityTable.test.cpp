// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "scion/math/CoulombPenetrabilityTable.hpp"
#include "scion/math/ConstantWeightFunction.hpp"
#include "scion/math/MeanWeightFunction.hpp"

// other includes
#include "utility/IteratorView.hpp"

// convenience typedefs
using namespace njoy::scion;
template < typename X, typename Y = X,
           typename XContainer = std::vector< X >,
           typename YContainer = std::vector< Y > >
using CoulombPenetrabilityTable = math::CoulombPenetrabilityTable< X, Y, XContainer, YContainer >;
template < typename X > using IntervalDomain = math::IntervalDomain< X >;
template < typename X > using OpenDomain = math::OpenDomain< X >;
using InterpolationType = interpolation::InterpolationType;
template < typename X, typename Y = X, typename W = X >
using ConstantWeightFunction = math::ConstantWeightFunction< X, W >;
template < typename X, typename Y = X, typename W = X >
using MeanWeightFunction = math::MeanWeightFunction< X >;

SCENARIO( "CoulombPenetrabilityTable" ) {

  ConstantWeightFunction< double > constant( 1. );
  MeanWeightFunction< double > mean;

  GIVEN( "tabulated data" ) {

    WHEN( "the data is given explicitly using vectors" ) {

      const std::vector< double > x = { 2.0, 3.0, 5.0, 7.0 };
      const std::vector< double > y = { 10., 17.735176446201578, 26.437218001252052, 30. };
      const double threshold = 0.3;

      CoulombPenetrabilityTable< double, double > chunk( std::move( x ), std::move( y ), std::move( threshold ) );

      // Unit test answers were generated using a Python script that evaluated the function on a
      // dense grid using the numpy linspace function, and integrated over regions using the
      // numpy trapezoid function.

      THEN( "a CoulombPenetrabilityTable can be constructed and members can be tested" ) {

        CHECK( InterpolationType::CoulombPenetrability == chunk.interpolation() );
        CHECK( 4 == chunk.numberPoints() );
        CHECK( 4 == chunk.x().size() );
        CHECK( 4 == chunk.y().size() );
        CHECK_THAT( 2., WithinRel( chunk.x()[0] ) );
        CHECK_THAT( 3., WithinRel( chunk.x()[1] ) );
        CHECK_THAT( 5., WithinRel( chunk.x()[2] ) );
        CHECK_THAT( 7., WithinRel( chunk.x()[3] ) );
        CHECK_THAT( 10., WithinRel( chunk.y()[0] ) );
        CHECK_THAT( 17.735176446201578, WithinRel( chunk.y()[1] ) );
        CHECK_THAT( 26.437218001252052, WithinRel( chunk.y()[2] ) );
        CHECK_THAT( 30., WithinRel( chunk.y()[3] ) );

        CHECK_THAT( 0.3, WithinRel( chunk.threshold() ) );

        CHECK( true == std::holds_alternative< IntervalDomain< double > >( chunk.domain() ) );
      } // THEN

      THEN( "a CoulombPenetrabilityTable can be evaluated" ) {

        // values of x in the x grid
        CHECK_THAT( 10., WithinRel( chunk( 2. ) ) );
        CHECK_THAT( 17.735176446201578, WithinRel( chunk( 3. ) ) );
        CHECK_THAT( 26.437218001252052, WithinRel( chunk( 5. ) ) );
        CHECK_THAT( 30., WithinRel( chunk( 7. ) ) );

        // values of x outside the x grid
        CHECK_THAT( 0., WithinRel( chunk( 1.5 ) ) );
        CHECK_THAT( 0., WithinRel( chunk( 35. ) ) );

        // values of x inside the x grid
        CHECK_THAT( 27.658122472732494, WithinRel( chunk( 5.5 ) ) );
        CHECK_THAT( 24.910475969087816, WithinRel( chunk( 4.5 ) ) );
      } // THEN

      THEN( "the domain can be tested" ) {

        CHECK( true == chunk.isInside( 2.0 ) );
        CHECK( true == chunk.isInside( 3.0 ) );
        CHECK( true == chunk.isInside( 7.0 ) );

        CHECK( false == chunk.isContained( 2.0 ) );
        CHECK( true == chunk.isContained( 3.0 ) );
        CHECK( false == chunk.isContained( 7.0 ) );

        CHECK( true == chunk.isSameDomain( IntervalDomain< double >( 2., 7. ) ) );
        CHECK( false == chunk.isSameDomain( IntervalDomain< double >( 0., 4. ) ) );
        CHECK( false == chunk.isSameDomain( OpenDomain< double >() ) );
      } // THEN

      THEN( "the integral can be calculated with constant and mean WFs" ) {

        CHECK_THAT( 116.47154112769871, WithinRel( chunk.integrate( constant ), 1e-8 ) );
        CHECK_THAT( 563.4270027081915, WithinRel( chunk.integrate( mean ), 1e-8 ) );
      } // THEN

      THEN( "the cumulative integral can be calculated" ) {

        auto cumulative = chunk.cumulativeIntegrate( 0., constant );
        CHECK( 4 == cumulative.size() );
        CHECK_THAT( 0. , WithinRel( cumulative[0] ) );
        CHECK_THAT( 14.080978126372528, WithinRel( cumulative[1], 1e-8 ) );
        CHECK_THAT( 59.484310860195265 , WithinRel( cumulative[2], 1e-8 ) );
        CHECK_THAT( 116.47154112769871, WithinRel( cumulative[3], 1e-8 ) );
      } // THEN


      THEN( "the table can be linearised" ) {

        auto linear = chunk.linearise();

        CHECK_THAT( 2.25, WithinRel( linear.first[2] ) );
        CHECK_THAT( 12.169490587611747, WithinRel( linear.second[2] ) );

        CHECK_THAT( 3.25, WithinRel( linear.first[10] ) );
        CHECK_THAT( 19.265892760109487, WithinRel( linear.second[10] ) );
      } // THEN

    } // WHEN
  } // GIVEN

  GIVEN( "invalid data for a CoulombPenetrabilityTable object" ) {

    WHEN( "there are not enough values in the x or y grid" ) {

      std::vector< double > empty = {};
      std::vector< double > one = { 1. };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( CoulombPenetrabilityTable< double, double >( empty, empty, 0.0 ) );
        CHECK_THROWS( CoulombPenetrabilityTable< double, double >( one, one, 0.0 ) );
      } // THEN
    } // WHEN

    WHEN( "the x and y grid do not have the same number of points" ) {

      std::vector< double > x = { 1., 2., 3., 4. };
      std::vector< double > y = { 4., 3., 2. };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( CoulombPenetrabilityTable< double, double >( std::move( x ), std::move( y ) , 0.0 ) );
      } // THEN
    } // WHEN

    WHEN( "the x grid is not sorted" ) {

      std::vector< double > x = { 1., 3., 2., 4. };
      std::vector< double > y = { 4., 3., 2., 1. };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( CoulombPenetrabilityTable< double, double >( std::move( x ), std::move( y ), 0.0 ) );
      } // THEN
    } // WHEN

    WHEN( "the x grid has a duplicate point" ) {

      std::vector< double > x = { 1., 2., 2., 4. };
      std::vector< double > y = { 4., 3., 2., 1. };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( CoulombPenetrabilityTable< double, double >( std::move( x ), std::move( y ), 0.0 ) );
      } // THEN
    } // WHEN

    WHEN( "the x grid has points below the threshold" ) {

      std::vector< double > x = { 1., 2., 2.5, 4. };
      std::vector< double > y = { 4., 3., 2., 1. };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( CoulombPenetrabilityTable< double, double >( std::move( x ), std::move( y ), 1.5 ) );
      } // THEN
    } // WHEN

  } // GIVEN
} // SCENARIO
