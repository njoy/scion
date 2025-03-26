// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "scion/integration/integrate.hpp"
#include "scion/integration/LinearLinear.hpp"

// other includes

// convenience typedefs
using namespace njoy::scion;

SCENARIO( "integrate" ) {

  GIVEN( "tabulated x and y values" ) {

    std::vector< double > x = { 1., 2., 3, 4, 5. };
    std::vector< double > y = { 5., 4., 3, 2, 1. };

    WHEN( "an analytical integrator is applied" ) {

      integration::LinearLinear integrator;

      THEN( "the integration is performed correctly using iterators" ) {

        // over the entire table
        auto xbegin = x.begin() + 1;
        auto ybegin = y.begin() + 1;
        CHECK_THAT( 12.0, WithinRel( integration::integrate( xbegin, x.end(), ybegin, integrator ) ) );

        // over the first 2 panels of the table
        xbegin = x.begin() + 1;
        ybegin = y.begin() + 1;
        CHECK_THAT(  8.0, WithinRel( integration::integrate( xbegin, xbegin + 2, ybegin, integrator ) ) );

        // over the middle 2 panels of the table
        xbegin = x.begin() + 2;
        ybegin = y.begin() + 2;
        CHECK_THAT(  6.0, WithinRel( integration::integrate( xbegin, xbegin + 2, ybegin, integrator ) ) );

        // over the last 2 panels of the table
        xbegin = x.begin() + 3;
        ybegin = y.begin() + 3;
        CHECK_THAT(  4.0, WithinRel( integration::integrate( xbegin, x.end(), ybegin, integrator ) ) );
      } // THEN

      THEN( "the integration is performed correctly using ranges" ) {

        // over the entire table
        CHECK_THAT( 12.0, WithinRel( integration::integrate( x, y, integrator ) ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
