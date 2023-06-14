#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>

// what we are testing
#include "scion/math/ChebyshevApproximation.hpp"

// other includes

// convenience typedefs
using namespace Catch;
using namespace njoy::scion;
template < typename X, typename Y = X > using ChebyshevApproximation = math::ChebyshevApproximation< X, Y >;
template < typename X > using IntervalDomain = math::IntervalDomain< X >;
template < typename X > using OpenDomain = math::OpenDomain< X >;

SCENARIO( "ChebyshevApproximation" ) {

  GIVEN( "a function" ) {

    WHEN( "approximated on [-1,1]" ) {

      auto function = [] ( double x ) { return x; };
      ChebyshevApproximation< double > chunk( -1., 1., function, 10 );

      THEN( "a ChebyshevApproximation can be constructed and members can be tested" ) {

        CHECK( 10 == chunk.order() );

        CHECK( 11 == chunk.coefficients().size() );

//        CHECK( 0.0 == Approx( chunk.coefficients()[0] ) );
        CHECK( 1.0 == Approx( chunk.coefficients()[1] ) );
//        CHECK( 0.0 == Approx( chunk.coefficients()[2] ) );
//        CHECK( 0.0 == Approx( chunk.coefficients()[3] ) );
//        CHECK( 0.0 == Approx( chunk.coefficients()[4] ) );
//        CHECK( 0.0 == Approx( chunk.coefficients()[5] ) );
//        CHECK( 0.0 == Approx( chunk.coefficients()[6] ) );
//        CHECK( 0.0 == Approx( chunk.coefficients()[7] ) );
//        CHECK( 0.0 == Approx( chunk.coefficients()[8] ) );
//        CHECK( 0.0 == Approx( chunk.coefficients()[9] ) );

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
//        CHECK(  0.0       == Approx( chunk(  0. ) ) );
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

      THEN( "arithmetic operations can be performed" ) {

        ChebyshevApproximation< double > small( -1., 1.,
                                                std::vector< double >{ 3., 0., 1. } );
        ChebyshevApproximation< double > result( -1., 1., std::vector< double >{ 0. } );

        chunk += 2.;

        CHECK( 10 == chunk.order() );
        CHECK( 11 == chunk.coefficients().size() );
        CHECK( 2.0 == Approx( chunk.coefficients()[0] ) );
        CHECK( 1.0 == Approx( chunk.coefficients()[1] ) );
//        CHECK( 0.0 == Approx( chunk.coefficients()[2] ) );
//        CHECK( 0.0 == Approx( chunk.coefficients()[3] ) );
//        CHECK( 0.0 == Approx( chunk.coefficients()[4] ) );
//        CHECK( 0.0 == Approx( chunk.coefficients()[5] ) );
//        CHECK( 0.0 == Approx( chunk.coefficients()[6] ) );
//        CHECK( 0.0 == Approx( chunk.coefficients()[7] ) );
//        CHECK( 0.0 == Approx( chunk.coefficients()[8] ) );
//        CHECK( 0.0 == Approx( chunk.coefficients()[9] ) );
        CHECK( true == std::holds_alternative< IntervalDomain< double > >( chunk.domain() ) );

        chunk -= 2.;

        CHECK( 10 == chunk.order() );
        CHECK( 11 == chunk.coefficients().size() );
//        CHECK( 0.0 == Approx( chunk.coefficients()[0] ) );
        CHECK( 1.0 == Approx( chunk.coefficients()[1] ) );
//        CHECK( 0.0 == Approx( chunk.coefficients()[2] ) );
//        CHECK( 0.0 == Approx( chunk.coefficients()[3] ) );
//        CHECK( 0.0 == Approx( chunk.coefficients()[4] ) );
//        CHECK( 0.0 == Approx( chunk.coefficients()[5] ) );
//        CHECK( 0.0 == Approx( chunk.coefficients()[6] ) );
//        CHECK( 0.0 == Approx( chunk.coefficients()[7] ) );
//        CHECK( 0.0 == Approx( chunk.coefficients()[8] ) );
//        CHECK( 0.0 == Approx( chunk.coefficients()[9] ) );
        CHECK( true == std::holds_alternative< IntervalDomain< double > >( chunk.domain() ) );

        chunk += small;

        CHECK( 10 == chunk.order() );
        CHECK( 11 == chunk.coefficients().size() );
        CHECK( 3.0 == Approx( chunk.coefficients()[0] ) );
        CHECK( 1.0 == Approx( chunk.coefficients()[1] ) );
        CHECK( 1.0 == Approx( chunk.coefficients()[2] ) );
//        CHECK( 0.0 == Approx( chunk.coefficients()[3] ) );
//        CHECK( 0.0 == Approx( chunk.coefficients()[4] ) );
//        CHECK( 0.0 == Approx( chunk.coefficients()[5] ) );
//        CHECK( 0.0 == Approx( chunk.coefficients()[6] ) );
//        CHECK( 0.0 == Approx( chunk.coefficients()[7] ) );
//        CHECK( 0.0 == Approx( chunk.coefficients()[8] ) );
//        CHECK( 0.0 == Approx( chunk.coefficients()[9] ) );
        CHECK( true == std::holds_alternative< IntervalDomain< double > >( chunk.domain() ) );

        chunk -= small;

        CHECK( 10 == chunk.order() );
        CHECK( 11 == chunk.coefficients().size() );
//        CHECK( 0.0 == Approx( chunk.coefficients()[0] ) );
        CHECK( 1.0 == Approx( chunk.coefficients()[1] ) );
//        CHECK( 0.0 == Approx( chunk.coefficients()[2] ) );
//        CHECK( 0.0 == Approx( chunk.coefficients()[3] ) );
//        CHECK( 0.0 == Approx( chunk.coefficients()[4] ) );
//        CHECK( 0.0 == Approx( chunk.coefficients()[5] ) );
//        CHECK( 0.0 == Approx( chunk.coefficients()[6] ) );
//        CHECK( 0.0 == Approx( chunk.coefficients()[7] ) );
//        CHECK( 0.0 == Approx( chunk.coefficients()[8] ) );
//        CHECK( 0.0 == Approx( chunk.coefficients()[9] ) );
        CHECK( true == std::holds_alternative< IntervalDomain< double > >( chunk.domain() ) );

        chunk *= 2.;

        CHECK( 10 == chunk.order() );
        CHECK( 11 == chunk.coefficients().size() );
//        CHECK( 0.0 == Approx( chunk.coefficients()[0] ) );
        CHECK( 2.0 == Approx( chunk.coefficients()[1] ) );
//        CHECK( 0.0 == Approx( chunk.coefficients()[2] ) );
//        CHECK( 0.0 == Approx( chunk.coefficients()[3] ) );
//        CHECK( 0.0 == Approx( chunk.coefficients()[4] ) );
//        CHECK( 0.0 == Approx( chunk.coefficients()[5] ) );
//        CHECK( 0.0 == Approx( chunk.coefficients()[6] ) );
//        CHECK( 0.0 == Approx( chunk.coefficients()[7] ) );
//        CHECK( 0.0 == Approx( chunk.coefficients()[8] ) );
//        CHECK( 0.0 == Approx( chunk.coefficients()[9] ) );
        CHECK( true == std::holds_alternative< IntervalDomain< double > >( chunk.domain() ) );

        chunk /= 2.;

        CHECK( 10 == chunk.order() );
        CHECK( 11 == chunk.coefficients().size() );
//        CHECK( 0.0 == Approx( chunk.coefficients()[0] ) );
        CHECK( 1.0 == Approx( chunk.coefficients()[1] ) );
//        CHECK( 0.0 == Approx( chunk.coefficients()[2] ) );
//        CHECK( 0.0 == Approx( chunk.coefficients()[3] ) );
//        CHECK( 0.0 == Approx( chunk.coefficients()[4] ) );
//        CHECK( 0.0 == Approx( chunk.coefficients()[5] ) );
//        CHECK( 0.0 == Approx( chunk.coefficients()[6] ) );
//        CHECK( 0.0 == Approx( chunk.coefficients()[7] ) );
//        CHECK( 0.0 == Approx( chunk.coefficients()[8] ) );
//        CHECK( 0.0 == Approx( chunk.coefficients()[9] ) );
        CHECK( true == std::holds_alternative< IntervalDomain< double > >( chunk.domain() ) );

        result = chunk + 2.;

        CHECK( 10 == result.order() );
        CHECK( 11 == result.coefficients().size() );
        CHECK( 2.0 == Approx( result.coefficients()[0] ) );
        CHECK( 1.0 == Approx( result.coefficients()[1] ) );
//        CHECK( 0.0 == Approx( result.coefficients()[2] ) );
//        CHECK( 0.0 == Approx( result.coefficients()[3] ) );
//        CHECK( 0.0 == Approx( result.coefficients()[4] ) );
//        CHECK( 0.0 == Approx( result.coefficients()[5] ) );
//        CHECK( 0.0 == Approx( result.coefficients()[6] ) );
//        CHECK( 0.0 == Approx( result.coefficients()[7] ) );
//        CHECK( 0.0 == Approx( result.coefficients()[8] ) );
//        CHECK( 0.0 == Approx( result.coefficients()[9] ) );
        CHECK( true == std::holds_alternative< IntervalDomain< double > >( result.domain() ) );

        result = chunk - 2.;

        CHECK( 10 == result.order() );
        CHECK( 11 == result.coefficients().size() );
        CHECK( -2.0 == Approx( result.coefficients()[0] ) );
        CHECK(  1.0 == Approx( result.coefficients()[1] ) );
//        CHECK(  0.0 == Approx( result.coefficients()[2] ) );
//        CHECK(  0.0 == Approx( result.coefficients()[3] ) );
//        CHECK(  0.0 == Approx( result.coefficients()[4] ) );
//        CHECK(  0.0 == Approx( result.coefficients()[5] ) );
//        CHECK(  0.0 == Approx( result.coefficients()[6] ) );
//        CHECK(  0.0 == Approx( result.coefficients()[7] ) );
//        CHECK(  0.0 == Approx( result.coefficients()[8] ) );
//        CHECK(  0.0 == Approx( result.coefficients()[9] ) );
        CHECK( true == std::holds_alternative< IntervalDomain< double > >( result.domain() ) );

        result = chunk + small;

        CHECK( 10 == result.order() );
        CHECK( 11 == result.coefficients().size() );
        CHECK( 3.0 == Approx( result.coefficients()[0] ) );
        CHECK( 1.0 == Approx( result.coefficients()[1] ) );
        CHECK( 1.0 == Approx( result.coefficients()[2] ) );
//        CHECK( 0.0 == Approx( result.coefficients()[3] ) );
//        CHECK( 0.0 == Approx( result.coefficients()[4] ) );
//        CHECK( 0.0 == Approx( result.coefficients()[5] ) );
//        CHECK( 0.0 == Approx( result.coefficients()[6] ) );
//        CHECK( 0.0 == Approx( result.coefficients()[7] ) );
//        CHECK( 0.0 == Approx( result.coefficients()[8] ) );
//        CHECK( 0.0 == Approx( result.coefficients()[9] ) );
        CHECK( true == std::holds_alternative< IntervalDomain< double > >( result.domain() ) );

        result = chunk - small;

        CHECK( 10 == result.order() );
        CHECK( 11 == result.coefficients().size() );
        CHECK( -3.0 == Approx( result.coefficients()[0] ) );
        CHECK(  1.0 == Approx( result.coefficients()[1] ) );
        CHECK( -1.0 == Approx( result.coefficients()[2] ) );
//        CHECK(  0.0 == Approx( result.coefficients()[3] ) );
//        CHECK(  0.0 == Approx( result.coefficients()[4] ) );
//        CHECK(  0.0 == Approx( result.coefficients()[5] ) );
//        CHECK(  0.0 == Approx( result.coefficients()[6] ) );
//        CHECK(  0.0 == Approx( result.coefficients()[7] ) );
//        CHECK(  0.0 == Approx( result.coefficients()[8] ) );
//        CHECK(  0.0 == Approx( result.coefficients()[9] ) );
        CHECK( true == std::holds_alternative< IntervalDomain< double > >( result.domain() ) );

        result = chunk * 2.;

        CHECK( 10 == result.order() );
        CHECK( 11 == result.coefficients().size() );
//        CHECK( 0.0 == Approx( result.coefficients()[0] ) );
        CHECK( 2.0 == Approx( result.coefficients()[1] ) );
//        CHECK( 0.0 == Approx( result.coefficients()[2] ) );
//        CHECK( 0.0 == Approx( result.coefficients()[3] ) );
//        CHECK( 0.0 == Approx( result.coefficients()[4] ) );
//        CHECK( 0.0 == Approx( result.coefficients()[5] ) );
//        CHECK( 0.0 == Approx( result.coefficients()[6] ) );
//        CHECK( 0.0 == Approx( result.coefficients()[7] ) );
//        CHECK( 0.0 == Approx( result.coefficients()[8] ) );
//        CHECK( 0.0 == Approx( result.coefficients()[9] ) );
        CHECK( true == std::holds_alternative< IntervalDomain< double > >( result.domain() ) );

        result = chunk / 2.;

        CHECK( 10 == result.order() );
        CHECK( 11 == result.coefficients().size() );
//        CHECK( 0.0 == Approx( result.coefficients()[0] ) );
        CHECK( 0.5 == Approx( result.coefficients()[1] ) );
//        CHECK( 0.0 == Approx( result.coefficients()[2] ) );
//        CHECK( 0.0 == Approx( result.coefficients()[3] ) );
//        CHECK( 0.0 == Approx( result.coefficients()[4] ) );
//        CHECK( 0.0 == Approx( result.coefficients()[5] ) );
//        CHECK( 0.0 == Approx( result.coefficients()[6] ) );
//        CHECK( 0.0 == Approx( result.coefficients()[7] ) );
//        CHECK( 0.0 == Approx( result.coefficients()[8] ) );
//        CHECK( 0.0 == Approx( result.coefficients()[9] ) );
        CHECK( true == std::holds_alternative< IntervalDomain< double > >( result.domain() ) );
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
//        CHECK( 0.0 == Approx( chunk.coefficients()[2] ) );
//        CHECK( 0.0 == Approx( chunk.coefficients()[3] ) );
//        CHECK( 0.0 == Approx( chunk.coefficients()[4] ) );
//        CHECK( 0.0 == Approx( chunk.coefficients()[5] ) );
//        CHECK( 0.0 == Approx( chunk.coefficients()[6] ) );
//        CHECK( 0.0 == Approx( chunk.coefficients()[7] ) );
//        CHECK( 0.0 == Approx( chunk.coefficients()[8] ) );
//        CHECK( 0.0 == Approx( chunk.coefficients()[9] ) );

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
//        CHECK(  0.0       == Approx( chunk(  0. ) ) );
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

      THEN( "the domain can be tested" ) {

        CHECK( true == chunk.isInside( -2. ) );
        CHECK( true == chunk.isInside(  1. ) );
        CHECK( true == chunk.isInside(  4. ) );

        CHECK( false == chunk.isContained( -2. ) );
        CHECK( true == chunk.isContained( 1. ) );
        CHECK( false == chunk.isContained( 4. ) );

        CHECK( true == chunk.isSameDomain( IntervalDomain< double >( -2., 4. ) ) );
        CHECK( false == chunk.isSameDomain( IntervalDomain< double >( 0., 4. ) ) );
        CHECK( false == chunk.isSameDomain( OpenDomain< double >() ) );
      } // THEN

      THEN( "arithmetic operations can be performed" ) {

        chunk += 2.;

        CHECK( 10 == chunk.order() );
        CHECK( 11 == chunk.coefficients().size() );
        CHECK( 3.0 == Approx( chunk.coefficients()[0] ) );
        CHECK( 3.0 == Approx( chunk.coefficients()[1] ) );
//        CHECK( 0.0 == Approx( chunk.coefficients()[2] ) );
//        CHECK( 0.0 == Approx( chunk.coefficients()[3] ) );
//        CHECK( 0.0 == Approx( chunk.coefficients()[4] ) );
//        CHECK( 0.0 == Approx( chunk.coefficients()[5] ) );
//        CHECK( 0.0 == Approx( chunk.coefficients()[6] ) );
//        CHECK( 0.0 == Approx( chunk.coefficients()[7] ) );
//        CHECK( 0.0 == Approx( chunk.coefficients()[8] ) );
//        CHECK( 0.0 == Approx( chunk.coefficients()[9] ) );
        CHECK( true == std::holds_alternative< IntervalDomain< double > >( chunk.domain() ) );

        chunk -= 2.;

        CHECK( 10 == chunk.order() );
        CHECK( 11 == chunk.coefficients().size() );
        CHECK( 1.0 == Approx( chunk.coefficients()[0] ) );
        CHECK( 3.0 == Approx( chunk.coefficients()[1] ) );
//        CHECK( 0.0 == Approx( chunk.coefficients()[2] ) );
//        CHECK( 0.0 == Approx( chunk.coefficients()[3] ) );
//        CHECK( 0.0 == Approx( chunk.coefficients()[4] ) );
//        CHECK( 0.0 == Approx( chunk.coefficients()[5] ) );
//        CHECK( 0.0 == Approx( chunk.coefficients()[6] ) );
//        CHECK( 0.0 == Approx( chunk.coefficients()[7] ) );
//        CHECK( 0.0 == Approx( chunk.coefficients()[8] ) );
//        CHECK( 0.0 == Approx( chunk.coefficients()[9] ) );
        CHECK( true == std::holds_alternative< IntervalDomain< double > >( chunk.domain() ) );

        chunk *= 2.;

        CHECK( 10 == chunk.order() );
        CHECK( 11 == chunk.coefficients().size() );
        CHECK( 2.0 == Approx( chunk.coefficients()[0] ) );
        CHECK( 6.0 == Approx( chunk.coefficients()[1] ) );
//        CHECK( 0.0 == Approx( chunk.coefficients()[2] ) );
//        CHECK( 0.0 == Approx( chunk.coefficients()[3] ) );
//        CHECK( 0.0 == Approx( chunk.coefficients()[4] ) );
//        CHECK( 0.0 == Approx( chunk.coefficients()[5] ) );
//        CHECK( 0.0 == Approx( chunk.coefficients()[6] ) );
//        CHECK( 0.0 == Approx( chunk.coefficients()[7] ) );
//        CHECK( 0.0 == Approx( chunk.coefficients()[8] ) );
//        CHECK( 0.0 == Approx( chunk.coefficients()[9] ) );
        CHECK( true == std::holds_alternative< IntervalDomain< double > >( chunk.domain() ) );

        chunk /= 2.;

        CHECK( 10 == chunk.order() );
        CHECK( 11 == chunk.coefficients().size() );
        CHECK( 1.0 == Approx( chunk.coefficients()[0] ) );
        CHECK( 3.0 == Approx( chunk.coefficients()[1] ) );
//        CHECK( 0.0 == Approx( chunk.coefficients()[2] ) );
//        CHECK( 0.0 == Approx( chunk.coefficients()[3] ) );
//        CHECK( 0.0 == Approx( chunk.coefficients()[4] ) );
//        CHECK( 0.0 == Approx( chunk.coefficients()[5] ) );
//        CHECK( 0.0 == Approx( chunk.coefficients()[6] ) );
//        CHECK( 0.0 == Approx( chunk.coefficients()[7] ) );
//        CHECK( 0.0 == Approx( chunk.coefficients()[8] ) );
//        CHECK( 0.0 == Approx( chunk.coefficients()[9] ) );
        CHECK( true == std::holds_alternative< IntervalDomain< double > >( chunk.domain() ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
