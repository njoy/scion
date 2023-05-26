#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "scion/math/ChebyshevSeries.hpp"

// other includes

// convenience typedefs
using namespace njoy::scion;
template < typename X, typename Y = X > using ChebyshevSeries = math::ChebyshevSeries< X, Y >;
template < typename X > using IntervalDomain = math::IntervalDomain< X >;

SCENARIO( "ChebyshevSeries" ) {

  GIVEN( "Chebyshev coefficients for an expansion" ) {

    WHEN( "the data is given explicitly" ) {

      // the 3rd order Chebyshev series was designed to have 3 real roots: 1, 2 and 4
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

        CHECK(  -8.0 == Approx( chunk(  0. ) ) );
        CHECK(   0.0 == Approx( chunk(  1. ) ) );
        CHECK( -30.0 == Approx( chunk( -1. ) ) );
      } // THEN

      THEN( "roots can be calculated" ) {

        std::vector< double > roots = chunk.roots();

        CHECK( 3 == roots.size() );
        CHECK( 1.0 == Approx( roots[0] ) );
        CHECK( 2.0 == Approx( roots[1] ) );
        CHECK( 4.0 == Approx( roots[2] ) );

        roots = chunk.roots( -8. );

        CHECK( 1 == roots.size() );
        CHECK(  0.0 == Approx( roots[0] ) );
      } // THEN

      THEN( "a ChebyshevSeries can be differentiated" ) {

        ChebyshevSeries< double > first = chunk.derivative();
        ChebyshevSeries< double > second = first.derivative();
        ChebyshevSeries< double > third = second.derivative();
        ChebyshevSeries< double > fourth = third.derivative();

        CHECK( 2 == first.order() );
        CHECK( 3 == first.coefficients().size() );
        CHECK(  15.5 == Approx( first.coefficients()[0] ) );
        CHECK( -14.0 == Approx( first.coefficients()[1] ) );
        CHECK(   1.5 == Approx( first.coefficients()[2] ) );

        CHECK( 1 == second.order() );
        CHECK( 2 == second.coefficients().size() );
        CHECK( -14. == Approx( second.coefficients()[0] ) );
        CHECK(   6. == Approx( second.coefficients()[1] ) );

        CHECK( 0 == third.order() );
        CHECK( 1 == third.coefficients().size() );
        CHECK( 6. == Approx( third.coefficients()[0] ) );

        CHECK( 0 == fourth.order() );
        CHECK( 1 == fourth.coefficients().size() );
        CHECK( 0. == Approx( fourth.coefficients()[0] ) );
      } // THEN

      THEN( "a ChebyshevSeries can be integrated" ) {

        ChebyshevSeries< double > primitive = chunk.primitive();

        CHECK( 4 == primitive.order() );
        CHECK( 5 == primitive.coefficients().size() );
        CHECK(  3.59375 == Approx( primitive.coefficients()[0] ) );
        CHECK( -9.75 == Approx( primitive.coefficients()[1] ) );
        CHECK(  3.625 == Approx( primitive.coefficients()[2] ) );
        CHECK( -0.5833333333333334 == Approx( primitive.coefficients()[3] ) );
        CHECK(  0.03125 == Approx( primitive.coefficients()[4] ) );
      } // THEN

      THEN( "arithmetic operations can be performed" ) {

        ChebyshevSeries< double > small( { 3., 0., 1. } );
        ChebyshevSeries< double > equal( { 3., 0., 0., 1. } );
        ChebyshevSeries< double > larger( { 3., 0., 0., 0., 1. } );

        chunk += 2.;

        CHECK( 3 == chunk.order() );
        CHECK(  4 == chunk.coefficients().size() );
        CHECK(  -9.50 == Approx( chunk.coefficients()[0] ) );
        CHECK(  14.75 == Approx( chunk.coefficients()[1] ) );
        CHECK(  -3.50 == Approx( chunk.coefficients()[2] ) );
        CHECK(   0.25 == Approx( chunk.coefficients()[3] ) );
        CHECK( true == std::holds_alternative< IntervalDomain< double > >( chunk.domain() ) );

        chunk -= 2.;

        CHECK( 3 == chunk.order() );
        CHECK(  4 == chunk.coefficients().size() );
        CHECK( -11.50 == Approx( chunk.coefficients()[0] ) );
        CHECK(  14.75 == Approx( chunk.coefficients()[1] ) );
        CHECK(  -3.50 == Approx( chunk.coefficients()[2] ) );
        CHECK(   0.25 == Approx( chunk.coefficients()[3] ) );
        CHECK( true == std::holds_alternative< IntervalDomain< double > >( chunk.domain() ) );

        chunk += small;

        CHECK( 3 == chunk.order() );
        CHECK(  4 == chunk.coefficients().size() );
        CHECK( -8.50 == Approx( chunk.coefficients()[0] ) );
        CHECK( 14.75 == Approx( chunk.coefficients()[1] ) );
        CHECK( -2.50 == Approx( chunk.coefficients()[2] ) );
        CHECK(  0.25 == Approx( chunk.coefficients()[3] ) );
        CHECK( true == std::holds_alternative< IntervalDomain< double > >( chunk.domain() ) );

        chunk -= small;

        CHECK( 3 == chunk.order() );
        CHECK(  4 == chunk.coefficients().size() );
        CHECK( -11.50 == Approx( chunk.coefficients()[0] ) );
        CHECK(  14.75 == Approx( chunk.coefficients()[1] ) );
        CHECK(  -3.50 == Approx( chunk.coefficients()[2] ) );
        CHECK(   0.25 == Approx( chunk.coefficients()[3] ) );
        CHECK( true == std::holds_alternative< IntervalDomain< double > >( chunk.domain() ) );

        chunk += equal;

        CHECK( 3 == chunk.order() );
        CHECK(  4 == chunk.coefficients().size() );
        CHECK( -8.50 == Approx( chunk.coefficients()[0] ) );
        CHECK( 14.75 == Approx( chunk.coefficients()[1] ) );
        CHECK( -3.50 == Approx( chunk.coefficients()[2] ) );
        CHECK(  1.25 == Approx( chunk.coefficients()[3] ) );
        CHECK( true == std::holds_alternative< IntervalDomain< double > >( chunk.domain() ) );

        chunk -= equal;

        CHECK( 3 == chunk.order() );
        CHECK(  4 == chunk.coefficients().size() );
        CHECK( -11.50 == Approx( chunk.coefficients()[0] ) );
        CHECK(  14.75 == Approx( chunk.coefficients()[1] ) );
        CHECK(  -3.50 == Approx( chunk.coefficients()[2] ) );
        CHECK(   0.25 == Approx( chunk.coefficients()[3] ) );
        CHECK( true == std::holds_alternative< IntervalDomain< double > >( chunk.domain() ) );

        chunk *= 2.;

        CHECK( 3 == chunk.order() );
        CHECK(  4 == chunk.coefficients().size() );
        CHECK( -23.0 == Approx( chunk.coefficients()[0] ) );
        CHECK(  29.5 == Approx( chunk.coefficients()[1] ) );
        CHECK(  -7.0 == Approx( chunk.coefficients()[2] ) );
        CHECK(   0.5 == Approx( chunk.coefficients()[3] ) );
        CHECK( true == std::holds_alternative< IntervalDomain< double > >( chunk.domain() ) );

        chunk /= 2.;

        CHECK( 3 == chunk.order() );
        CHECK(  4 == chunk.coefficients().size() );
        CHECK( -11.50 == Approx( chunk.coefficients()[0] ) );
        CHECK(  14.75 == Approx( chunk.coefficients()[1] ) );
        CHECK(  -3.50 == Approx( chunk.coefficients()[2] ) );
        CHECK(   0.25 == Approx( chunk.coefficients()[3] ) );
        CHECK( true == std::holds_alternative< IntervalDomain< double > >( chunk.domain() ) );
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
