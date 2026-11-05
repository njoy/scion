// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "scion/math/LinearLinearTable.hpp"

// other includes
#include "utility/IteratorView.hpp"
#include "scion/math/ConstantWeightFunction.hpp"
#include "scion/math/MeanWeightFunction.hpp"

// convenience typedefs
using namespace njoy::scion;
template < typename X, typename Y = X,
           typename XContainer = std::vector< X >,
           typename YContainer = std::vector< Y > >
using LinearLinearTable = math::LinearLinearTable< X, Y, XContainer, YContainer >;
using InterpolationType = interpolation::InterpolationType;
template < typename X, typename Y = X, typename W = X >
using ConstantWeightFunction = math::ConstantWeightFunction< X, W >;
template < typename X, typename Y = X, typename W = X >
using MeanWeightFunction = math::MeanWeightFunction< X >;

SCENARIO( "LinearLinearTable" ) {

  ConstantWeightFunction< double > constant( 1. );
  MeanWeightFunction< double > mean;

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

      THEN( "a LinearLinearTable can be evaluated" ) {

        // values of x in the x grid
        CHECK_THAT( 4., WithinRel( chunk( 1. ) ) );
        CHECK_THAT( 3., WithinRel( chunk( 2. ) ) );
        CHECK_THAT( 2., WithinRel( chunk( 3. ) ) );
        CHECK_THAT( 1., WithinRel( chunk( 4. ) ) );

        // values of x outside the x grid
        CHECK_THAT( 0., WithinRel( chunk( 0. ) ) );
        CHECK_THAT( 0., WithinRel( chunk( 5. ) ) );

        // values of x inside the x grid
        CHECK_THAT( 3.5, WithinRel( chunk( 1.5 ) ) );
        CHECK_THAT( 2.5, WithinRel( chunk( 2.5 ) ) );
        CHECK_THAT( 1.5, WithinRel( chunk( 3.5 ) ) );
      } // THEN

      THEN( "a LinearLinearTable can be integrated" ) {

        // ( 4 + 1 ) * 3 / 2 = 7.5
        CHECK_THAT( 7.5, WithinRel( chunk.integrate( constant ) ) );
      } // THEN

      THEN( "the cumulative integral of a LinearLinearTable can be calculated" ) {

        auto cumulative = chunk.cumulativeIntegrate( 0., constant );
        CHECK( 4 == cumulative.size() );
        CHECK_THAT( 0. , WithinRel( cumulative[0] ) );
        CHECK_THAT( 3.5, WithinRel( cumulative[1] ) );
        CHECK_THAT( 6. , WithinRel( cumulative[2] ) );
        CHECK_THAT( 7.5, WithinRel( cumulative[3] ) );
      } // THEN

      THEN( "the first raw moment of a LinearLinearTable can be calculated" ) {

        // f(x) = 5 - x
        // x f(x) = 5 x - x^2
        // primitive = 5 x^2 / 2 - x^3 / 3
        // integral = 5 * 16 / 2 - 64 / 3 - 5 / 2 + 1 / 3
        //          = 75 / 2 -  63 / 3 = 37.5 - 21
        CHECK_THAT( 16.5, WithinRel( chunk.integrate( mean ) ) );
      } // THEN

      THEN( "the integral over a set of groups can be calculated" ) {

        std::vector< double > boundaries = { 0.5, 1.5, 2., 3.25, 5. };

        std::vector< double > integrals = { 0., 0., 0., 0. };
        chunk.integrate( constant, boundaries, integrals );

        CHECK( 4 == integrals.size() );
        CHECK_THAT( 1.875, WithinRel( integrals[0] ) );
        CHECK_THAT( 1.625, WithinRel( integrals[1] ) );
        CHECK_THAT( 2.96875, WithinRel( integrals[2] ) );
        CHECK_THAT( 1.03125, WithinRel( integrals[3] ) );

        std::vector< double > moments = { 0., 0., 0., 0. };
        chunk.integrate( mean, boundaries, moments );

        CHECK( 4 == moments.size() );
        CHECK_THAT( 2.33333333333333, WithinRel( moments[0] ) );
        CHECK_THAT( 2.83333333333333, WithinRel( moments[1] ) );
        CHECK_THAT( 7.63020833333333, WithinRel( moments[2] ) );
        CHECK_THAT( 3.703125        , WithinRel( moments[3] ) );

        CHECK_THAT( chunk.integrate( constant ),
                    WithinRel( integrals[0] + integrals[1] + integrals[2] + integrals[3] ) );
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

      THEN( "a LinearLinearTable can be evaluated" ) {

        // values of x in the x grid
        CHECK_THAT( 4., WithinRel( chunk( 1. ) ) );
        CHECK_THAT( 3., WithinRel( chunk( 2. ) ) );
        CHECK_THAT( 2., WithinRel( chunk( 3. ) ) );
        CHECK_THAT( 1., WithinRel( chunk( 4. ) ) );

        // values of x outside the x grid
        CHECK_THAT( 0., WithinRel( chunk( 0. ) ) );
        CHECK_THAT( 0., WithinRel( chunk( 5. ) ) );

        // values of x inside the x grid
        CHECK_THAT( 3.5, WithinRel( chunk( 1.5 ) ) );
        CHECK_THAT( 1.5, WithinRel( chunk( 3.5 ) ) );
      } // THEN

      THEN( "a LinearLinearTable can be integrated" ) {

        // ( 4 + 1 ) * 3 / 2 = 7.5
        CHECK_THAT( 7.5, WithinRel( chunk.integrate( constant ) ) );
      } // THEN

      THEN( "the cumulative integral of a LinearLinearTable can be calculated" ) {

        auto cumulative = chunk.cumulativeIntegrate( 0., constant );
        CHECK( 4 == cumulative.size() );
        CHECK_THAT( 0. , WithinRel( cumulative[0] ) );
        CHECK_THAT( 3.5, WithinRel( cumulative[1] ) );
        CHECK_THAT( 6. , WithinRel( cumulative[2] ) );
        CHECK_THAT( 7.5, WithinRel( cumulative[3] ) );
      } // THEN

      THEN( "the first raw moment of a LinearLinearTable can be calculated" ) {

        // f(x) = 5 - x
        // x f(x) = 5 x - x^2
        // primitive = 5 x^2 / 2 - x^3 / 3
        // integral = 5 * 16 / 2 - 64 / 3 - 5 / 2 + 1 / 3
        //          = 75 / 2 -  63 / 3 = 37.5 - 21
        CHECK_THAT( 16.5, WithinRel( chunk.integrate( mean ) ) );
      } // THEN

      THEN( "the integral over a set of groups can be calculated" ) {

        std::vector< double > boundaries = { 0.5, 1.5, 2., 3.25, 5. };

        std::vector< double > integrals = { 0., 0., 0., 0. };
        chunk.integrate( constant, boundaries, integrals );

        CHECK( 4 == integrals.size() );
        CHECK_THAT( 1.875, WithinRel( integrals[0] ) );
        CHECK_THAT( 1.625, WithinRel( integrals[1] ) );
        CHECK_THAT( 2.96875, WithinRel( integrals[2] ) );
        CHECK_THAT( 1.03125, WithinRel( integrals[3] ) );

        std::vector< double > moments = { 0., 0., 0., 0. };
        chunk.integrate( mean, boundaries, moments );

        CHECK( 4 == moments.size() );
        CHECK_THAT( 2.33333333333333, WithinRel( moments[0] ) );
        CHECK_THAT( 2.83333333333333, WithinRel( moments[1] ) );
        CHECK_THAT( 7.63020833333333, WithinRel( moments[2] ) );
        CHECK_THAT( 3.703125        , WithinRel( moments[3] ) );

        CHECK_THAT( chunk.integrate( constant ),
                    WithinRel( integrals[0] + integrals[1] + integrals[2] + integrals[3] ) );
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
