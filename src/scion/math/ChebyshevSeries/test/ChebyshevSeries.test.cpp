#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "scion/math/ChebyshevSeries.hpp"

// other includes

// convenience typedefs
using namespace njoy::scion;
template < typename X, typename Y = X > using ChebyshevSeries = math::ChebyshevSeries< X, Y >;
template < typename X > using IntervalDomain = math::IntervalDomain< X >;

SCENARIO( "ChebyshevSeries" ) {

  GIVEN( "Legendre coefficients for an expansion" ) {

    WHEN( "the data is given explicitly" ) {

      // the 3rd order Legendre series was designed to have 3 real roots: 1, 2 and 4
      // the 3rd order polynomial series equivalent to this is the same as the
      // one in the PolynomialSeries example

      std::vector< double > coefficients = { -23./2., 59./4., -7./2., 1./4. };

      ChebyshevSeries< double > chunk( std::move( coefficients ) );

      THEN( "a ChebyshevSeries can be constructed and members can be tested" ) {

        CHECK( 3 == chunk.order() );

        CHECK( 4 == chunk.coefficients().size() );
        CHECK( -11.50 == Approx( chunk.coefficients()[0] ) );
        CHECK(  14.75 == Approx( chunk.coefficients()[1] ) );
        CHECK(  -3.50 == Approx( chunk.coefficients()[2] ) );
        CHECK(   0.25 == Approx( chunk.coefficients()[3] ) );

        CHECK( true == std::holds_alternative< IntervalDomain< double > >( chunk.domain() ) );
      } // THEN

      THEN( "a ChebyshevSeries can be evaluated" ) {

        CHECK(  -8.0 == Approx( chunk.evaluate(  0. ) ) );
        CHECK(   0.0 == Approx( chunk.evaluate(  1. ) ) );
        CHECK( -30.0 == Approx( chunk.evaluate( -1. ) ) );

        CHECK(  -8.0 == Approx( chunk(  0. ) ) );
        CHECK(   0.0 == Approx( chunk(  1. ) ) );
        CHECK( -30.0 == Approx( chunk( -1. ) ) );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "invalid data" ) {

    WHEN( "the coefficient vector is empty" ) {

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( ChebyshevSeries< double >( {} ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
