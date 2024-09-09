// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;
using Catch::Matchers::WithinAbs;

// what we are testing
#include "scion/math/ChebyshevSeries.hpp"

// other includes

// convenience typedefs
using namespace njoy::scion;
template < typename X, typename Y = X > using ChebyshevSeries = math::ChebyshevSeries< X, Y >;
template < typename X > using IntervalDomain = math::IntervalDomain< X >;
template < typename X > using OpenDomain = math::OpenDomain< X >;
template < typename X, typename Y = X >
using InterpolationTable = math::InterpolationTable< X, Y >;
template < typename X > using IntervalDomain = math::IntervalDomain< X >;
using InterpolationType = interpolation::InterpolationType;
template< typename X, typename Y = X >
using ToleranceConvergence = linearisation::ToleranceConvergence< X, Y >;

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
        CHECK_THAT( -11.50, WithinRel( chunk.coefficients()[0] ) );
        CHECK_THAT(  14.75, WithinRel( chunk.coefficients()[1] ) );
        CHECK_THAT(  -3.50, WithinRel( chunk.coefficients()[2] ) );
        CHECK_THAT(   0.25, WithinRel( chunk.coefficients()[3] ) );

        CHECK( true == std::holds_alternative< IntervalDomain< double > >( chunk.domain() ) );
      } // THEN

      THEN( "a ChebyshevSeries can be evaluated" ) {

        CHECK_THAT(  -8.0, WithinRel( chunk(  0. ) ) );
        CHECK_THAT(   0.0, WithinRel( chunk(  1. ) ) );
        CHECK_THAT( -30.0, WithinRel( chunk( -1. ) ) );
      } // THEN

      THEN( "roots can be calculated" ) {

        std::vector< double > roots = chunk.roots();

        CHECK( 3 == roots.size() );
        CHECK_THAT( 1.0, WithinRel( roots[0] ) );
        CHECK_THAT( 2.0, WithinRel( roots[1] ) );
        CHECK_THAT( 4.0, WithinRel( roots[2] ) );

        roots = chunk.roots( -8. );

        CHECK( 1 == roots.size() );
        CHECK_THAT( 0.0, WithinAbs( roots[0], 1e-12 ) );
      } // THEN

      THEN( "the domain can be tested" ) {

        CHECK( true == chunk.isInside( -1. ) );
        CHECK( true == chunk.isInside(  0. ) );
        CHECK( true == chunk.isInside(  1. ) );

        CHECK( false == chunk.isContained( -1. ) );
        CHECK( true == chunk.isContained( 0. ) );
        CHECK( false == chunk.isContained( 1. ) );

        CHECK( true == chunk.isSameDomain( IntervalDomain< double >( -1., 1. ) ) );
        CHECK( false == chunk.isSameDomain( IntervalDomain< double >( 0., 1. ) ) );
        CHECK( false == chunk.isSameDomain( OpenDomain< double >() ) );
      } // THEN

      THEN( "a ChebyshevSeries can be differentiated" ) {

        ChebyshevSeries< double > first = chunk.derivative();
        ChebyshevSeries< double > second = first.derivative();
        ChebyshevSeries< double > third = second.derivative();
        ChebyshevSeries< double > fourth = third.derivative();

        CHECK( 2 == first.order() );
        CHECK( 3 == first.coefficients().size() );
        CHECK_THAT(  15.5, WithinRel( first.coefficients()[0] ) );
        CHECK_THAT( -14.0, WithinRel( first.coefficients()[1] ) );
        CHECK_THAT(   1.5, WithinRel( first.coefficients()[2] ) );

        CHECK( 1 == second.order() );
        CHECK( 2 == second.coefficients().size() );
        CHECK_THAT( -14., WithinRel( second.coefficients()[0] ) );
        CHECK_THAT(   6., WithinRel( second.coefficients()[1] ) );

        CHECK( 0 == third.order() );
        CHECK( 1 == third.coefficients().size() );
        CHECK_THAT( 6., WithinRel( third.coefficients()[0] ) );

        CHECK( 0 == fourth.order() );
        CHECK( 1 == fourth.coefficients().size() );
        CHECK_THAT( 0., WithinRel( fourth.coefficients()[0] ) );
      } // THEN

      THEN( "a ChebyshevSeries can be integrated" ) {

        ChebyshevSeries< double > primitive = chunk.primitive();

        CHECK( 4 == primitive.order() );
        CHECK( 5 == primitive.coefficients().size() );
        CHECK_THAT(  3.59375           , WithinRel( primitive.coefficients()[0] ) );
        CHECK_THAT( -9.75              , WithinRel( primitive.coefficients()[1] ) );
        CHECK_THAT(  3.625             , WithinRel( primitive.coefficients()[2] ) );
        CHECK_THAT( -0.5833333333333333, WithinRel( primitive.coefficients()[3] ) );
        CHECK_THAT(  0.03125           , WithinRel( primitive.coefficients()[4] ) );

        primitive = chunk.primitive( -1. );

        CHECK( 4 == primitive.order() );
        CHECK( 5 == primitive.coefficients().size() );
        CHECK_THAT( -13.989583333333333, WithinRel( primitive.coefficients()[0] ) );
        CHECK_THAT( -9.75              , WithinRel( primitive.coefficients()[1] ) );
        CHECK_THAT(  3.625             , WithinRel( primitive.coefficients()[2] ) );
        CHECK_THAT( -0.5833333333333333, WithinRel( primitive.coefficients()[3] ) );
        CHECK_THAT(  0.03125           , WithinRel( primitive.coefficients()[4] ) );
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

        CHECK_THAT( -1.0      , WithinRel( linear.x()[0] ) );
        CHECK_THAT( -0.75     , WithinRel( linear.x()[1] ) );
        CHECK_THAT( -0.5      , WithinRel( linear.x()[2] ) );
        CHECK_THAT( -0.25     , WithinRel( linear.x()[3] ) );
        CHECK_THAT( -0.125    , WithinRel( linear.x()[4] ) );
        CHECK_THAT(  0.0      , WithinRel( linear.x()[5] ) );
        CHECK_THAT(  0.125    , WithinRel( linear.x()[6] ) );
        CHECK_THAT(  0.25     , WithinRel( linear.x()[7] ) );
        CHECK_THAT(  0.375    , WithinRel( linear.x()[8] ) );
        CHECK_THAT(  0.5      , WithinRel( linear.x()[9] ) );
        CHECK_THAT(  0.625    , WithinRel( linear.x()[10] ) );
        CHECK_THAT(  0.6875   , WithinRel( linear.x()[11] ) );
        CHECK_THAT(  0.75     , WithinRel( linear.x()[12] ) );
        CHECK_THAT(  0.8125   , WithinRel( linear.x()[13] ) );
        CHECK_THAT(  0.875    , WithinRel( linear.x()[14] ) );
        CHECK_THAT(  0.90625  , WithinRel( linear.x()[15] ) );
        CHECK_THAT(  0.9375   , WithinRel( linear.x()[16] ) );
        CHECK_THAT(  0.96875  , WithinRel( linear.x()[17] ) );
        CHECK_THAT(  0.984375 , WithinRel( linear.x()[18] ) );
        CHECK_THAT(  0.9921875, WithinRel( linear.x()[19] ) );
        CHECK_THAT(  1.0      , WithinRel( linear.x()[20] ) );

        CHECK_THAT( -30.0             , WithinRel( linear.y()[0] ) );
        CHECK_THAT( -22.859375        , WithinRel( linear.y()[1] ) );
        CHECK_THAT( -16.875           , WithinRel( linear.y()[2] ) );
        CHECK_THAT( -11.953125        , WithinRel( linear.y()[3] ) );
        CHECK_THAT( -9.861328125      , WithinRel( linear.y()[4] ) );
        CHECK_THAT( -8.0              , WithinRel( linear.y()[5] ) );
        CHECK_THAT( -6.357421875      , WithinRel( linear.y()[6] ) );
        CHECK_THAT( -4.921875         , WithinRel( linear.y()[7] ) );
        CHECK_THAT( -3.681640625      , WithinRel( linear.y()[8] ) );
        CHECK_THAT( -2.625            , WithinRel( linear.y()[9] ) );
        CHECK_THAT( -1.740234375      , WithinRel( linear.y()[10] ) );
        CHECK_THAT( -1.358642578125   , WithinRel( linear.y()[11] ) );
        CHECK_THAT( -1.015625         , WithinRel( linear.y()[12] ) );
        CHECK_THAT( -0.709716796875   , WithinRel( linear.y()[13] ) );
        CHECK_THAT( -0.439453125      , WithinRel( linear.y()[14] ) );
        CHECK_THAT( -0.317230224609375, WithinRel( linear.y()[15] ) );
        CHECK_THAT( -0.203369140625   , WithinRel( linear.y()[16] ) );
        CHECK_THAT( -0.097686767578125, WithinRel( linear.y()[17] ) );
        CHECK_THAT( -0.047855377197266, WithinRel( linear.y()[18] ) );
        CHECK_THAT( -0.023682117462158, WithinRel( linear.y()[19] ) );
        CHECK_THAT(  0.0              , WithinRel( linear.y()[20] ) );

        CHECK( true == linear.isLinearised() );
      } // THEN

      THEN( "arithmetic operations can be performed" ) {

        ChebyshevSeries< double > small( { 3., 0., 1. } );
        ChebyshevSeries< double > equal( { 3., 0., 0., 1. } );
        ChebyshevSeries< double > large( { 3., 0., 0., 0., 1. } );
        ChebyshevSeries< double > result( { 0. } );

        result = -chunk;

        CHECK( 3 == result.order() );
        CHECK( 4 == result.coefficients().size() );
        CHECK_THAT(  11.50, WithinRel( result.coefficients()[0] ) );
        CHECK_THAT( -14.75, WithinRel( result.coefficients()[1] ) );
        CHECK_THAT(   3.50, WithinRel( result.coefficients()[2] ) );
        CHECK_THAT(  -0.25, WithinRel( result.coefficients()[3] ) );
        CHECK( true == std::holds_alternative< IntervalDomain< double > >( result.domain() ) );

        chunk += 2.;

        CHECK( 3 == chunk.order() );
        CHECK( 4 == chunk.coefficients().size() );
        CHECK_THAT( -9.50, WithinRel( chunk.coefficients()[0] ) );
        CHECK_THAT( 14.75, WithinRel( chunk.coefficients()[1] ) );
        CHECK_THAT( -3.50, WithinRel( chunk.coefficients()[2] ) );
        CHECK_THAT(  0.25, WithinRel( chunk.coefficients()[3] ) );
        CHECK( true == std::holds_alternative< IntervalDomain< double > >( chunk.domain() ) );

        chunk -= 2.;

        CHECK( 3 == chunk.order() );
        CHECK( 4 == chunk.coefficients().size() );
        CHECK_THAT( -11.50, WithinRel( chunk.coefficients()[0] ) );
        CHECK_THAT(  14.75, WithinRel( chunk.coefficients()[1] ) );
        CHECK_THAT(  -3.50, WithinRel( chunk.coefficients()[2] ) );
        CHECK_THAT(   0.25, WithinRel( chunk.coefficients()[3] ) );
        CHECK( true == std::holds_alternative< IntervalDomain< double > >( chunk.domain() ) );

        chunk += small;

        CHECK( 3 == chunk.order() );
        CHECK( 4 == chunk.coefficients().size() );
        CHECK_THAT( -8.50, WithinRel( chunk.coefficients()[0] ) );
        CHECK_THAT( 14.75, WithinRel( chunk.coefficients()[1] ) );
        CHECK_THAT( -2.50, WithinRel( chunk.coefficients()[2] ) );
        CHECK_THAT(  0.25, WithinRel( chunk.coefficients()[3] ) );
        CHECK( true == std::holds_alternative< IntervalDomain< double > >( chunk.domain() ) );

        chunk -= small;

        CHECK( 3 == chunk.order() );
        CHECK( 4 == chunk.coefficients().size() );
        CHECK_THAT( -11.50, WithinRel( chunk.coefficients()[0] ) );
        CHECK_THAT(  14.75, WithinRel( chunk.coefficients()[1] ) );
        CHECK_THAT(  -3.50, WithinRel( chunk.coefficients()[2] ) );
        CHECK_THAT(   0.25, WithinRel( chunk.coefficients()[3] ) );
        CHECK( true == std::holds_alternative< IntervalDomain< double > >( chunk.domain() ) );

        chunk += equal;

        CHECK( 3 == chunk.order() );
        CHECK( 4 == chunk.coefficients().size() );
        CHECK_THAT( -8.50, WithinRel( chunk.coefficients()[0] ) );
        CHECK_THAT( 14.75, WithinRel( chunk.coefficients()[1] ) );
        CHECK_THAT( -3.50, WithinRel( chunk.coefficients()[2] ) );
        CHECK_THAT(  1.25, WithinRel( chunk.coefficients()[3] ) );
        CHECK( true == std::holds_alternative< IntervalDomain< double > >( chunk.domain() ) );

        chunk -= equal;

        CHECK( 3 == chunk.order() );
        CHECK( 4 == chunk.coefficients().size() );
        CHECK_THAT( -11.50, WithinRel( chunk.coefficients()[0] ) );
        CHECK_THAT(  14.75, WithinRel( chunk.coefficients()[1] ) );
        CHECK_THAT(  -3.50, WithinRel( chunk.coefficients()[2] ) );
        CHECK_THAT(   0.25, WithinRel( chunk.coefficients()[3] ) );
        CHECK( true == std::holds_alternative< IntervalDomain< double > >( chunk.domain() ) );

        chunk += large;

        CHECK( 4 == chunk.order() );
        CHECK(  5 == chunk.coefficients().size() );
        CHECK_THAT( -8.50, WithinRel( chunk.coefficients()[0] ) );
        CHECK_THAT( 14.75, WithinRel( chunk.coefficients()[1] ) );
        CHECK_THAT( -3.50, WithinRel( chunk.coefficients()[2] ) );
        CHECK_THAT(  0.25, WithinRel( chunk.coefficients()[3] ) );
        CHECK_THAT(  1.  , WithinRel( chunk.coefficients()[4] ) );
        CHECK( true == std::holds_alternative< IntervalDomain< double > >( chunk.domain() ) );

        chunk -= large;

        CHECK( 3 == chunk.order() );
        CHECK( 4 == chunk.coefficients().size() );
        CHECK_THAT( -11.50, WithinRel( chunk.coefficients()[0] ) );
        CHECK_THAT(  14.75, WithinRel( chunk.coefficients()[1] ) );
        CHECK_THAT(  -3.50, WithinRel( chunk.coefficients()[2] ) );
        CHECK_THAT(   0.25, WithinRel( chunk.coefficients()[3] ) );
        CHECK( true == std::holds_alternative< IntervalDomain< double > >( chunk.domain() ) );

        chunk *= 2.;

        CHECK( 3 == chunk.order() );
        CHECK( 4 == chunk.coefficients().size() );
        CHECK_THAT( -23.0, WithinRel( chunk.coefficients()[0] ) );
        CHECK_THAT(  29.5, WithinRel( chunk.coefficients()[1] ) );
        CHECK_THAT(  -7.0, WithinRel( chunk.coefficients()[2] ) );
        CHECK_THAT(   0.5, WithinRel( chunk.coefficients()[3] ) );
        CHECK( true == std::holds_alternative< IntervalDomain< double > >( chunk.domain() ) );

        chunk /= 2.;

        CHECK( 3 == chunk.order() );
        CHECK( 4 == chunk.coefficients().size() );
        CHECK_THAT( -11.50, WithinRel( chunk.coefficients()[0] ) );
        CHECK_THAT(  14.75, WithinRel( chunk.coefficients()[1] ) );
        CHECK_THAT(  -3.50, WithinRel( chunk.coefficients()[2] ) );
        CHECK_THAT(   0.25, WithinRel( chunk.coefficients()[3] ) );
        CHECK( true == std::holds_alternative< IntervalDomain< double > >( chunk.domain() ) );

        result = chunk + 2.;

        CHECK( 3 == result.order() );
        CHECK( 4 == result.coefficients().size() );
        CHECK_THAT( -9.50, WithinRel( result.coefficients()[0] ) );
        CHECK_THAT( 14.75, WithinRel( result.coefficients()[1] ) );
        CHECK_THAT( -3.50, WithinRel( result.coefficients()[2] ) );
        CHECK_THAT(  0.25, WithinRel( result.coefficients()[3] ) );
        CHECK( true == std::holds_alternative< IntervalDomain< double > >( result.domain() ) );

        result = 2. + chunk;

        CHECK( 3 == result.order() );
        CHECK( 4 == result.coefficients().size() );
        CHECK_THAT( -9.50, WithinRel( result.coefficients()[0] ) );
        CHECK_THAT( 14.75, WithinRel( result.coefficients()[1] ) );
        CHECK_THAT( -3.50, WithinRel( result.coefficients()[2] ) );
        CHECK_THAT(  0.25, WithinRel( result.coefficients()[3] ) );
        CHECK( true == std::holds_alternative< IntervalDomain< double > >( result.domain() ) );

        result = chunk - 2.;

        CHECK( 3 == result.order() );
        CHECK( 4 == result.coefficients().size() );
        CHECK_THAT( -13.50, WithinRel( result.coefficients()[0] ) );
        CHECK_THAT(  14.75, WithinRel( result.coefficients()[1] ) );
        CHECK_THAT(  -3.50, WithinRel( result.coefficients()[2] ) );
        CHECK_THAT(   0.25, WithinRel( result.coefficients()[3] ) );
        CHECK( true == std::holds_alternative< IntervalDomain< double > >( result.domain() ) );

        result = 2. - chunk;

        CHECK( 3 == result.order() );
        CHECK( 4 == result.coefficients().size() );
        CHECK_THAT(  13.50, WithinRel( result.coefficients()[0] ) );
        CHECK_THAT( -14.75, WithinRel( result.coefficients()[1] ) );
        CHECK_THAT(   3.50, WithinRel( result.coefficients()[2] ) );
        CHECK_THAT(  -0.25, WithinRel( result.coefficients()[3] ) );
        CHECK( true == std::holds_alternative< IntervalDomain< double > >( result.domain() ) );

        result = chunk * 2.;

        CHECK( 3 == result.order() );
        CHECK( 4 == result.coefficients().size() );
        CHECK_THAT( -23.0, WithinRel( result.coefficients()[0] ) );
        CHECK_THAT(  29.5, WithinRel( result.coefficients()[1] ) );
        CHECK_THAT(  -7.0, WithinRel( result.coefficients()[2] ) );
        CHECK_THAT(   0.5, WithinRel( result.coefficients()[3] ) );
        CHECK( true == std::holds_alternative< IntervalDomain< double > >( result.domain() ) );

        result = 2. * chunk;

        CHECK( 3 == result.order() );
        CHECK( 4 == result.coefficients().size() );
        CHECK_THAT( -23.0, WithinRel( result.coefficients()[0] ) );
        CHECK_THAT(  29.5, WithinRel( result.coefficients()[1] ) );
        CHECK_THAT(  -7.0, WithinRel( result.coefficients()[2] ) );
        CHECK_THAT(   0.5, WithinRel( result.coefficients()[3] ) );
        CHECK( true == std::holds_alternative< IntervalDomain< double > >( result.domain() ) );

        result = chunk / 2.;

        CHECK( 3 == result.order() );
        CHECK( 4 == result.coefficients().size() );
        CHECK_THAT( -5.750, WithinRel( result.coefficients()[0] ) );
        CHECK_THAT(  7.375, WithinRel( result.coefficients()[1] ) );
        CHECK_THAT( -1.750, WithinRel( result.coefficients()[2] ) );
        CHECK_THAT(  0.125, WithinRel( result.coefficients()[3] ) );
        CHECK( true == std::holds_alternative< IntervalDomain< double > >( result.domain() ) );

        result = chunk + small;

        CHECK( 3 == result.order() );
        CHECK( 4 == result.coefficients().size() );
        CHECK_THAT( -8.50, WithinRel( result.coefficients()[0] ) );
        CHECK_THAT( 14.75, WithinRel( result.coefficients()[1] ) );
        CHECK_THAT( -2.50, WithinRel( result.coefficients()[2] ) );
        CHECK_THAT(  0.25, WithinRel( result.coefficients()[3] ) );
        CHECK( true == std::holds_alternative< IntervalDomain< double > >( result.domain() ) );

        result = chunk - small;

        CHECK( 3 == result.order() );
        CHECK( 4 == result.coefficients().size() );
        CHECK_THAT( -14.50, WithinRel( result.coefficients()[0] ) );
        CHECK_THAT(  14.75, WithinRel( result.coefficients()[1] ) );
        CHECK_THAT(  -4.50, WithinRel( result.coefficients()[2] ) );
        CHECK_THAT(   0.25, WithinRel( result.coefficients()[3] ) );
        CHECK( true == std::holds_alternative< IntervalDomain< double > >( result.domain() ) );

        result = chunk + equal;

        CHECK( 3 == result.order() );
        CHECK( 4 == result.coefficients().size() );
        CHECK_THAT( -8.50, WithinRel( result.coefficients()[0] ) );
        CHECK_THAT( 14.75, WithinRel( result.coefficients()[1] ) );
        CHECK_THAT( -3.50, WithinRel( result.coefficients()[2] ) );
        CHECK_THAT(  1.25, WithinRel( result.coefficients()[3] ) );
        CHECK( true == std::holds_alternative< IntervalDomain< double > >( result.domain() ) );

        result = chunk - equal;

        CHECK( 3 == result.order() );
        CHECK( 4 == result.coefficients().size() );
        CHECK_THAT( -14.50, WithinRel( result.coefficients()[0] ) );
        CHECK_THAT(  14.75, WithinRel( result.coefficients()[1] ) );
        CHECK_THAT(  -3.50, WithinRel( result.coefficients()[2] ) );
        CHECK_THAT(  -0.75, WithinRel( result.coefficients()[3] ) );
        CHECK( true == std::holds_alternative< IntervalDomain< double > >( result.domain() ) );

        result = chunk + large;

        CHECK( 4 == result.order() );
        CHECK( 5 == result.coefficients().size() );
        CHECK_THAT( -8.50, WithinRel( result.coefficients()[0] ) );
        CHECK_THAT( 14.75, WithinRel( result.coefficients()[1] ) );
        CHECK_THAT( -3.50, WithinRel( result.coefficients()[2] ) );
        CHECK_THAT(  0.25, WithinRel( result.coefficients()[3] ) );
        CHECK_THAT(  1.00, WithinRel( result.coefficients()[4] ) );
        CHECK( true == std::holds_alternative< IntervalDomain< double > >( result.domain() ) );

        result = chunk - large;

        CHECK( 4 == result.order() );
        CHECK( 5 == result.coefficients().size() );
        CHECK_THAT( -14.50, WithinRel( result.coefficients()[0] ) );
        CHECK_THAT(  14.75, WithinRel( result.coefficients()[1] ) );
        CHECK_THAT(  -3.50, WithinRel( result.coefficients()[2] ) );
        CHECK_THAT(   0.25, WithinRel( result.coefficients()[3] ) );
        CHECK_THAT(  -1.00, WithinRel( result.coefficients()[4] ) );
        CHECK( true == std::holds_alternative< IntervalDomain< double > >( result.domain() ) );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "invalid data" ) {

    WHEN( "the coefficient vector is empty" ) {

      THEN( "an exception is thrown" ) {

        std::vector< double > empty = {};
        CHECK_THROWS( ChebyshevSeries< double >( empty ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
