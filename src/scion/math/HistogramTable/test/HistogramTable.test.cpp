#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "scion/math/HistogramTable.hpp"

// other includes
#include "utility/IteratorView.hpp"

// convenience typedefs
using namespace njoy::scion;
template < typename X, typename Y = X > using LinearLinearTable = math::LinearLinearTable< X, Y >;
template < typename X, typename Y = X,
           typename XContainer = std::vector< X >,
           typename YContainer = std::vector< Y > >
using HistogramTable = math::HistogramTable< X, Y, XContainer, YContainer >;
template < typename X > using IntervalDomain = math::IntervalDomain< X >;
using InterpolationType = interpolation::InterpolationType;

SCENARIO( "HistogramTable" ) {

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

      THEN( "a HistogramTable can be evaluated" ) {

        // values of x in the x grid
        CHECK( 4. == Approx( chunk.evaluate( 1. ) ) );
        CHECK( 4. == Approx( chunk.evaluate( 2. ) ) );
        CHECK( 3. == Approx( chunk.evaluate( 3. ) ) );
        CHECK( 2. == Approx( chunk.evaluate( 4. ) ) );

        // values of x outside the x grid
        CHECK( 0. == Approx( chunk.evaluate( 0. ) ) );
        CHECK( 0. == Approx( chunk.evaluate( 5. ) ) );

        // values of x inside the x grid
        CHECK( 4. == Approx( chunk.evaluate( 1.5 ) ) );
        CHECK( 3. == Approx( chunk.evaluate( 2.5 ) ) );
        CHECK( 2. == Approx( chunk.evaluate( 3.5 ) ) );
      } // THEN

      THEN( "a HistogramTable can be linearised" ) {

        LinearLinearTable< double > linear = chunk.linearise();

        CHECK( 6 == linear.x().size() );
        CHECK( 6 == linear.y().size() );

        CHECK( 1. == Approx( linear.x()[0] ) );
        CHECK( 2. == Approx( linear.x()[1] ) );
        CHECK( 2. == Approx( linear.x()[2] ) );
        CHECK( 3. == Approx( linear.x()[3] ) );
        CHECK( 3. == Approx( linear.x()[4] ) );
        CHECK( 4. == Approx( linear.x()[5] ) );

        CHECK( 4. == Approx( linear.y()[0] ) );
        CHECK( 4. == Approx( linear.y()[1] ) );
        CHECK( 3. == Approx( linear.y()[2] ) );
        CHECK( 3. == Approx( linear.y()[3] ) );
        CHECK( 2. == Approx( linear.y()[4] ) );
        CHECK( 2. == Approx( linear.y()[5] ) );
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

      THEN( "a HistogramTable can be evaluated" ) {

        // values of x in the x grid
        CHECK( 4. == Approx( chunk.evaluate( 1. ) ) );
        CHECK( 4. == Approx( chunk.evaluate( 2. ) ) );
        CHECK( 3. == Approx( chunk.evaluate( 3. ) ) );
        CHECK( 2. == Approx( chunk.evaluate( 4. ) ) );

        // values of x outside the x grid
        CHECK( 0. == Approx( chunk.evaluate( 0. ) ) );
        CHECK( 0. == Approx( chunk.evaluate( 5. ) ) );

        // values of x inside the x grid
        CHECK( 4. == Approx( chunk.evaluate( 1.5 ) ) );
        CHECK( 3. == Approx( chunk.evaluate( 2.5 ) ) );
        CHECK( 2. == Approx( chunk.evaluate( 3.5 ) ) );
      } // THEN

      THEN( "a HistogramTable can be linearised" ) {

        LinearLinearTable< double > linear = chunk.linearise();

        CHECK( 6 == linear.x().size() );
        CHECK( 6 == linear.y().size() );

        CHECK( 1.    == Approx( linear.x()[0] ) );
        CHECK( 2.    == Approx( linear.x()[1] ) );
        CHECK( 2.    == Approx( linear.x()[2] ) );
        CHECK( 3.    == Approx( linear.x()[3] ) );
        CHECK( 3.    == Approx( linear.x()[4] ) );
        CHECK( 4.    == Approx( linear.x()[5] ) );

        CHECK( 4. == Approx( linear.y()[0] ) );
        CHECK( 4. == Approx( linear.y()[1] ) );
        CHECK( 3. == Approx( linear.y()[2] ) );
        CHECK( 3. == Approx( linear.y()[3] ) );
        CHECK( 2. == Approx( linear.y()[4] ) );
        CHECK( 2. == Approx( linear.y()[5] ) );
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
