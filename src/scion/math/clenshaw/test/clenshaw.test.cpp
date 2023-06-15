// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "scion/math/clenshaw.hpp"

// other includes

// convenience typedefs
using namespace njoy::scion;

SCENARIO( "clenshaw" ) {

  GIVEN( "valid data for polynomials" ) {

    // polynomial coefficients (from lower order to higher order)
    std::vector< double > order0 = { 1. };
    std::vector< double > order1 = { 1., 2. };
    std::vector< double > order2 = { 1., 2., 3. };
    std::vector< double > order3 = { 1., 2., 3., 4. };

    auto a = [] ( unsigned int k, double x ) -> double
                { return x; };
    auto b = [] ( unsigned int k, double x ) -> double
                { return 0.; };

    WHEN( "the iterators are used" ) {

      THEN( "the polynomials can be evaluated" ) {

        CHECK_THAT(  1., WithinRel( math::clenshaw( order0.rbegin(), order0.rend(), a, b, 1., 0., 0. ) ) );
        CHECK_THAT(  1., WithinRel( math::clenshaw( order1.rbegin(), order1.rend(), a, b, 1., 0., 0. ) ) );
        CHECK_THAT(  1., WithinRel( math::clenshaw( order2.rbegin(), order2.rend(), a, b, 1., 0., 0. ) ) );
        CHECK_THAT(  1., WithinRel( math::clenshaw( order3.rbegin(), order3.rend(), a, b, 1., 0., 0. ) ) );

        CHECK_THAT(  1., WithinRel( math::clenshaw( order0.rbegin(), order0.rend(), a, b, 1., 1., 1. ) ) );
        CHECK_THAT(  3., WithinRel( math::clenshaw( order1.rbegin(), order1.rend(), a, b, 1., 1., 1. ) ) );
        CHECK_THAT(  6., WithinRel( math::clenshaw( order2.rbegin(), order2.rend(), a, b, 1., 1., 1. ) ) );
        CHECK_THAT( 10., WithinRel( math::clenshaw( order3.rbegin(), order3.rend(), a, b, 1., 1., 1. ) ) );

        CHECK_THAT(  1., WithinRel( math::clenshaw( order0.rbegin(), order0.rend(), a, b, 1., -1., -1. ) ) );
        CHECK_THAT( -1., WithinRel( math::clenshaw( order1.rbegin(), order1.rend(), a, b, 1., -1., -1. ) ) );
        CHECK_THAT(  2., WithinRel( math::clenshaw( order2.rbegin(), order2.rend(), a, b, 1., -1., -1. ) ) );
        CHECK_THAT( -2., WithinRel( math::clenshaw( order3.rbegin(), order3.rend(), a, b, 1., -1., -1. ) ) );
      } // THEN
    } // WHEN

    WHEN( "the vectors are used" ) {

      THEN( "the polynomials can be evaluated" ) {

        CHECK_THAT(  1., WithinRel( math::clenshaw( order0, a, b, 1., 0., 0. ) ) );
        CHECK_THAT(  1., WithinRel( math::clenshaw( order1, a, b, 1., 0., 0. ) ) );
        CHECK_THAT(  1., WithinRel( math::clenshaw( order2, a, b, 1., 0., 0. ) ) );
        CHECK_THAT(  1., WithinRel( math::clenshaw( order3, a, b, 1., 0., 0. ) ) );

        CHECK_THAT(  1., WithinRel( math::clenshaw( order0, a, b, 1., 1., 1. ) ) );
        CHECK_THAT(  3., WithinRel( math::clenshaw( order1, a, b, 1., 1., 1. ) ) );
        CHECK_THAT(  6., WithinRel( math::clenshaw( order2, a, b, 1., 1., 1. ) ) );
        CHECK_THAT( 10., WithinRel( math::clenshaw( order3, a, b, 1., 1., 1. ) ) );

        CHECK_THAT(  1., WithinRel( math::clenshaw( order0, a, b, 1., -1., -1. ) ) );
        CHECK_THAT( -1., WithinRel( math::clenshaw( order1, a, b, 1., -1., -1. ) ) );
        CHECK_THAT(  2., WithinRel( math::clenshaw( order2, a, b, 1., -1., -1. ) ) );
        CHECK_THAT( -2., WithinRel( math::clenshaw( order3, a, b, 1., -1., -1. ) ) );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "valid data for Legendre polynomials" ) {

    // Legendre coefficients (from lower order to higher order)
    std::vector< double > order0 = { 1. };
    std::vector< double > order1 = { 1., 2. };
    std::vector< double > order2 = { 1., 2., 3. };
    std::vector< double > order3 = { 1., 2., 3., 4. };

    auto a = [] ( unsigned int k, double x ) -> double {

      return static_cast< double >( 2 * k + 1 ) / static_cast< double >( k + 1 ) * x;
    };
    auto b = [] ( unsigned int k, double x ) -> double {

      return - static_cast< double >( k ) / static_cast< double >( k + 1 );
    };

    WHEN( "the iterators are used" ) {

      THEN( "the Legendre polynomials can be evaluated" ) {

        CHECK_THAT(   1., WithinRel( math::clenshaw( order0.rbegin(), order0.rend(), a, b, 1., 0., 0. ) ) );
        CHECK_THAT(   1., WithinRel( math::clenshaw( order1.rbegin(), order1.rend(), a, b, 1., 0., 0. ) ) );
        CHECK_THAT( -0.5, WithinRel( math::clenshaw( order2.rbegin(), order2.rend(), a, b, 1., 0., 0. ) ) );
        CHECK_THAT( -0.5, WithinRel( math::clenshaw( order3.rbegin(), order3.rend(), a, b, 1., 0., 0. ) ) );

        CHECK_THAT(  1., WithinRel( math::clenshaw( order0.rbegin(), order0.rend(), a, b, 1., 1., 1. ) ) );
        CHECK_THAT(  3., WithinRel( math::clenshaw( order1.rbegin(), order1.rend(), a, b, 1., 1., 1. ) ) );
        CHECK_THAT(  6., WithinRel( math::clenshaw( order2.rbegin(), order2.rend(), a, b, 1., 1., 1. ) ) );
        CHECK_THAT( 10., WithinRel( math::clenshaw( order3.rbegin(), order3.rend(), a, b, 1., 1., 1. ) ) );

        CHECK_THAT(  1., WithinRel( math::clenshaw( order0.rbegin(), order0.rend(), a, b, 1., -1., -1. ) ) );
        CHECK_THAT( -1., WithinRel( math::clenshaw( order1.rbegin(), order1.rend(), a, b, 1., -1., -1. ) ) );
        CHECK_THAT(  2., WithinRel( math::clenshaw( order2.rbegin(), order2.rend(), a, b, 1., -1., -1. ) ) );
        CHECK_THAT( -2., WithinRel( math::clenshaw( order3.rbegin(), order3.rend(), a, b, 1., -1., -1. ) ) );

        CHECK_THAT(   1., WithinRel( math::clenshawLegendre( order0.rbegin(), order0.rend(), 0. ) ) );
        CHECK_THAT(   1., WithinRel( math::clenshawLegendre( order1.rbegin(), order1.rend(), 0. ) ) );
        CHECK_THAT( -0.5, WithinRel( math::clenshawLegendre( order2.rbegin(), order2.rend(), 0. ) ) );
        CHECK_THAT( -0.5, WithinRel( math::clenshawLegendre( order3.rbegin(), order3.rend(), 0. ) ) );

        CHECK_THAT(  1., WithinRel( math::clenshawLegendre( order0.rbegin(), order0.rend(), 1. ) ) );
        CHECK_THAT(  3., WithinRel( math::clenshawLegendre( order1.rbegin(), order1.rend(), 1. ) ) );
        CHECK_THAT(  6., WithinRel( math::clenshawLegendre( order2.rbegin(), order2.rend(), 1. ) ) );
        CHECK_THAT( 10., WithinRel( math::clenshawLegendre( order3.rbegin(), order3.rend(), 1. ) ) );

        CHECK_THAT(  1., WithinRel( math::clenshawLegendre( order0.rbegin(), order0.rend(), -1. ) ) );
        CHECK_THAT( -1., WithinRel( math::clenshawLegendre( order1.rbegin(), order1.rend(), -1. ) ) );
        CHECK_THAT(  2., WithinRel( math::clenshawLegendre( order2.rbegin(), order2.rend(), -1. ) ) );
        CHECK_THAT( -2., WithinRel( math::clenshawLegendre( order3.rbegin(), order3.rend(), -1. ) ) );
      } // THEN
    } // WHEN

    WHEN( "the vectors are used" ) {

      THEN( "the Legendre polynomials can be evaluated" ) {

        CHECK_THAT(   1., WithinRel( math::clenshaw( order0, a, b, 1., 0., 0. ) ) );
        CHECK_THAT(   1., WithinRel( math::clenshaw( order1, a, b, 1., 0., 0. ) ) );
        CHECK_THAT( -0.5, WithinRel( math::clenshaw( order2, a, b, 1., 0., 0. ) ) );
        CHECK_THAT( -0.5, WithinRel( math::clenshaw( order3, a, b, 1., 0., 0. ) ) );

        CHECK_THAT(  1., WithinRel( math::clenshaw( order0, a, b, 1., 1., 1. ) ) );
        CHECK_THAT(  3., WithinRel( math::clenshaw( order1, a, b, 1., 1., 1. ) ) );
        CHECK_THAT(  6., WithinRel( math::clenshaw( order2, a, b, 1., 1., 1. ) ) );
        CHECK_THAT( 10., WithinRel( math::clenshaw( order3, a, b, 1., 1., 1. ) ) );

        CHECK_THAT(  1., WithinRel( math::clenshaw( order0, a, b, 1., -1., -1. ) ) );
        CHECK_THAT( -1., WithinRel( math::clenshaw( order1, a, b, 1., -1., -1. ) ) );
        CHECK_THAT(  2., WithinRel( math::clenshaw( order2, a, b, 1., -1., -1. ) ) );
        CHECK_THAT( -2., WithinRel( math::clenshaw( order3, a, b, 1., -1., -1. ) ) );

        CHECK_THAT(   1., WithinRel( math::clenshawLegendre( order0, 0. ) ) );
        CHECK_THAT(   1., WithinRel( math::clenshawLegendre( order1, 0. ) ) );
        CHECK_THAT( -0.5, WithinRel( math::clenshawLegendre( order2, 0. ) ) );
        CHECK_THAT( -0.5, WithinRel( math::clenshawLegendre( order3, 0. ) ) );

        CHECK_THAT(  1., WithinRel( math::clenshawLegendre( order0, 1. ) ) );
        CHECK_THAT(  3., WithinRel( math::clenshawLegendre( order1, 1. ) ) );
        CHECK_THAT(  6., WithinRel( math::clenshawLegendre( order2, 1. ) ) );
        CHECK_THAT( 10., WithinRel( math::clenshawLegendre( order3, 1. ) ) );

        CHECK_THAT(  1., WithinRel( math::clenshawLegendre( order0, -1. ) ) );
        CHECK_THAT( -1., WithinRel( math::clenshawLegendre( order1, -1. ) ) );
        CHECK_THAT(  2., WithinRel( math::clenshawLegendre( order2, -1. ) ) );
        CHECK_THAT( -2., WithinRel( math::clenshawLegendre( order3, -1. ) ) );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "valid data for Chebyshev polynomials" ) {

    // Chebyshev coefficients (from lower order to higher order)
    std::vector< double > order0 = { 1. };
    std::vector< double > order1 = { 1., 2. };
    std::vector< double > order2 = { 1., 2., 3. };
    std::vector< double > order3 = { 1., 2., 3., 4. };

    auto a = [] ( unsigned int k, double x ) -> double {

      return static_cast< double >( 2 ) * x;
    };
    auto b = [] ( unsigned int k, double x ) -> double {

      return - static_cast< double >( 1 );
    };

    WHEN( "the iterators are used" ) {

      THEN( "the Chebyshev polynomials can be evaluated" ) {

        CHECK_THAT(  1., WithinRel( math::clenshaw( order0.rbegin(), order0.rend(), a, b, 1., 0., 0. ) ) );
        CHECK_THAT(  1., WithinRel( math::clenshaw( order1.rbegin(), order1.rend(), a, b, 1., 0., 0. ) ) );
        CHECK_THAT( -2., WithinRel( math::clenshaw( order2.rbegin(), order2.rend(), a, b, 1., 0., 0. ) ) );
        CHECK_THAT( -2., WithinRel( math::clenshaw( order3.rbegin(), order3.rend(), a, b, 1., 0., 0. ) ) );

        CHECK_THAT(  1., WithinRel( math::clenshaw( order0.rbegin(), order0.rend(), a, b, 1., 1., 1. ) ) );
        CHECK_THAT(  3., WithinRel( math::clenshaw( order1.rbegin(), order1.rend(), a, b, 1., 1., 1. ) ) );
        CHECK_THAT(  6., WithinRel( math::clenshaw( order2.rbegin(), order2.rend(), a, b, 1., 1., 1. ) ) );
        CHECK_THAT( 10., WithinRel( math::clenshaw( order3.rbegin(), order3.rend(), a, b, 1., 1., 1. ) ) );

        CHECK_THAT(  1., WithinRel( math::clenshaw( order0.rbegin(), order0.rend(), a, b, 1., -1., -1. ) ) );
        CHECK_THAT( -1., WithinRel( math::clenshaw( order1.rbegin(), order1.rend(), a, b, 1., -1., -1. ) ) );
        CHECK_THAT(  2., WithinRel( math::clenshaw( order2.rbegin(), order2.rend(), a, b, 1., -1., -1. ) ) );
        CHECK_THAT( -2., WithinRel( math::clenshaw( order3.rbegin(), order3.rend(), a, b, 1., -1., -1. ) ) );

        CHECK_THAT(  1., WithinRel( math::clenshawChebyshev( order0.rbegin(), order0.rend(), 0. ) ) );
        CHECK_THAT(  1., WithinRel( math::clenshawChebyshev( order1.rbegin(), order1.rend(), 0. ) ) );
        CHECK_THAT( -2., WithinRel( math::clenshawChebyshev( order2.rbegin(), order2.rend(), 0. ) ) );
        CHECK_THAT( -2., WithinRel( math::clenshawChebyshev( order3.rbegin(), order3.rend(), 0. ) ) );

        CHECK_THAT(  1., WithinRel( math::clenshawChebyshev( order0.rbegin(), order0.rend(), 1. ) ) );
        CHECK_THAT(  3., WithinRel( math::clenshawChebyshev( order1.rbegin(), order1.rend(), 1. ) ) );
        CHECK_THAT(  6., WithinRel( math::clenshawChebyshev( order2.rbegin(), order2.rend(), 1. ) ) );
        CHECK_THAT( 10., WithinRel( math::clenshawChebyshev( order3.rbegin(), order3.rend(), 1. ) ) );

        CHECK_THAT(  1., WithinRel( math::clenshawChebyshev( order0.rbegin(), order0.rend(), -1. ) ) );
        CHECK_THAT( -1., WithinRel( math::clenshawChebyshev( order1.rbegin(), order1.rend(), -1. ) ) );
        CHECK_THAT(  2., WithinRel( math::clenshawChebyshev( order2.rbegin(), order2.rend(), -1. ) ) );
        CHECK_THAT( -2., WithinRel( math::clenshawChebyshev( order3.rbegin(), order3.rend(), -1. ) ) );
      } // THEN
    } // WHEN

    WHEN( "the vectors are used" ) {

      THEN( "the Chebyshev polynomials can be evaluated" ) {

        CHECK_THAT(  1., WithinRel( math::clenshaw( order0, a, b, 1., 0., 0. ) ) );
        CHECK_THAT(  1., WithinRel( math::clenshaw( order1, a, b, 1., 0., 0. ) ) );
        CHECK_THAT( -2., WithinRel( math::clenshaw( order2, a, b, 1., 0., 0. ) ) );
        CHECK_THAT( -2., WithinRel( math::clenshaw( order3, a, b, 1., 0., 0. ) ) );

        CHECK_THAT(  1., WithinRel( math::clenshaw( order0, a, b, 1., 1., 1. ) ) );
        CHECK_THAT(  3., WithinRel( math::clenshaw( order1, a, b, 1., 1., 1. ) ) );
        CHECK_THAT(  6., WithinRel( math::clenshaw( order2, a, b, 1., 1., 1. ) ) );
        CHECK_THAT( 10., WithinRel( math::clenshaw( order3, a, b, 1., 1., 1. ) ) );

        CHECK_THAT(  1., WithinRel( math::clenshaw( order0, a, b, 1., -1., -1. ) ) );
        CHECK_THAT( -1., WithinRel( math::clenshaw( order1, a, b, 1., -1., -1. ) ) );
        CHECK_THAT(  2., WithinRel( math::clenshaw( order2, a, b, 1., -1., -1. ) ) );
        CHECK_THAT( -2., WithinRel( math::clenshaw( order3, a, b, 1., -1., -1. ) ) );

        CHECK_THAT(  1., WithinRel( math::clenshawChebyshev( order0, 0. ) ) );
        CHECK_THAT(  1., WithinRel( math::clenshawChebyshev( order1, 0. ) ) );
        CHECK_THAT( -2., WithinRel( math::clenshawChebyshev( order2, 0. ) ) );
        CHECK_THAT( -2., WithinRel( math::clenshawChebyshev( order3, 0. ) ) );

        CHECK_THAT(  1., WithinRel( math::clenshawChebyshev( order0, 1. ) ) );
        CHECK_THAT(  3., WithinRel( math::clenshawChebyshev( order1, 1. ) ) );
        CHECK_THAT(  6., WithinRel( math::clenshawChebyshev( order2, 1. ) ) );
        CHECK_THAT( 10., WithinRel( math::clenshawChebyshev( order3, 1. ) ) );

        CHECK_THAT(  1., WithinRel( math::clenshawChebyshev( order0, -1. ) ) );
        CHECK_THAT( -1., WithinRel( math::clenshawChebyshev( order1, -1. ) ) );
        CHECK_THAT(  2., WithinRel( math::clenshawChebyshev( order2, -1. ) ) );
        CHECK_THAT( -2., WithinRel( math::clenshawChebyshev( order3, -1. ) ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
