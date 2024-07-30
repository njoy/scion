// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "scion/math/InterpolationTableFunction.hpp"

// other includes
#include "scion/math/InterpolationTable.hpp"

// convenience typedefs
using namespace njoy::scion;
template < typename X, typename Y = X >
using InterpolationTable = math::InterpolationTable< X, Y >;
template < typename X, typename F, typename Y = X, typename Z = X >
using InterpolationTableFunction = math::InterpolationTableFunction< X, F, Y, Z >;
using InterpolationType = interpolation::InterpolationType;

SCENARIO( "InterpolationTable" ) {

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

      InterpolationTableFunction< double, InterpolationTable< double > >
      chunk( std::move( x ), std::move( f ), interpolant );

      THEN( "an InterpolationTable can be constructed and members can be tested" ) {

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
        CHECK_THAT( -1. , WithinRel( chunk.f()[3].x()[0] ) );
        CHECK_THAT(  1. , WithinRel( chunk.f()[3].x()[1] ) );
        CHECK_THAT(  0.1, WithinRel( chunk.f()[3].y()[0] ) );
        CHECK_THAT(  0.9, WithinRel( chunk.f()[3].y()[1] ) );
        CHECK( 3 == chunk.boundaries()[0] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );
      } // THEN

      THEN( "an InterpolationTable can be evaluated" ) {

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

//  GIVEN( "invalid data for an InterpolationTable object" ) {
//
//    WHEN( "there are not enough values in the x or y grid" ) {
//
//      std::vector< double > empty = {};
//      std::vector< double > one = { 1. };
//
//      THEN( "an exception is thrown" ) {
//
//        CHECK_THROWS( InterpolationTable< double >( empty, empty ) );
//        CHECK_THROWS( InterpolationTable< double >( one, one ) );
//      } // THEN
//    } // WHEN
//
//    WHEN( "the x and y grid do not have the same number of points" ) {
//
//      std::vector< double > x = { 1., 2., 3., 4. };
//      std::vector< double > y = { 4., 3., 2. };
//
//      THEN( "an exception is thrown" ) {
//
//        CHECK_THROWS( InterpolationTable< double >( std::move( x ), std::move( y ) ) );
//      } // THEN
//    } // WHEN
//
//    WHEN( "the boundaries and interpolants do not have the same size" ) {
//
//      std::vector< double > x = { 1., 2., 3., 4. };
//      std::vector< double > y = { 4., 3., 2., 1. };
//      std::vector< std::size_t > boundaries = { 3 };
//      std::vector< InterpolationType > interpolants = {};
//
//      THEN( "an exception is thrown" ) {
//
//        CHECK_THROWS( InterpolationTable< double >( std::move( x ), std::move( y ),
//                                                    std::move( boundaries ),
//                                                    std::move( interpolants ) ) );
//      } // THEN
//    } // WHEN
//
//    WHEN( "the x grid is not sorted" ) {
//
//      std::vector< double > x = { 1., 3., 2., 4. };
//      std::vector< double > y = { 4., 3., 2., 1. };
//
//      THEN( "an exception is thrown" ) {
//
//        CHECK_THROWS( InterpolationTable< double >( std::move( x ), std::move( y ) ) );
//      } // THEN
//    } // WHEN
//
//    WHEN( "the x grid contains a triple x value" ) {
//
//      std::vector< double > x = { 1., 2., 2., 2., 3., 4. };
//      std::vector< double > y = { 4., 3., 3., 3., 2., 1. };
//
//      THEN( "an exception is thrown" ) {
//
//        CHECK_THROWS( InterpolationTable< double >( std::move( x ), std::move( y ) ) );
//      } // THEN
//    } // WHEN
//
//    WHEN( "the x grid has a jump at the beginning" ) {
//
//      std::vector< double > x = { 1., 1., 3., 4. };
//      std::vector< double > y = { 4., 3., 1., 4. };
//
//      THEN( "an exception is thrown" ) {
//
//        CHECK_THROWS( InterpolationTable< double >( std::move( x ), std::move( y ) ) );
//      } // THEN
//    } // WHEN
//
//    WHEN( "the x grid has a jump at the end" ) {
//
//      std::vector< double > x = { 1., 2., 4., 4. };
//      std::vector< double > y = { 4., 3., 1., 4. };
//
//      THEN( "an exception is thrown" ) {
//
//        CHECK_THROWS( InterpolationTable< double >( std::move( x ), std::move( y ) ) );
//      } // THEN
//    } // WHEN
//
//    WHEN( "the last boundary does not point to the last point" ) {
//
//      std::vector< double > x = { 1., 2., 4., 4. };
//      std::vector< double > y = { 4., 3., 1., 4. };
//      std::vector< std::size_t > boundaries = { 2 };
//      std::vector< InterpolationType > interpolants = { InterpolationType::LinearLinear };
//
//      THEN( "an exception is thrown" ) {
//
//        CHECK_THROWS( InterpolationTable< double >( std::move( x ), std::move( y ),
//                                                    std::move( boundaries ),
//                                                    std::move( interpolants ) ) );
//      } // THEN
//    } // WHEN
//  } // GIVEN
} // SCENARIO
