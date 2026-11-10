// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "scion/integration/integral.hpp"
#include "scion/integration/LinearLinear.hpp"
#include "scion/interpolation/LinearLinear.hpp"

// other includes

// convenience typedefs
using namespace njoy::scion;

SCENARIO( "integrate" ) {

  interpolation::LinearLinear interpolator;
  integration::LinearLinear integrator;

  GIVEN( "tabulated x and y values" ) {

    std::vector< double > x = { 1., 2., 3, 4, 5. };
    std::vector< double > y = { 5., 4., 3, 2, 1. };

    WHEN( "an analytical integrator is applied" ) {

      THEN( "the integration is performed correctly using iterators" ) {

        // over the entire table
        auto xbegin = x.begin() + 1;
        auto ybegin = y.begin() + 1;
        CHECK_THAT( 12.0, WithinRel( integration::integral( xbegin, x.end(), ybegin, integrator ) ) );

        // over the first 2 panels of the table
        xbegin = x.begin() + 1;
        ybegin = y.begin() + 1;
        CHECK_THAT(  8.0, WithinRel( integration::integral( xbegin, xbegin + 2, ybegin, integrator ) ) );

        // over the middle 2 panels of the table
        xbegin = x.begin() + 2;
        ybegin = y.begin() + 2;
        CHECK_THAT(  6.0, WithinRel( integration::integral( xbegin, xbegin + 2, ybegin, integrator ) ) );

        // over the last 2 panels of the table
        xbegin = x.begin() + 3;
        ybegin = y.begin() + 3;
        CHECK_THAT(  4.0, WithinRel( integration::integral( xbegin, x.end(), ybegin, integrator ) ) );
      } // THEN

      THEN( "the integration is performed correctly using ranges" ) {

        // over the entire table
        CHECK_THAT( 12.0, WithinRel( integration::integral( x, y, integrator ) ) );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "tabulated x and y values and boundary values" ) {

    std::vector< double > x = { 1., 2., 3., 4., 5. };
    std::vector< double > y = { 5., 4., 3., 2., 1. };

    WHEN( "the group boundaries coincide with the x values" ) {

      std::vector< double > boundaries = { 1., 2., 3., 4., 5. };
      std::vector< double > result = { 0., 0., 0., 0. };

      THEN( "the integral over each group is calculated correctly" ) {

        integration::integral( x.begin(), x.end(), y.begin(),
                               boundaries.begin(), boundaries.end(), result.begin(),
                               interpolator, integrator );

        CHECK( 4 == result.size() );
        CHECK_THAT( 4.5, WithinRel( result[0] ) );
        CHECK_THAT( 3.5, WithinRel( result[1] ) );
        CHECK_THAT( 2.5, WithinRel( result[2] ) );
        CHECK_THAT( 1.5, WithinRel( result[3] ) );
      } // THEN
    } // WHEN

    WHEN( "the groups are finer than the panels" ) {

      std::vector< double > boundaries = { 1., 1.25, 1.5, 2.5, 2.75, 3. };
      std::vector< double > result = { 0., 0., 0., 0., 0. };

      THEN( "the integral over each group is calculated correctly" ) {

        integration::integral( x.begin(), x.end(), y.begin(),
                               boundaries.begin(), boundaries.end(), result.begin(),
                               interpolator, integrator );

        CHECK( 5 == result.size() );
        CHECK_THAT( 1.21875, WithinRel( result[0] ) );
        CHECK_THAT( 1.15625, WithinRel( result[1] ) );
        CHECK_THAT( 4.00000, WithinRel( result[2] ) );
        CHECK_THAT( 0.84375, WithinRel( result[3] ) );
        CHECK_THAT( 0.78125, WithinRel( result[4] ) );
      } // THEN
    } // WHEN

    WHEN( "the groups are coarser than the panels" ) {

      std::vector< double > boundaries = { 1.5, 4.5, 5. };
      std::vector< double > result = { 0., 0. };

      THEN( "the integral over each group is calculated correctly" ) {

        integration::integral( x.begin(), x.end(), y.begin(),
                               boundaries.begin(), boundaries.end(), result.begin(),
                               interpolator, integrator );

        CHECK( 2 == result.size() );
        CHECK_THAT( 9.   , WithinRel( result[0] ) );
        CHECK_THAT( 0.625, WithinRel( result[1] ) );
      } // THEN
    } // WHEN

    WHEN( "there is a single group inside a single panel" ) {

      std::vector< double > boundaries = { 2.25, 2.75 };
      std::vector< double > result = { 0. };

      THEN( "the integral over each group is calculated correctly" ) {

        integration::integral( x.begin(), x.end(), y.begin(),
                               boundaries.begin(), boundaries.end(), result.begin(),
                               interpolator, integrator );

        CHECK( 1 == result.size() );
        CHECK_THAT( 1.75, WithinRel( result[0] ) );
      } // THEN
    } // WHEN

    WHEN( "the groups extend beyond the tabulated data" ) {

      std::vector< double > boundaries = { 0., 0.5, 1.5, 3., 4.5, 6., 7. };
      std::vector< double > result = { 0., 0., 0., 0., 0., 0. };

      THEN( "the integral over each group is calculated correctly" ) {

        integration::integral( x.begin(), x.end(), y.begin(),
                               boundaries.begin(), boundaries.end(), result.begin(),
                               interpolator, integrator );

        CHECK( 6 == result.size() );
        CHECK_THAT( 0.   , WithinRel( result[0] ) );
        CHECK_THAT( 2.375, WithinRel( result[1] ) );
        CHECK_THAT( 5.625, WithinRel( result[2] ) );
        CHECK_THAT( 3.375, WithinRel( result[3] ) );
        CHECK_THAT( 0.625, WithinRel( result[4] ) );
        CHECK_THAT( 0.   , WithinRel( result[5] ) );
      } // THEN
    } // WHEN

    WHEN( "a single group contains the tabulated data" ) {

      std::vector< double > boundaries = { 0., 10. };
      std::vector< double > result = { 0. };

      THEN( "the integral over each group is calculated correctly" ) {

        integration::integral( x.begin(), x.end(), y.begin(),
                               boundaries.begin(), boundaries.end(), result.begin(),
                               interpolator, integrator );

        CHECK( 1 == result.size() );
        CHECK_THAT( 12., WithinRel( result[0] ) );
      } // THEN
    } // WHEN

    WHEN( "all groups are below or above the tabulated data" ) {

      std::vector< double > boundaries1 = { 0., 0.5, 1. };
      std::vector< double > boundaries2 = { 5., 6., 7. };
      std::vector< double > below = { 0., 0. };
      std::vector< double > above = { 0., 0. };

      THEN( "the integral over each group is zero" ) {

        integration::integral( x.begin(), x.end(), y.begin(),
                               boundaries1.begin(), boundaries1.end(), below.begin(),
                               interpolator, integrator );

        CHECK( 2 == below.size() );
        CHECK_THAT( 0., WithinRel( below[0] ) );
        CHECK_THAT( 0., WithinRel( below[1] ) );

        integration::integral( x.begin(), x.end(), y.begin(),
                               boundaries2.begin(), boundaries2.end(), above.begin(),
                               interpolator, integrator );

        CHECK( 2 == above.size() );
        CHECK_THAT( 0., WithinRel( above[0] ) );
        CHECK_THAT( 0., WithinRel( above[1] ) );
      } // THEN
    } // WHEN

    WHEN( "an existing result is provided" ) {

      std::vector< double > boundaries = { 0., 2.5, 10. };
      std::vector< double > result = { 1., 2. };

      THEN( "the integrals are accumulated" ) {

        integration::integral( x.begin(), x.end(), y.begin(),
                               boundaries.begin(), boundaries.end(), result.begin(),
                               interpolator, integrator );

        CHECK_THAT( 7.375, WithinRel( result[0] ) );
        CHECK_THAT( 7.625, WithinRel( result[1] ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
