#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "scion/math/ChebyshevApproximation.hpp"

// other includes

// convenience typedefs
using namespace njoy::scion;
template < typename X, typename Y = X > using ChebyshevApproximation = math::ChebyshevApproximation< X, Y >;
template < typename X > using IntervalDomain = math::IntervalDomain< X >;

SCENARIO( "ChebyshevApproximation" ) {

  GIVEN( "a function" ) {

    WHEN( "approximated on [-1,1]" ) {

      auto function = [] ( double x ) { return x; };
      ChebyshevApproximation< double > chunk( -1., 1., function, 10 );

      THEN( "a ChebyshevApproximation can be constructed and members can be tested" ) {

        CHECK( 10 == chunk.order() );

        CHECK( 11 == chunk.coefficients().size() );

        CHECK( 0.0 == Approx( chunk.coefficients()[0] ) );
        CHECK( 1.0 == Approx( chunk.coefficients()[1] ) );
        CHECK( 0.0 == Approx( chunk.coefficients()[2] ) );
        CHECK( 0.0 == Approx( chunk.coefficients()[3] ) );
        CHECK( 0.0 == Approx( chunk.coefficients()[4] ) );
        CHECK( 0.0 == Approx( chunk.coefficients()[5] ) );
        CHECK( 0.0 == Approx( chunk.coefficients()[6] ) );
        CHECK( 0.0 == Approx( chunk.coefficients()[7] ) );
        CHECK( 0.0 == Approx( chunk.coefficients()[8] ) );
        CHECK( 0.0 == Approx( chunk.coefficients()[9] ) );

        IntervalDomain< double > domain = std::get< IntervalDomain< double > >( chunk.domain() );
        CHECK( -1. == Approx( domain.lowerLimit() ) );
        CHECK(  1. == Approx( domain.upperLimit() ) );
      } // THEN

      THEN( "a ChebyshevApproximation can be evaluated" ) {

        CHECK( -1.0       == Approx( chunk( -1. ) ) );
        CHECK( -0.9999999 == Approx( chunk( -0.9999999 ) ) );
        CHECK( -0.999999  == Approx( chunk( -0.999999 ) ) );
        CHECK( -0.99999   == Approx( chunk( -0.99999 ) ) );
        CHECK( -0.9999    == Approx( chunk( -0.9999 ) ) );
        CHECK( -0.999     == Approx( chunk( -0.999 ) ) );
        CHECK( -0.99      == Approx( chunk( -0.99 ) ) );
        CHECK( -0.9       == Approx( chunk( -0.9 ) ) );
        CHECK( -0.5       == Approx( chunk( -0.5 ) ) );
        CHECK( -0.05      == Approx( chunk( -0.05 ) ) );
        CHECK( -0.005     == Approx( chunk( -0.005 ) ) );
        CHECK( -0.0005    == Approx( chunk( -0.0005 ) ) );
        CHECK( -0.00005   == Approx( chunk( -0.00005 ) ) );
        CHECK( -0.000005  == Approx( chunk( -0.000005 ) ) );
        CHECK( -0.0000005 == Approx( chunk( -0.0000005 ) ) );
        CHECK(  0.0       == Approx( chunk(  0. ) ) );
        CHECK( +0.0000005 == Approx( chunk(  0.0000005 ) ) );
        CHECK( +0.000005  == Approx( chunk(  0.000005 ) ) );
        CHECK( +0.00005   == Approx( chunk(  0.00005 ) ) );
        CHECK( +0.0005    == Approx( chunk(  0.0005 ) ) );
        CHECK( +0.005     == Approx( chunk(  0.005 ) ) );
        CHECK( +0.05      == Approx( chunk(  0.05 ) ) );
        CHECK( +0.5       == Approx( chunk(  0.5 ) ) );
        CHECK( +0.9       == Approx( chunk(  0.9 ) ) );
        CHECK( +0.99      == Approx( chunk(  0.99 ) ) );
        CHECK( +0.999     == Approx( chunk(  0.999 ) ) );
        CHECK( +0.9999    == Approx( chunk(  0.9999 ) ) );
        CHECK( +0.99999   == Approx( chunk(  0.99999 ) ) );
        CHECK( +0.999999  == Approx( chunk(  0.999999 ) ) );
        CHECK( +0.9999999 == Approx( chunk(  0.9999999 ) ) );
        CHECK( +1.0       == Approx( chunk(  1. ) ) );
      } // THEN
    } // WHEN

    WHEN( "approximated on [a,b]" ) {

      auto function = [] ( double x ) { return x; };
      ChebyshevApproximation< double > chunk( -2., 4., function, 10 );

      THEN( "a ChebyshevApproximation can be constructed and members can be tested" ) {

        CHECK( 10 == chunk.order() );

        CHECK( 11 == chunk.coefficients().size() );

        CHECK( 1.0 == Approx( chunk.coefficients()[0] ) );
        CHECK( 3.0 == Approx( chunk.coefficients()[1] ) );
        CHECK( 0.0 == Approx( chunk.coefficients()[2] ) );
        CHECK( 0.0 == Approx( chunk.coefficients()[3] ) );
        CHECK( 0.0 == Approx( chunk.coefficients()[4] ) );
        CHECK( 0.0 == Approx( chunk.coefficients()[5] ) );
        CHECK( 0.0 == Approx( chunk.coefficients()[6] ) );
        CHECK( 0.0 == Approx( chunk.coefficients()[7] ) );
        CHECK( 0.0 == Approx( chunk.coefficients()[8] ) );
        CHECK( 0.0 == Approx( chunk.coefficients()[9] ) );

        IntervalDomain< double > domain = std::get< IntervalDomain< double > >( chunk.domain() );
        CHECK( -2. == Approx( domain.lowerLimit() ) );
        CHECK(  4. == Approx( domain.upperLimit() ) );
      } // THEN

      THEN( "a ChebyshevApproximation can be evaluated" ) {

        CHECK( -1.0       == Approx( chunk( -1. ) ) );
        CHECK( -0.9999999 == Approx( chunk( -0.9999999 ) ) );
        CHECK( -0.999999  == Approx( chunk( -0.999999 ) ) );
        CHECK( -0.99999   == Approx( chunk( -0.99999 ) ) );
        CHECK( -0.9999    == Approx( chunk( -0.9999 ) ) );
        CHECK( -0.999     == Approx( chunk( -0.999 ) ) );
        CHECK( -0.99      == Approx( chunk( -0.99 ) ) );
        CHECK( -0.9       == Approx( chunk( -0.9 ) ) );
        CHECK( -0.5       == Approx( chunk( -0.5 ) ) );
        CHECK( -0.05      == Approx( chunk( -0.05 ) ) );
        CHECK( -0.005     == Approx( chunk( -0.005 ) ) );
        CHECK( -0.0005    == Approx( chunk( -0.0005 ) ) );
        CHECK( -0.00005   == Approx( chunk( -0.00005 ) ) );
        CHECK( -0.000005  == Approx( chunk( -0.000005 ) ) );
        CHECK( -0.0000005 == Approx( chunk( -0.0000005 ) ) );
        CHECK(  0.0       == Approx( chunk(  0. ) ) );
        CHECK( +0.0000005 == Approx( chunk(  0.0000005 ) ) );
        CHECK( +0.000005  == Approx( chunk(  0.000005 ) ) );
        CHECK( +0.00005   == Approx( chunk(  0.00005 ) ) );
        CHECK( +0.0005    == Approx( chunk(  0.0005 ) ) );
        CHECK( +0.005     == Approx( chunk(  0.005 ) ) );
        CHECK( +0.05      == Approx( chunk(  0.05 ) ) );
        CHECK( +0.5       == Approx( chunk(  0.5 ) ) );
        CHECK( +0.9       == Approx( chunk(  0.9 ) ) );
        CHECK( +0.99      == Approx( chunk(  0.99 ) ) );
        CHECK( +0.999     == Approx( chunk(  0.999 ) ) );
        CHECK( +0.9999    == Approx( chunk(  0.9999 ) ) );
        CHECK( +0.99999   == Approx( chunk(  0.99999 ) ) );
        CHECK( +0.999999  == Approx( chunk(  0.999999 ) ) );
        CHECK( +0.9999999 == Approx( chunk(  0.9999999 ) ) );
        CHECK( +1.0       == Approx( chunk(  1. ) ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
