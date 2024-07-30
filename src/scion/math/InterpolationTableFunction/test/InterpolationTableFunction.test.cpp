// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "scion/math/InterpolationTableFunction.hpp"

// other includes
#include "scion/math/InterpolationTable.hpp"
#include "scion/math/LegendreSeries.hpp"

// convenience typedefs
using namespace njoy::scion;
template < typename X, typename Y = X >
using InterpolationTable = math::InterpolationTable< X, Y >;
template < typename X, typename Y = X >
using LegendreSeries = math::LegendreSeries< X, Y >;
template < typename X, typename F, typename Y = X, typename Z = X >
using InterpolationTableFunction = math::InterpolationTableFunction< X, F, Y, Z >;
using InterpolationType = interpolation::InterpolationType;

using Table2D = InterpolationTableFunction< double, InterpolationTable< double > >;
using Legendre2D = InterpolationTableFunction< double, LegendreSeries< double > >;

SCENARIO( "InterpolationTableFunction" ) {

  GIVEN( "linearised data without boundaries and no jumps" ) {

    WHEN( "the data is given explicitly" ) {

      const std::vector< double > x = { 1., 2., 3., 4. };
      const std::vector< InterpolationTable< double > > f = {

        { { -1., +1. }, { 0.5, 0.5 } },
        { { -1., 0., +1. }, { 0.49, 0.5, 0.51 } },
        { { -1., 0., +1. }, { 0.4, 0.5, 0.6 } },
        { { -1., +1. }, { 0.1, 0.9 } }
      };
      InterpolationType interpolant = InterpolationType::LinearLinear;

      Table2D chunk( std::move( x ), std::move( f ), interpolant );

      THEN( "an InterpolationTableFunction can be constructed and members can be tested" ) {

        CHECK( 4 == chunk.numberPoints() );
        CHECK( 1 == chunk.numberRegions() );
        CHECK( 4 == chunk.x().size() );
        CHECK( 4 == chunk.f().size() );
        CHECK( 1 == chunk.boundaries().size() );
        CHECK( 1 == chunk.interpolants().size() );
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
        CHECK_THAT( -1.  , WithinRel( chunk.f()[3].x()[0] ) );
        CHECK_THAT(  1.  , WithinRel( chunk.f()[3].x()[1] ) );
        CHECK_THAT(  0.1 , WithinRel( chunk.f()[3].y()[0] ) );
        CHECK_THAT(  0.9 , WithinRel( chunk.f()[3].y()[1] ) );
        CHECK( 3 == chunk.boundaries()[0] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );
      } // THEN

      THEN( "an InterpolationTableFunction can be evaluated" ) {

        // values of x in the x grid
        CHECK_THAT( 0.5  , WithinRel( chunk( 1., -0.5 ) ) );
        CHECK_THAT( 0.495, WithinRel( chunk( 2., -0.5 ) ) );
        CHECK_THAT( 0.45 , WithinRel( chunk( 3., -0.5 ) ) );
        CHECK_THAT( 0.3  , WithinRel( chunk( 4., -0.5 ) ) );

        // values of x outside the x grid
        CHECK_THAT( 0., WithinRel( chunk( 0., -0.5 ) ) );
        CHECK_THAT( 0., WithinRel( chunk( 5., -0.5 ) ) );

        // values of x inside the x grid
        CHECK_THAT( 0.4975, WithinRel( chunk( 1.5, -0.5 ) ) );
        CHECK_THAT( 0.4725, WithinRel( chunk( 2.5, -0.5 ) ) );
        CHECK_THAT( 0.375 , WithinRel( chunk( 3.5, -0.5 ) ) );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "legendre series without boundaries and no jumps" ) {

    // note : the Legendre coefficients were chosen so that this
    //        test case linearises to the previous tabulated version.

    WHEN( "the data is given explicitly" ) {

      const std::vector< double > x = { 1., 2., 3., 4. };
      const std::vector< LegendreSeries< double > > f = {

        { { 0.5 } },
        { { 0.5, 0.01 } },
        { { 0.5, 0.1 } },
        { { 0.5, 0.4 } }
      };
      InterpolationType interpolant = InterpolationType::LinearLinear;

      Legendre2D chunk( std::move( x ), std::move( f ), interpolant );

      THEN( "an InterpolationTableFunction can be constructed and members can be tested" ) {

        CHECK( 4 == chunk.numberPoints() );
        CHECK( 1 == chunk.numberRegions() );
        CHECK( 4 == chunk.x().size() );
        CHECK( 4 == chunk.f().size() );
        CHECK( 1 == chunk.boundaries().size() );
        CHECK( 1 == chunk.interpolants().size() );
        CHECK_THAT( 1., WithinRel( chunk.x()[0] ) );
        CHECK_THAT( 2., WithinRel( chunk.x()[1] ) );
        CHECK_THAT( 3., WithinRel( chunk.x()[2] ) );
        CHECK_THAT( 4., WithinRel( chunk.x()[3] ) );
        CHECK( 1 == chunk.f()[0].coefficients().size() );
        CHECK( 2 == chunk.f()[1].coefficients().size() );
        CHECK( 2 == chunk.f()[2].coefficients().size() );
        CHECK( 2 == chunk.f()[3].coefficients().size() );
        CHECK_THAT( 0.5 , WithinRel( chunk.f()[0].coefficients()[0] ) );
        CHECK_THAT( 0.5 , WithinRel( chunk.f()[1].coefficients()[0] ) );
        CHECK_THAT( 0.01, WithinRel( chunk.f()[1].coefficients()[1] ) );
        CHECK_THAT( 0.5 , WithinRel( chunk.f()[2].coefficients()[0] ) );
        CHECK_THAT( 0.1 , WithinRel( chunk.f()[2].coefficients()[1] ) );
        CHECK_THAT( 0.5 , WithinRel( chunk.f()[3].coefficients()[0] ) );
        CHECK_THAT( 0.4 , WithinRel( chunk.f()[3].coefficients()[1] ) );
        CHECK( 3 == chunk.boundaries()[0] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );
      } // THEN

      THEN( "an InterpolationTableFunction can be evaluated" ) {

        // values of x in the x grid
        CHECK_THAT( 0.5  , WithinRel( chunk( 1., -0.5 ) ) );
        CHECK_THAT( 0.495, WithinRel( chunk( 2., -0.5 ) ) );
        CHECK_THAT( 0.45 , WithinRel( chunk( 3., -0.5 ) ) );
        CHECK_THAT( 0.3  , WithinRel( chunk( 4., -0.5 ) ) );

        // values of x outside the x grid
        CHECK_THAT( 0., WithinRel( chunk( 0., -0.5 ) ) );
        CHECK_THAT( 0., WithinRel( chunk( 5., -0.5 ) ) );

        // values of x inside the x grid
        CHECK_THAT( 0.4975, WithinRel( chunk( 1.5, -0.5 ) ) );
        CHECK_THAT( 0.4725, WithinRel( chunk( 2.5, -0.5 ) ) );
        CHECK_THAT( 0.375 , WithinRel( chunk( 3.5, -0.5 ) ) );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "invalid data for an InterpolationTableFunction object" ) {

    WHEN( "there are not enough values in the x or f(y) grid" ) {

      std::vector< double > xempty = {};
      std::vector< double > xone = { 1. };
      std::vector< InterpolationTable< double > > fempty = {};
      std::vector< InterpolationTable< double > > fone = { { { 1., 2. }, { 3., 4. } } };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( Table2D( xempty, fempty ) );
        CHECK_THROWS( Table2D( xone, fone ) );
        CHECK_THROWS( Table2D( xempty, fone ) );
        CHECK_THROWS( Table2D( xone, fempty ) );
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

        CHECK_THROWS( Table2D( std::move( x ), std::move( f ) ) );
      } // THEN
    } // WHEN

    WHEN( "the boundaries and interpolants do not have the same size" ) {

      const std::vector< double > x = { 1., 2., 3., 4. };
      const std::vector< InterpolationTable< double > > f = {

        { { -1., +1. }, { 0.5, 0.5 } },
        { { -1., 0., +1. }, { 0.49, 0.5, 0.51 } },
        { { -1., 0., +1. }, { 0.4, 0.5, 0.6 } },
        { { -1., +1. }, { 0.1, 0.9 } }
      };
      std::vector< std::size_t > boundaries = { 3 };
      std::vector< InterpolationType > interpolants = {};

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( Table2D( std::move( x ), std::move( f ),
                                 std::move( boundaries ),
                                 std::move( interpolants ) ) );
      } // THEN
    } // WHEN

    WHEN( "the x grid is not sorted" ) {

      const std::vector< double > x = { 1., 3., 2., 4. };
      const std::vector< InterpolationTable< double > > f = {

        { { -1., +1. }, { 0.5, 0.5 } },
        { { -1., 0., +1. }, { 0.49, 0.5, 0.51 } },
        { { -1., 0., +1. }, { 0.4, 0.5, 0.6 } },
        { { -1., +1. }, { 0.1, 0.9 } }
      };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( Table2D( std::move( x ), std::move( f ) ) );
      } // THEN
    } // WHEN

    WHEN( "the x grid contains a triple x value" ) {

      const std::vector< double > x = { 1., 2., 2., 2., 4. };
      const std::vector< InterpolationTable< double > > f = {

        { { -1., +1. }, { 0.5, 0.5 } },
        { { -1., 0., +1. }, { 0.49, 0.5, 0.51 } },
        { { -1., 0., +1. }, { 0.4, 0.5, 0.6 } },
        { { -1., +1. }, { 0.1, 0.9 } },
        { { -1., +1. }, { 0.3, 0.7 } }
      };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( Table2D( std::move( x ), std::move( f ) ) );
      } // THEN
    } // WHEN

    WHEN( "the x grid has a jump at the beginning" ) {

      const std::vector< double > x = { 1., 1., 3., 4. };
      const std::vector< InterpolationTable< double > > f = {

        { { -1., +1. }, { 0.5, 0.5 } },
        { { -1., 0., +1. }, { 0.49, 0.5, 0.51 } },
        { { -1., 0., +1. }, { 0.4, 0.5, 0.6 } },
        { { -1., +1. }, { 0.1, 0.9 } }
      };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( Table2D( std::move( x ), std::move( f ) ) );
      } // THEN
    } // WHEN

    WHEN( "the x grid has a jump at the end" ) {

      const std::vector< double > x = { 1., 2., 4., 4. };
      const std::vector< InterpolationTable< double > > f = {

        { { -1., +1. }, { 0.5, 0.5 } },
        { { -1., 0., +1. }, { 0.49, 0.5, 0.51 } },
        { { -1., 0., +1. }, { 0.4, 0.5, 0.6 } },
        { { -1., +1. }, { 0.1, 0.9 } }
      };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( Table2D( std::move( x ), std::move( f ) ) );
      } // THEN
    } // WHEN

    WHEN( "the last boundary does not point to the last point" ) {

      const std::vector< double > x = { 1., 2., 3., 4. };
      const std::vector< InterpolationTable< double > > f = {

        { { -1., +1. }, { 0.5, 0.5 } },
        { { -1., 0., +1. }, { 0.49, 0.5, 0.51 } },
        { { -1., 0., +1. }, { 0.4, 0.5, 0.6 } },
        { { -1., +1. }, { 0.1, 0.9 } }
      };
      std::vector< std::size_t > boundaries = { 2 };
      std::vector< InterpolationType > interpolants = { InterpolationType::LinearLinear };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( Table2D( std::move( x ), std::move( f ),
                               std::move( boundaries ), std::move( interpolants ) ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
