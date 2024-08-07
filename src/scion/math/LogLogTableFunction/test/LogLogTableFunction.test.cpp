// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "scion/math/InterpolationTable.hpp"
#include "scion/math/LogLogTableFunction.hpp"

// other includes
#include "utility/IteratorView.hpp"

// convenience typedefs
using namespace njoy::scion;
template < typename X, typename Y = X >
using InterpolationTable = math::InterpolationTable< X, Y >;
template < typename X, typename Y = X, typename Z = X,
           typename F = InterpolationTable< X >,
           typename XContainer = std::vector< X >,
           typename FContainer = std::vector< F > >
using LogLogTableFunction = math::LogLogTableFunction< X, Y, Z, F, XContainer, FContainer >;
using InterpolationType = interpolation::InterpolationType;

SCENARIO( "LogLogTableFunction" ) {

  GIVEN( "tabulated x,f(y) data" ) {

    WHEN( "the data is given explicitly using vectors" ) {

      const std::vector< double > x = { 1., 2., 3., 4. };
      const std::vector< InterpolationTable< double > > f = {

        { { -1., +1. }, { 0.5, 0.5 } },
        { { -1., 0., +1. }, { 0.49, 0.5, 0.51 } },
        { { -1., 0., +1. }, { 0.4, 0.5, 0.6 } },
        { { -1., +1. }, { 0.1, 0.9 } }
      };

      LogLogTableFunction< double > chunk( std::move( x ), std::move( f ) );

      THEN( "a LogLogTable can be constructed and members can be tested" ) {

        CHECK( InterpolationType::LogLog == chunk.interpolation() );
        CHECK( 4 == chunk.numberPoints() );
        CHECK( 4 == chunk.x().size() );
        CHECK( 4 == chunk.f().size() );
        CHECK_THAT( 1., WithinRel( chunk.x()[0] ) );
        CHECK_THAT( 2., WithinRel( chunk.x()[1] ) );
        CHECK_THAT( 3., WithinRel( chunk.x()[2] ) );
        CHECK_THAT( 4., WithinRel( chunk.x()[3] ) );
        CHECK( 2 == chunk.f()[0].x().size() );
        CHECK( 2 == chunk.f()[0].y().size() );
        CHECK( 3 == chunk.f()[1].x().size() );
        CHECK( 3 == chunk.f()[1].y().size() );
        CHECK( 3 == chunk.f()[2].x().size() );
        CHECK( 3 == chunk.f()[2].y().size() );
        CHECK( 2 == chunk.f()[3].x().size() );
        CHECK( 2 == chunk.f()[3].y().size() );
        CHECK_THAT( -1.  , WithinRel( chunk.f()[0].x()[0] ) );
        CHECK_THAT(  1.  , WithinRel( chunk.f()[0].x()[1] ) );
        CHECK_THAT(  0.5 , WithinRel( chunk.f()[0].y()[0] ) );
        CHECK_THAT(  0.5 , WithinRel( chunk.f()[0].y()[1] ) );
        CHECK_THAT( -1.  , WithinRel( chunk.f()[1].x()[0] ) );
        CHECK_THAT(  0.  , WithinRel( chunk.f()[1].x()[1] ) );
        CHECK_THAT(  1.  , WithinRel( chunk.f()[1].x()[2] ) );
        CHECK_THAT(  0.49, WithinRel( chunk.f()[1].y()[0] ) );
        CHECK_THAT(  0.5 , WithinRel( chunk.f()[1].y()[1] ) );
        CHECK_THAT(  0.51, WithinRel( chunk.f()[1].y()[2] ) );
        CHECK_THAT( -1.  , WithinRel( chunk.f()[2].x()[0] ) );
        CHECK_THAT(  0.  , WithinRel( chunk.f()[2].x()[1] ) );
        CHECK_THAT(  1.  , WithinRel( chunk.f()[2].x()[2] ) );
        CHECK_THAT(  0.4 , WithinRel( chunk.f()[2].y()[0] ) );
        CHECK_THAT(  0.5 , WithinRel( chunk.f()[2].y()[1] ) );
        CHECK_THAT(  0.6 , WithinRel( chunk.f()[2].y()[2] ) );
        CHECK_THAT( -1. , WithinRel( chunk.f()[3].x()[0] ) );
        CHECK_THAT(  1. , WithinRel( chunk.f()[3].x()[1] ) );
        CHECK_THAT(  0.1, WithinRel( chunk.f()[3].y()[0] ) );
        CHECK_THAT(  0.9, WithinRel( chunk.f()[3].y()[1] ) );
      } // THEN

      THEN( "a LogLogTable can be evaluated" ) {

        // values of x in the x grid
        CHECK_THAT( 0.5  , WithinRel( chunk( 1., -0.5 ) ) );
        CHECK_THAT( 0.495, WithinRel( chunk( 2., -0.5 ) ) );
        CHECK_THAT( 0.45 , WithinRel( chunk( 3., -0.5 ) ) );
        CHECK_THAT( 0.3  , WithinRel( chunk( 4., -0.5 ) ) );

        // values of x outside the x grid
        CHECK_THAT( 0., WithinRel( chunk( 0., -0.5 ) ) );
        CHECK_THAT( 0., WithinRel( chunk( 5., -0.5 ) ) );

        // values of x inside the x grid
        CHECK_THAT( 0.49706908915929, WithinRel( chunk( 1.5, -0.5 ) ) );
        CHECK_THAT( 0.46970497533108, WithinRel( chunk( 2.5, -0.5 ) ) );
        CHECK_THAT( 0.36212316985370, WithinRel( chunk( 3.5, -0.5 ) ) );
      } // THEN
    } // WHEN

    WHEN( "the data is given explicitly using iterator views" ) {

      using XView = njoy::utility::IteratorView< std::vector< double >::const_iterator >;
      using FView = njoy::utility::IteratorView< std::vector< InterpolationTable< double > >::const_iterator >;

      const std::vector< double > xvalues = { 1., 2., 3., 4. };
      const std::vector< InterpolationTable< double > > fvalues = {

        { { -1., +1. }, { 0.5, 0.5 } },
        { { -1., 0., +1. }, { 0.49, 0.5, 0.51 } },
        { { -1., 0., +1. }, { 0.4, 0.5, 0.6 } },
        { { -1., +1. }, { 0.1, 0.9 } }
      };


      XView x = njoy::utility::make_view( xvalues );
      FView f = njoy::utility::make_view( fvalues );

      LogLogTableFunction< double, double, double, InterpolationTable< double >,
                                 XView, FView > chunk( std::move( x ), std::move( f ) );

      THEN( "a LogLogTable can be constructed and members can be tested" ) {

        CHECK( InterpolationType::LogLog == chunk.interpolation() );
        CHECK( 4 == chunk.numberPoints() );
        CHECK( 4 == chunk.x().size() );
        CHECK( 4 == chunk.f().size() );
        CHECK_THAT( 1., WithinRel( chunk.x()[0] ) );
        CHECK_THAT( 2., WithinRel( chunk.x()[1] ) );
        CHECK_THAT( 3., WithinRel( chunk.x()[2] ) );
        CHECK_THAT( 4., WithinRel( chunk.x()[3] ) );
        CHECK( 2 == chunk.f()[0].x().size() );
        CHECK( 2 == chunk.f()[0].y().size() );
        CHECK( 3 == chunk.f()[1].x().size() );
        CHECK( 3 == chunk.f()[1].y().size() );
        CHECK( 3 == chunk.f()[2].x().size() );
        CHECK( 3 == chunk.f()[2].y().size() );
        CHECK( 2 == chunk.f()[3].x().size() );
        CHECK( 2 == chunk.f()[3].y().size() );
        CHECK_THAT( -1.  , WithinRel( chunk.f()[0].x()[0] ) );
        CHECK_THAT(  1.  , WithinRel( chunk.f()[0].x()[1] ) );
        CHECK_THAT(  0.5 , WithinRel( chunk.f()[0].y()[0] ) );
        CHECK_THAT(  0.5 , WithinRel( chunk.f()[0].y()[1] ) );
        CHECK_THAT( -1.  , WithinRel( chunk.f()[1].x()[0] ) );
        CHECK_THAT(  0.  , WithinRel( chunk.f()[1].x()[1] ) );
        CHECK_THAT(  1.  , WithinRel( chunk.f()[1].x()[2] ) );
        CHECK_THAT(  0.49, WithinRel( chunk.f()[1].y()[0] ) );
        CHECK_THAT(  0.5 , WithinRel( chunk.f()[1].y()[1] ) );
        CHECK_THAT(  0.51, WithinRel( chunk.f()[1].y()[2] ) );
        CHECK_THAT( -1.  , WithinRel( chunk.f()[2].x()[0] ) );
        CHECK_THAT(  0.  , WithinRel( chunk.f()[2].x()[1] ) );
        CHECK_THAT(  1.  , WithinRel( chunk.f()[2].x()[2] ) );
        CHECK_THAT(  0.4 , WithinRel( chunk.f()[2].y()[0] ) );
        CHECK_THAT(  0.5 , WithinRel( chunk.f()[2].y()[1] ) );
        CHECK_THAT(  0.6 , WithinRel( chunk.f()[2].y()[2] ) );
        CHECK_THAT( -1. , WithinRel( chunk.f()[3].x()[0] ) );
        CHECK_THAT(  1. , WithinRel( chunk.f()[3].x()[1] ) );
        CHECK_THAT(  0.1, WithinRel( chunk.f()[3].y()[0] ) );
        CHECK_THAT(  0.9, WithinRel( chunk.f()[3].y()[1] ) );
      } // THEN

      THEN( "a LogLogTable can be evaluated" ) {

        // values of x in the x grid
        CHECK_THAT( 0.5  , WithinRel( chunk( 1., -0.5 ) ) );
        CHECK_THAT( 0.495, WithinRel( chunk( 2., -0.5 ) ) );
        CHECK_THAT( 0.45 , WithinRel( chunk( 3., -0.5 ) ) );
        CHECK_THAT( 0.3  , WithinRel( chunk( 4., -0.5 ) ) );

        // values of x outside the x grid
        CHECK_THAT( 0., WithinRel( chunk( 0., -0.5 ) ) );
        CHECK_THAT( 0., WithinRel( chunk( 5., -0.5 ) ) );

        // values of x inside the x grid
        CHECK_THAT( 0.49706908915929, WithinRel( chunk( 1.5, -0.5 ) ) );
        CHECK_THAT( 0.46970497533108, WithinRel( chunk( 2.5, -0.5 ) ) );
        CHECK_THAT( 0.36212316985370, WithinRel( chunk( 3.5, -0.5 ) ) );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "invalid data for a LogLogTable object" ) {

    WHEN( "there are not enough values in the x or f(y) grid" ) {

      std::vector< double > xempty = {};
      std::vector< double > xone = { 1. };
      std::vector< InterpolationTable< double > > fempty = {};
      std::vector< InterpolationTable< double > > fone = { { { 1., 2. }, { 3., 4. } } };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( LogLogTableFunction< double >( xempty, fempty ) );
        CHECK_THROWS( LogLogTableFunction< double >( xone, fone ) );
        CHECK_THROWS( LogLogTableFunction< double >( xempty, fone ) );
        CHECK_THROWS( LogLogTableFunction< double >( xone, fempty ) );
      } // THEN
    } // WHEN

    WHEN( "the x and f(y) grid do not have the same number of points" ) {

      std::vector< double > x = { 1., 2., 3., 4. };
      std::vector< InterpolationTable< double > > f = {

        { { -1., +1. }, { 0.5, 0.5 } },
        { { -1., 0., +1. }, { 0.49, 0.5, 0.51 } },
        { { -1., 0., +1. }, { 0.4, 0.5, 0.6 } }
      };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( LogLogTableFunction< double >( std::move( x ), std::move( f ) ) );
      } // THEN
    } // WHEN

    WHEN( "the x grid is not sorted" ) {

      std::vector< double > x = { 1., 3., 2., 4. };
      std::vector< InterpolationTable< double > > f = {

        { { -1., +1. }, { 0.5, 0.5 } },
        { { -1., 0., +1. }, { 0.49, 0.5, 0.51 } },
        { { -1., 0., +1. }, { 0.4, 0.5, 0.6 } },
        { { -1., +1. }, { 0.1, 0.9 } }
      };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( LogLogTableFunction< double >( std::move( x ), std::move( f ) ) );
      } // THEN
    } // WHEN

    WHEN( "the x grid has a duplicate point" ) {

      std::vector< double > x = { 1., 2., 2., 4. };
      std::vector< InterpolationTable< double > > f = {

        { { -1., +1. }, { 0.5, 0.5 } },
        { { -1., 0., +1. }, { 0.49, 0.5, 0.51 } },
        { { -1., 0., +1. }, { 0.4, 0.5, 0.6 } },
        { { -1., +1. }, { 0.1, 0.9 } }
      };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( LogLogTableFunction< double >( std::move( x ), std::move( f ) ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
