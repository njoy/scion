// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "scion/math/HistogramTable.hpp"

// other includes
#include "utility/IteratorView.hpp"
#include "scion/math/ConstantWeightFunction.hpp"
#include "scion/math/MeanWeightFunction.hpp"

// convenience typedefs
using namespace njoy::scion;
template < typename X, typename Y = X,
           typename XContainer = std::vector< X >,
           typename YContainer = std::vector< Y > >
using HistogramTable = math::HistogramTable< X, Y, XContainer, YContainer >;
using InterpolationType = interpolation::InterpolationType;
template < typename X, typename W = X >
using ConstantWeightFunction = math::ConstantWeightFunction< X, W >;
template < typename X, typename W = X >
using MeanWeightFunction = math::MeanWeightFunction< X >;

SCENARIO( "HistogramTable" ) {

  ConstantWeightFunction< double > constant( 1. );
  MeanWeightFunction< double > mean;

  GIVEN( "tabulated data" ) {

    WHEN( "the data is given explicitly using vectors" ) {

      const std::vector< double > x = { 1., 2., 3., 4. };
      const std::vector< double > y = { 4., 3., 2., 1. };

      HistogramTable< double > chunk( std::move( x ), std::move( y ) );

      THEN( "a HistogramTable can be constructed and members can be tested" ) {

        CHECK( InterpolationType::Histogram == chunk.interpolation() );
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

        CHECK_THAT( 1., WithinRel( chunk.lowerLimit() ) );
        CHECK_THAT( 4., WithinRel( chunk.upperLimit() ) );
      } // THEN

      THEN( "a HistogramTable can be evaluated" ) {

        // values of x in the x grid
        CHECK_THAT( 4., WithinRel( chunk( 1. ) ) );
        CHECK_THAT( 4., WithinRel( chunk( 2. ) ) );
        CHECK_THAT( 3., WithinRel( chunk( 3. ) ) );
        CHECK_THAT( 2., WithinRel( chunk( 4. ) ) );

        // values of x outside the x grid
        CHECK_THAT( 0., WithinRel( chunk( 0. ) ) );
        CHECK_THAT( 0., WithinRel( chunk( 5. ) ) );

        // values of x inside the x grid
        CHECK_THAT( 4., WithinRel( chunk( 1.5 ) ) );
        CHECK_THAT( 3., WithinRel( chunk( 2.5 ) ) );
        CHECK_THAT( 2., WithinRel( chunk( 3.5 ) ) );
      } // THEN

      THEN( "a HistogramTable can be integrated" ) {

        // 4 + 3 + 2 = 9
        CHECK_THAT( 9., WithinRel( chunk.integrate( constant ) ) );
      } // THEN

      THEN( "the cumulative integral of a HistogramTable can be calculated" ) {

        auto cumulative = chunk.cumulativeIntegrate( 0., constant );
        CHECK( 4 == cumulative.size() );
        CHECK_THAT( 0., WithinRel( cumulative[0] ) );
        CHECK_THAT( 4., WithinRel( cumulative[1] ) );
        CHECK_THAT( 7., WithinRel( cumulative[2] ) );
        CHECK_THAT( 9., WithinRel( cumulative[3] ) );
      } // THEN

      THEN( "the integral over a set of groups can be calculated" ) {

        std::vector< double > boundaries = { 0.5, 1.5, 2., 3.25, 5. };

        std::vector< double > integrals = { 0., 0., 0., 0. };
        chunk.integrate( constant, boundaries, integrals );

        CHECK( 4 == integrals.size() );
        CHECK_THAT( 2. , WithinRel( integrals[0] ) );
        CHECK_THAT( 2. , WithinRel( integrals[1] ) );
        CHECK_THAT( 3.5, WithinRel( integrals[2] ) );
        CHECK_THAT( 1.5, WithinRel( integrals[3] ) );

        std::vector< double > moments = { 0., 0., 0., 0. };
        chunk.integrate( mean, boundaries, moments );

        CHECK( 4 == moments.size() );
        CHECK_THAT( 2.5   , WithinRel( moments[0] ) );
        CHECK_THAT( 3.5   , WithinRel( moments[1] ) );
        CHECK_THAT( 9.0625, WithinRel( moments[2] ) );
        CHECK_THAT( 5.4375, WithinRel( moments[3] ) );

        CHECK_THAT( chunk.integrate( constant ),
                    WithinRel( integrals[0] + integrals[1] + integrals[2] + integrals[3] ) );
      } // THEN

      THEN( "the first raw moment of a HistogramTable can be calculated" ) {

        // ( 4 * ( 1 + 2) + 3 * ( 2 + 3 ) + 2 * ( 3 + 4 ) ) / 2 = 20.5
        CHECK_THAT( 20.5, WithinRel( chunk.integrate( mean ) ) );
      } // THEN

      THEN( "the domain can be tested" ) {

        CHECK( true == chunk.isInside( 1.0 ) );
        CHECK( true == chunk.isInside( 2.5 ) );
        CHECK( true == chunk.isInside( 4.0 ) );

        CHECK( false == chunk.isContained( 1.0 ) );
        CHECK( true == chunk.isContained( 2.5 ) );
        CHECK( false == chunk.isContained( 4.0 ) );
      } // THEN

      THEN( "a HistogramTable can be linearised" ) {

        auto linear = chunk.linearise();

        CHECK( 6 == linear.first.size() );
        CHECK( 6 == linear.second.size() );

        CHECK_THAT( 1., WithinRel( linear.first[0] ) );
        CHECK_THAT( 2., WithinRel( linear.first[1] ) );
        CHECK_THAT( 2., WithinRel( linear.first[2] ) );
        CHECK_THAT( 3., WithinRel( linear.first[3] ) );
        CHECK_THAT( 3., WithinRel( linear.first[4] ) );
        CHECK_THAT( 4., WithinRel( linear.first[5] ) );

        CHECK_THAT( 4., WithinRel( linear.second[0] ) );
        CHECK_THAT( 4., WithinRel( linear.second[1] ) );
        CHECK_THAT( 3., WithinRel( linear.second[2] ) );
        CHECK_THAT( 3., WithinRel( linear.second[3] ) );
        CHECK_THAT( 2., WithinRel( linear.second[4] ) );
        CHECK_THAT( 2., WithinRel( linear.second[5] ) );
      } // THEN
    } // WHEN

    WHEN( "the data is given explicitly using iterator views" ) {

      using View = njoy::utility::IteratorView< std::vector< double >::const_iterator >;

      const std::vector< double > xvalues= { 1., 2., 3., 4. };
      const std::vector< double > yvalues = { 4., 3., 2., 1. };

      View x = njoy::utility::make_view( xvalues );
      View y = njoy::utility::make_view( yvalues );

      HistogramTable< double, double, View, View > chunk( std::move( x ), std::move( y ) );

      THEN( "a HistogramTable can be constructed and members can be tested" ) {

        CHECK( InterpolationType::Histogram == chunk.interpolation() );
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

        CHECK_THAT( 1., WithinRel( chunk.lowerLimit() ) );
        CHECK_THAT( 4., WithinRel( chunk.upperLimit() ) );
      } // THEN

      THEN( "a HistogramTable can be evaluated" ) {

        // values of x in the x grid
        CHECK_THAT( 4., WithinRel( chunk( 1. ) ) );
        CHECK_THAT( 4., WithinRel( chunk( 2. ) ) );
        CHECK_THAT( 3., WithinRel( chunk( 3. ) ) );
        CHECK_THAT( 2., WithinRel( chunk( 4. ) ) );

        // values of x outside the x grid
        CHECK_THAT( 0., WithinRel( chunk( 0. ) ) );
        CHECK_THAT( 0., WithinRel( chunk( 5. ) ) );

        // values of x inside the x grid
        CHECK_THAT( 4., WithinRel( chunk( 1.5 ) ) );
        CHECK_THAT( 3., WithinRel( chunk( 2.5 ) ) );
        CHECK_THAT( 2., WithinRel( chunk( 3.5 ) ) );
      } // THEN

      THEN( "a HistogramTable can be integrated" ) {

        // 4 + 3 + 2 = 9
        CHECK_THAT( 9., WithinRel( chunk.integrate( constant ) ) );
      } // THEN

      THEN( "the cumulative integral of a HistogramTable can be calculated" ) {

        auto cumulative = chunk.cumulativeIntegrate( 0., constant );
        CHECK( 4 == cumulative.size() );
        CHECK_THAT( 0., WithinRel( cumulative[0] ) );
        CHECK_THAT( 4., WithinRel( cumulative[1] ) );
        CHECK_THAT( 7., WithinRel( cumulative[2] ) );
        CHECK_THAT( 9., WithinRel( cumulative[3] ) );
      } // THEN

      THEN( "the mean value of a HistogramTable can be calculated" ) {

        // ( 4 * ( 1 + 2) + 3 * ( 2 + 3 ) + 2 * ( 3 + 4 ) ) / 2 = 20.5
        CHECK_THAT( 20.5, WithinRel( chunk.integrate( mean ) ) );
      } // THEN

      THEN( "the integral over a set of groups can be calculated" ) {

        std::vector< double > boundaries = { 0.5, 1.5, 2., 3.25, 5. };

        std::vector< double > integrals = { 0., 0., 0., 0. };
        chunk.integrate( constant, boundaries, integrals );

        CHECK( 4 == integrals.size() );
        CHECK_THAT( 2. , WithinRel( integrals[0] ) );
        CHECK_THAT( 2. , WithinRel( integrals[1] ) );
        CHECK_THAT( 3.5, WithinRel( integrals[2] ) );
        CHECK_THAT( 1.5, WithinRel( integrals[3] ) );

        std::vector< double > moments = { 0., 0., 0., 0. };
        chunk.integrate( mean, boundaries, moments );

        CHECK( 4 == moments.size() );
        CHECK_THAT( 2.5   , WithinRel( moments[0] ) );
        CHECK_THAT( 3.5   , WithinRel( moments[1] ) );
        CHECK_THAT( 9.0625, WithinRel( moments[2] ) );
        CHECK_THAT( 5.4375, WithinRel( moments[3] ) );

        CHECK_THAT( chunk.integrate( constant ),
                    WithinRel( integrals[0] + integrals[1] + integrals[2] + integrals[3] ) );
      } // THEN

      THEN( "the domain can be tested" ) {

        CHECK( true == chunk.isInside( 1.0 ) );
        CHECK( true == chunk.isInside( 2.5 ) );
        CHECK( true == chunk.isInside( 4.0 ) );

        CHECK( false == chunk.isContained( 1.0 ) );
        CHECK( true == chunk.isContained( 2.5 ) );
        CHECK( false == chunk.isContained( 4.0 ) );
      } // THEN

      THEN( "a HistogramTable can be linearised" ) {

        auto linear = chunk.linearise();

        CHECK( 6 == linear.first.size() );
        CHECK( 6 == linear.second.size() );

        CHECK_THAT( 1., WithinRel( linear.first[0] ) );
        CHECK_THAT( 2., WithinRel( linear.first[1] ) );
        CHECK_THAT( 2., WithinRel( linear.first[2] ) );
        CHECK_THAT( 3., WithinRel( linear.first[3] ) );
        CHECK_THAT( 3., WithinRel( linear.first[4] ) );
        CHECK_THAT( 4., WithinRel( linear.first[5] ) );

        CHECK_THAT( 4., WithinRel( linear.second[0] ) );
        CHECK_THAT( 4., WithinRel( linear.second[1] ) );
        CHECK_THAT( 3., WithinRel( linear.second[2] ) );
        CHECK_THAT( 3., WithinRel( linear.second[3] ) );
        CHECK_THAT( 2., WithinRel( linear.second[4] ) );
        CHECK_THAT( 2., WithinRel( linear.second[5] ) );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "invalid data for a HistogramTable object" ) {

    WHEN( "there are not enough values in the x or y grid" ) {

      std::vector< double > empty = {};
      std::vector< double > one = { 1. };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( HistogramTable< double >( empty, empty ) );
        CHECK_THROWS( HistogramTable< double >( one, one ) );
      } // THEN
    } // WHEN

    WHEN( "the x and y grid do not have the same number of points" ) {

      std::vector< double > x = { 1., 2., 3., 4. };
      std::vector< double > y = { 4., 3., 2. };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( HistogramTable< double >( std::move( x ), std::move( y ) ) );
      } // THEN
    } // WHEN

    WHEN( "the x grid is not sorted" ) {

      std::vector< double > x = { 1., 3., 2., 4. };
      std::vector< double > y = { 4., 3., 2., 1. };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( HistogramTable< double >( std::move( x ), std::move( y ) ) );
      } // THEN
    } // WHEN

    WHEN( "the x grid has a duplicate point" ) {

      std::vector< double > x = { 1., 2., 2., 4. };
      std::vector< double > y = { 4., 3., 2., 1. };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( HistogramTable< double >( std::move( x ), std::move( y ) ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
