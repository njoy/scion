#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "scion/math/PolynomialSeries.hpp"

// other includes

// convenience typedefs
using namespace njoy::scion;
template < typename X, typename Y = X > using PolynomialSeries = math::PolynomialSeries< X, Y >;
template < typename X > using IntervalDomain = math::IntervalDomain< X >;
template < typename X > using OpenDomain = math::OpenDomain< X >;
template < typename X, typename Y = X >
using InterpolationTable = math::InterpolationTable< X, Y >;
template < typename X > using IntervalDomain = math::IntervalDomain< X >;
using InterpolationType = interpolation::InterpolationType;
template< typename X, typename Y = X >
using ToleranceConvergence = linearisation::ToleranceConvergence< X, Y >;

SCENARIO( "PolynomialSeries" ) {

  GIVEN( "Legendre coefficients for an expansion" ) {

    WHEN( "the data is given explicitly" ) {

      // the 3rd order polynomial was designed to have 3 real roots: 1, 2 and 4

      double lower = -1.;
      double upper = 1.;
      std::vector< double > coefficients = { -8., 14., -7., 1. };

      PolynomialSeries< double > chunk( lower, upper, std::move( coefficients ) );

      THEN( "a PolynomialSeries can be constructed and members can be tested" ) {

        CHECK( 3 == chunk.order() );

        CHECK( 4 == chunk.coefficients().size() );
        CHECK( -8. == Approx( chunk.coefficients()[0] ) );
        CHECK( 14. == Approx( chunk.coefficients()[1] ) );
        CHECK( -7. == Approx( chunk.coefficients()[2] ) );
        CHECK(  1. == Approx( chunk.coefficients()[3] ) );

        CHECK( true == std::holds_alternative< IntervalDomain< double > >( chunk.domain() ) );
      } // THEN

      THEN( "a PolynomialSeries can be evaluated" ) {

        CHECK(  -8.0 == Approx( chunk(  0. ) ) );
        CHECK(   0.0 == Approx( chunk(  1. ) ) );
        CHECK( -30.0 == Approx( chunk( -1. ) ) );
      } // THEN

      THEN( "a PolynomialSeries can be differentiated" ) {

        PolynomialSeries< double > first = chunk.derivative();
        PolynomialSeries< double > second = first.derivative();
        PolynomialSeries< double > third = second.derivative();
        PolynomialSeries< double > fourth = third.derivative();

        CHECK( 2 == first.order() );
        CHECK( 3 == first.coefficients().size() );
        CHECK(  14. == Approx( first.coefficients()[0] ) );
        CHECK( -14. == Approx( first.coefficients()[1] ) );
        CHECK(   3. == Approx( first.coefficients()[2] ) );
        IntervalDomain< double > domain = std::get< IntervalDomain< double > >( first.domain() );
        CHECK( -1. == Approx( domain.lowerLimit() ) );
        CHECK(  1. == Approx( domain.upperLimit() ) );

        CHECK( 1 == second.order() );
        CHECK( 2 == second.coefficients().size() );
        CHECK( -14. == Approx( second.coefficients()[0] ) );
        CHECK(   6. == Approx( second.coefficients()[1] ) );
        domain = std::get< IntervalDomain< double > >( second.domain() );
        CHECK( -1. == Approx( domain.lowerLimit() ) );
        CHECK(  1. == Approx( domain.upperLimit() ) );

        CHECK( 0 == third.order() );
        CHECK( 1 == third.coefficients().size() );
        CHECK( 6. == Approx( third.coefficients()[0] ) );
        domain = std::get< IntervalDomain< double > >( third.domain() );
        CHECK( -1. == Approx( domain.lowerLimit() ) );
        CHECK(  1. == Approx( domain.upperLimit() ) );

        CHECK( 0 == fourth.order() );
        CHECK( 1 == fourth.coefficients().size() );
        CHECK( 0. == Approx( fourth.coefficients()[0] ) );
        domain = std::get< IntervalDomain< double > >( fourth.domain() );
        CHECK( -1. == Approx( domain.lowerLimit() ) );
        CHECK(  1. == Approx( domain.upperLimit() ) );
      } // THEN

      THEN( "a PolynomialSeries can be integrated" ) {

        PolynomialSeries< double > primitive = chunk.primitive();

        CHECK( 4 == primitive.order() );
        CHECK( 5 == primitive.coefficients().size() );
        CHECK(   0. == Approx( primitive.coefficients()[0] ) );
        CHECK(  -8. == Approx( primitive.coefficients()[1] ) );
        CHECK(   7. == Approx( primitive.coefficients()[2] ) );
        CHECK(  -7. / 3. == Approx( primitive.coefficients()[3] ) );
        CHECK(   1. / 4. == Approx( primitive.coefficients()[4] ) );
        IntervalDomain< double > domain = std::get< IntervalDomain< double > >( primitive.domain() );
        CHECK( -1. == Approx( domain.lowerLimit() ) );
        CHECK(  1. == Approx( domain.upperLimit() ) );

        primitive = chunk.primitive( -1. );

        CHECK( 4 == primitive.order() );
        CHECK( 5 == primitive.coefficients().size() );
        CHECK( -211. / 12. == Approx( primitive.coefficients()[0] ) );
        CHECK(  -8. == Approx( primitive.coefficients()[1] ) );
        CHECK(   7. == Approx( primitive.coefficients()[2] ) );
        CHECK(  -7. / 3. == Approx( primitive.coefficients()[3] ) );
        CHECK(   1. / 4. == Approx( primitive.coefficients()[4] ) );
        domain = std::get< IntervalDomain< double > >( primitive.domain() );
        CHECK( -1. == Approx( domain.lowerLimit() ) );
        CHECK(  1. == Approx( domain.upperLimit() ) );
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

      THEN( "the domain can be tested" ) {

        CHECK( true == chunk.isInside( -1.0 ) );
        CHECK( true == chunk.isInside(  0.0 ) );
        CHECK( true == chunk.isInside(  1.0 ) );

        CHECK( false == chunk.isContained( -1.0 ) );
        CHECK( true == chunk.isContained(  0.0 ) );
        CHECK( false == chunk.isContained(  1.0 ) );

        CHECK( true == chunk.isSameDomain( IntervalDomain< double >( -1., +1. ) ) );
        CHECK( false == chunk.isSameDomain( IntervalDomain< double >( -1., 0. ) ) );
        CHECK( false == chunk.isSameDomain( OpenDomain< double >() ) );
      } // THEN

      THEN( "a PolynomialSeries can be linearised" ) {

        ToleranceConvergence< double > convergence( 0.01 );
        InterpolationTable< double > linear = chunk.linearise( convergence );

        CHECK( 21 == linear.numberPoints() );
        CHECK( 1 == linear.numberRegions() );

        CHECK( 21 == linear.x().size() );
        CHECK( 21 == linear.y().size() );
        CHECK( 1 == linear.boundaries().size() );
        CHECK( 1 == linear.interpolants().size() );

        CHECK( 20 == linear.boundaries()[0] );

        CHECK( InterpolationType::LinearLinear == linear.interpolants()[0] );

        CHECK( -1.0       == Approx( linear.x()[0] ) );
        CHECK( -0.75      == Approx( linear.x()[1] ) );
        CHECK( -0.5       == Approx( linear.x()[2] ) );
        CHECK( -0.25      == Approx( linear.x()[3] ) );
        CHECK( -0.125     == Approx( linear.x()[4] ) );
        CHECK(  0.0       == Approx( linear.x()[5] ) );
        CHECK(  0.125     == Approx( linear.x()[6] ) );
        CHECK(  0.25      == Approx( linear.x()[7] ) );
        CHECK(  0.375     == Approx( linear.x()[8] ) );
        CHECK(  0.5       == Approx( linear.x()[9] ) );
        CHECK(  0.625     == Approx( linear.x()[10] ) );
        CHECK(  0.6875    == Approx( linear.x()[11] ) );
        CHECK(  0.75      == Approx( linear.x()[12] ) );
        CHECK(  0.8125    == Approx( linear.x()[13] ) );
        CHECK(  0.875     == Approx( linear.x()[14] ) );
        CHECK(  0.90625   == Approx( linear.x()[15] ) );
        CHECK(  0.9375    == Approx( linear.x()[16] ) );
        CHECK(  0.96875   == Approx( linear.x()[17] ) );
        CHECK(  0.984375  == Approx( linear.x()[18] ) );
        CHECK(  0.9921875 == Approx( linear.x()[19] ) );
        CHECK(  1.0       == Approx( linear.x()[20] ) );

        CHECK( -30.0       == Approx( linear.y()[0] ) );
        CHECK( -22.859375  == Approx( linear.y()[1] ) );
        CHECK( -16.875     == Approx( linear.y()[2] ) );
        CHECK( -11.953125  == Approx( linear.y()[3] ) );
        CHECK( -9.86132813 == Approx( linear.y()[4] ) );
        CHECK( -8.0        == Approx( linear.y()[5] ) );
        CHECK( -6.35742188 == Approx( linear.y()[6] ) );
        CHECK( -4.921875   == Approx( linear.y()[7] ) );
        CHECK( -3.68164063 == Approx( linear.y()[8] ) );
        CHECK( -2.625      == Approx( linear.y()[9] ) );
        CHECK( -1.74023438 == Approx( linear.y()[10] ) );
        CHECK( -1.35864258 == Approx( linear.y()[11] ) );
        CHECK( -1.015625   == Approx( linear.y()[12] ) );
        CHECK( -0.70971680 == Approx( linear.y()[13] ) );
        CHECK( -0.43945313 == Approx( linear.y()[14] ) );
        CHECK( -0.31723023 == Approx( linear.y()[15] ) );
        CHECK( -0.20336914 == Approx( linear.y()[16] ) );
        CHECK( -0.09768677 == Approx( linear.y()[17] ) );
        CHECK( -0.04785538 == Approx( linear.y()[18] ) );
        CHECK( -0.02368212 == Approx( linear.y()[19] ) );
        CHECK(  0.0        == Approx( linear.y()[20] ) );
      } // THEN

      THEN( "arithmetic operations can be performed" ) {

        PolynomialSeries< double > small( { 3., 0., 1. } );
        PolynomialSeries< double > equal( { 3., 0., 0., 1. } );
        PolynomialSeries< double > large( { 3., 0., 0., 0., 1. } );
        PolynomialSeries< double > result( { 0. } );

        chunk += 2.;

        CHECK( 3 == chunk.order() );
        CHECK( 4 == chunk.coefficients().size() );
        CHECK( -6. == Approx( chunk.coefficients()[0] ) );
        CHECK( 14. == Approx( chunk.coefficients()[1] ) );
        CHECK( -7. == Approx( chunk.coefficients()[2] ) );
        CHECK(  1. == Approx( chunk.coefficients()[3] ) );
        CHECK( true == std::holds_alternative< IntervalDomain< double > >( chunk.domain() ) );

        chunk -= 2.;

        CHECK( 3 == chunk.order() );
        CHECK( 4 == chunk.coefficients().size() );
        CHECK( -8. == Approx( chunk.coefficients()[0] ) );
        CHECK( 14. == Approx( chunk.coefficients()[1] ) );
        CHECK( -7. == Approx( chunk.coefficients()[2] ) );
        CHECK(  1. == Approx( chunk.coefficients()[3] ) );
        CHECK( true == std::holds_alternative< IntervalDomain< double > >( chunk.domain() ) );

        chunk += small;

        CHECK( 3 == chunk.order() );
        CHECK( 4 == chunk.coefficients().size() );
        CHECK( -5. == Approx( chunk.coefficients()[0] ) );
        CHECK( 14. == Approx( chunk.coefficients()[1] ) );
        CHECK( -6. == Approx( chunk.coefficients()[2] ) );
        CHECK(  1. == Approx( chunk.coefficients()[3] ) );
        CHECK( true == std::holds_alternative< IntervalDomain< double > >( chunk.domain() ) );

        chunk -= small;

        CHECK( 3 == chunk.order() );
        CHECK( 4 == chunk.coefficients().size() );
        CHECK( -8. == Approx( chunk.coefficients()[0] ) );
        CHECK( 14. == Approx( chunk.coefficients()[1] ) );
        CHECK( -7. == Approx( chunk.coefficients()[2] ) );
        CHECK(  1. == Approx( chunk.coefficients()[3] ) );
        CHECK( true == std::holds_alternative< IntervalDomain< double > >( chunk.domain() ) );

        chunk += equal;

        CHECK( 3 == chunk.order() );
        CHECK( 4 == chunk.coefficients().size() );
        CHECK( -5. == Approx( chunk.coefficients()[0] ) );
        CHECK( 14. == Approx( chunk.coefficients()[1] ) );
        CHECK( -7. == Approx( chunk.coefficients()[2] ) );
        CHECK(  2. == Approx( chunk.coefficients()[3] ) );
        CHECK( true == std::holds_alternative< IntervalDomain< double > >( chunk.domain() ) );

        chunk -= equal;

        CHECK( 3 == chunk.order() );
        CHECK( 4 == chunk.coefficients().size() );
        CHECK( -8. == Approx( chunk.coefficients()[0] ) );
        CHECK( 14. == Approx( chunk.coefficients()[1] ) );
        CHECK( -7. == Approx( chunk.coefficients()[2] ) );
        CHECK(  1. == Approx( chunk.coefficients()[3] ) );
        CHECK( true == std::holds_alternative< IntervalDomain< double > >( chunk.domain() ) );

        chunk += large;

        CHECK( 4 == chunk.order() );
        CHECK(  5 == chunk.coefficients().size() );
        CHECK( -5. == Approx( chunk.coefficients()[0] ) );
        CHECK( 14. == Approx( chunk.coefficients()[1] ) );
        CHECK( -7. == Approx( chunk.coefficients()[2] ) );
        CHECK(  1. == Approx( chunk.coefficients()[3] ) );
        CHECK(  1. == Approx( chunk.coefficients()[4] ) );
        CHECK( true == std::holds_alternative< IntervalDomain< double > >( chunk.domain() ) );

        chunk -= large;

        CHECK( 3 == chunk.order() );
        CHECK( 4 == chunk.coefficients().size() );
        CHECK( -8. == Approx( chunk.coefficients()[0] ) );
        CHECK( 14. == Approx( chunk.coefficients()[1] ) );
        CHECK( -7. == Approx( chunk.coefficients()[2] ) );
        CHECK(  1. == Approx( chunk.coefficients()[3] ) );
        CHECK( true == std::holds_alternative< IntervalDomain< double > >( chunk.domain() ) );

        chunk *= 2.;

        CHECK( 3 == chunk.order() );
        CHECK( 4 == chunk.coefficients().size() );
        CHECK( -16. == Approx( chunk.coefficients()[0] ) );
        CHECK(  28. == Approx( chunk.coefficients()[1] ) );
        CHECK( -14. == Approx( chunk.coefficients()[2] ) );
        CHECK(   2. == Approx( chunk.coefficients()[3] ) );
        CHECK( true == std::holds_alternative< IntervalDomain< double > >( chunk.domain() ) );

        chunk /= 2.;

        CHECK( 3 == chunk.order() );
        CHECK( 4 == chunk.coefficients().size() );
        CHECK( -8. == Approx( chunk.coefficients()[0] ) );
        CHECK( 14. == Approx( chunk.coefficients()[1] ) );
        CHECK( -7. == Approx( chunk.coefficients()[2] ) );
        CHECK(  1. == Approx( chunk.coefficients()[3] ) );
        CHECK( true == std::holds_alternative< IntervalDomain< double > >( chunk.domain() ) );

        result = chunk + 2.;

        CHECK( 3 == result.order() );
        CHECK( 4 == result.coefficients().size() );
        CHECK( -6. == Approx( result.coefficients()[0] ) );
        CHECK( 14. == Approx( result.coefficients()[1] ) );
        CHECK( -7. == Approx( result.coefficients()[2] ) );
        CHECK(  1. == Approx( result.coefficients()[3] ) );
        CHECK( true == std::holds_alternative< IntervalDomain< double > >( result.domain() ) );

        result = chunk - 2.;

        CHECK( 3 == result.order() );
        CHECK( 4 == result.coefficients().size() );
        CHECK( -10. == Approx( result.coefficients()[0] ) );
        CHECK(  14. == Approx( result.coefficients()[1] ) );
        CHECK(  -7. == Approx( result.coefficients()[2] ) );
        CHECK(   1. == Approx( result.coefficients()[3] ) );
        CHECK( true == std::holds_alternative< IntervalDomain< double > >( result.domain() ) );

        result = chunk * 2.;

        CHECK( 3 == result.order() );
        CHECK( 4 == result.coefficients().size() );
        CHECK( -16. == Approx( result.coefficients()[0] ) );
        CHECK(  28. == Approx( result.coefficients()[1] ) );
        CHECK( -14. == Approx( result.coefficients()[2] ) );
        CHECK(   2. == Approx( result.coefficients()[3] ) );
        CHECK( true == std::holds_alternative< IntervalDomain< double > >( result.domain() ) );

        result = chunk / 2.;

        CHECK( 3 == result.order() );
        CHECK( 4 == result.coefficients().size() );
        CHECK( -4.  == Approx( result.coefficients()[0] ) );
        CHECK(  7.  == Approx( result.coefficients()[1] ) );
        CHECK( -3.5 == Approx( result.coefficients()[2] ) );
        CHECK(  0.5 == Approx( result.coefficients()[3] ) );
        CHECK( true == std::holds_alternative< IntervalDomain< double > >( result.domain() ) );

        result = chunk + small;

        CHECK( 3 == result.order() );
        CHECK( 4 == result.coefficients().size() );
        CHECK( -5. == Approx( result.coefficients()[0] ) );
        CHECK( 14. == Approx( result.coefficients()[1] ) );
        CHECK( -6. == Approx( result.coefficients()[2] ) );
        CHECK(  1. == Approx( result.coefficients()[3] ) );
        CHECK( true == std::holds_alternative< IntervalDomain< double > >( result.domain() ) );

        result = chunk - small;

        CHECK( 3 == result.order() );
        CHECK( 4 == result.coefficients().size() );
        CHECK( -11. == Approx( result.coefficients()[0] ) );
        CHECK(  14. == Approx( result.coefficients()[1] ) );
        CHECK(  -8. == Approx( result.coefficients()[2] ) );
        CHECK(   1. == Approx( result.coefficients()[3] ) );
        CHECK( true == std::holds_alternative< IntervalDomain< double > >( result.domain() ) );

        result = chunk + equal;

        CHECK( 3 == result.order() );
        CHECK( 4 == result.coefficients().size() );
        CHECK( -5. == Approx( result.coefficients()[0] ) );
        CHECK( 14. == Approx( result.coefficients()[1] ) );
        CHECK( -7. == Approx( result.coefficients()[2] ) );
        CHECK(  2. == Approx( result.coefficients()[3] ) );
        CHECK( true == std::holds_alternative< IntervalDomain< double > >( result.domain() ) );

        result = chunk - equal;

        CHECK( 2 == result.order() );
        CHECK(  3 == result.coefficients().size() );
        CHECK( -11. == Approx( result.coefficients()[0] ) );
        CHECK(  14. == Approx( result.coefficients()[1] ) );
        CHECK(  -7. == Approx( result.coefficients()[2] ) );
        CHECK( true == std::holds_alternative< IntervalDomain< double > >( result.domain() ) );

        result = chunk + large;

        CHECK( 4 == result.order() );
        CHECK(  5 == result.coefficients().size() );
        CHECK( -5. == Approx( result.coefficients()[0] ) );
        CHECK( 14. == Approx( result.coefficients()[1] ) );
        CHECK( -7. == Approx( result.coefficients()[2] ) );
        CHECK(  1. == Approx( result.coefficients()[3] ) );
        CHECK(  1. == Approx( result.coefficients()[4] ) );
        CHECK( true == std::holds_alternative< IntervalDomain< double > >( result.domain() ) );

        result = chunk - large;

        CHECK( 4 == result.order() );
        CHECK(  5 == result.coefficients().size() );
        CHECK( -11. == Approx( result.coefficients()[0] ) );
        CHECK(  14. == Approx( result.coefficients()[1] ) );
        CHECK(  -7. == Approx( result.coefficients()[2] ) );
        CHECK(   1. == Approx( result.coefficients()[3] ) );
        CHECK(  -1. == Approx( result.coefficients()[4] ) );
        CHECK( true == std::holds_alternative< IntervalDomain< double > >( result.domain() ) );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "invalid data" ) {

    WHEN( "the coefficient vector is empty" ) {

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( PolynomialSeries< double >( {} ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
