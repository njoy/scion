// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;
using Catch::Matchers::WithinAbs;

// what we are testing
#include "scion/integration/AdaptiveGaussLobatto.hpp"

// other includes
#include <cmath>

// convenience typedefs
using namespace njoy::scion;

SCENARIO( "Adaptive Gauss-Lobatto quadrature" ) {

  GIVEN( "an adaptive Gauss-Lobattointegration object" ) {

    integration::AdaptiveGaussLobatto< double > integrator{};

    WHEN( "integrating an interval" ) {

      THEN( "the integration is performed exactly for an order 0 polynomial" ) {

        // y = f(x) = 1
        auto functor = [] ( double ) { return 1.; };

        CHECK_THAT( 2., WithinRel( integrator( functor, -1.,  1. ) ) );
        CHECK_THAT( 2., WithinRel( integrator( functor,  3.,  5. ) ) );
      } // THEN

      THEN( "the integration is performed exactly for an order 1 polynomial" ) {

        // y = f(x) = x + 1
        auto functor = [] ( double x ) { return x + 1.; };

        CHECK_THAT(  2., WithinRel( integrator( functor, -1.,  1. ) ) );
        CHECK_THAT( 10., WithinRel( integrator( functor,  3.,  5. ) ) );
      } // THEN

      THEN( "the integration is performed for cosine on [-1,1] for different tolerances" ) {

        // y = f(x) = cosine( x )
        auto functor = [] ( double x ) { return std::cos( x ); };

        CHECK_THAT( 2. * std::sin( 1. ), WithinRel( integrator( functor, -1.,  1. ), 1e-8 ) );
        CHECK_THAT( 2. * std::sin( 1. ), WithinRel( integrator( functor, -1.,  1., 1e-12 ), 1e-11 ) );
      } // THEN

// intel C++ fails on this but all other compilers pass
//      THEN( "the integration is performed for sine on [-1,1] for different tolerances" ) {
//
//        // y = f(x) = sine( x )
//        auto functor = [] ( double x ) { return std::sin( x ); };
//
//        CHECK_THAT( 0., WithinRel( integrator( functor, -1.,  1. ), 1e-8 ) );
//        CHECK_THAT( 0., WithinRel( integrator( functor, -1.,  1., 1e-12 ), 5e-12 ) );
//      } // THEN

      THEN( "the integration is performed for 1/(1+x) on [0,1] for different tolerances" ) {

        // y = f(x) = 1 / ( 1 + x )
        auto functor = [] ( double x ) { return 1. / ( 1. + x ); };

        CHECK_THAT( std::log( 2. ), WithinRel( integrator( functor, 0.,  1. ), 1e-8 ) );
        CHECK_THAT( std::log( 2. ), WithinRel( integrator( functor, 0.,  1., 1e-12 ), 1e-11 ) );
      } // THEN

      THEN( "the integration is performed for 1/sqrt(1+x*x) on [-1,1] for different tolerances" ) {

        // y = f(x) = 1 / sqrt( 1 + x * x )
        auto functor = [] ( double x ) { return 1. / std::sqrt( 1. + x * x ); };

        CHECK_THAT( 2 * std::asinh( 1. ), WithinRel( integrator( functor, -1.,  1. ), 1e-8 ) );
        CHECK_THAT( 2 * std::asinh( 1. ), WithinRel( integrator( functor, -1.,  1., 1e-12 ), 1e-11 ) );
      } // THEN

      THEN( "the integration is performed for x * x * sin(x)^3 on [0,4] for different tolerances" ) {

        // y = f(x) = x * x * sin(x)^3
        auto functor = [] ( double x ) { return x * x * std::sin(x) * std::sin(x) * std::sin(x); };

        // wolfram alpha calculated result
        double result = 1. / 54. * (-80. - 567. * std::cos(4) + 71. * std::cos(12)
                      + 324. * std::sin(4) - 12. * std::sin(12));

        CHECK_THAT( result, WithinRel( integrator( functor, 0,  4. ), 1e-8 ) );
        CHECK_THAT( result, WithinRel( integrator( functor, 0,  4., 1e-12 ), 1e-11 ) );
      } // THEN

      THEN( "the integration is performed for x * x * sin(x)^3 on [-4,4] for different tolerances" ) {

        // y = f(x) = x * x * sin(x)^3
        auto functor = [] ( double x ) { return x * x * std::sin(x) * std::sin(x) * std::sin(x); };

        CHECK_THAT( 0., WithinAbs( integrator( functor, -4.,  4. ), 1e-14 ) );
        CHECK_THAT( 0., WithinAbs( integrator( functor, -4.,  4., 1e-12 ), 1e-14 ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
