// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "scion/math/MeanWeightFunction.hpp"

// convenience typedefs
using namespace njoy::scion;
using MeanWeightFunction = math::MeanWeightFunction< double >;

SCENARIO( "MeanWeightFunction" ) {

  GIVEN( "a constant weight function" ) {

    WHEN( "the data is given explicitly" ) {

      MeanWeightFunction weight;

      THEN( "the weight function can be evaluated" ) {

        CHECK_THAT( 1., WithinRel( weight( 1. ) ) );
        CHECK_THAT( 3., WithinRel( weight( 3. ) ) );
        CHECK_THAT( 5., WithinRel( weight( 5. ) ) );
      } // THEN

      THEN( "the integral of the weight function over a panel can be calculated" ) {

        CHECK_THAT(  6., WithinRel( weight.integral( 2., 4. ) ) );
        CHECK_THAT( 12., WithinRel( weight.integral( 1., 5. ) ) );
      } // THEN

      // test results taken from the mean integration tests

      THEN( "integration with histogram interpolation can be performed" ) {

        CHECK_THAT( 1.5, WithinRel( weight.integrateHistogram( 1., 2., 1., 4. ) ) );
        CHECK_THAT( 0., WithinRel( weight.integrateHistogram( 1., 1., 1., 4. ) ) );
      } // THEN

      THEN( "integration with lin-lin interpolation can be performed" ) {

        CHECK_THAT( 4., WithinRel( weight.integrateLinearLinear( 1., 2., 1., 4. ) ) );
        CHECK_THAT( 0., WithinRel( weight.integrateLinearLinear( 1., 1., 1., 4. ) ) );
      } // THEN

      THEN( "integration with lin-log interpolation can be performed" ) {

        // this value was calculated using Wolfram Alpha using this command:
        // "integrate x ( 1 + 3 / ln(2) * ln(x) ) dx between 1 and 2"
        // it was verified using Gauss-Legendre 64 quadrature as well
        CHECK_THAT( 4.2539361579999, WithinRel( weight.integrateLinearLogarithmic( 1., 2., 1., 4. ) ) );
        CHECK_THAT( 0., WithinRel( weight.integrateLinearLogarithmic( 1., 1., 1., 4. ) ) );
      } // THEN

      THEN( "integration with log-lin interpolation can be performed" ) {

        // this value was calculated using Wolfram Alpha using this command:
        // "integrate x exp( ln(4) (x-1) ) dx between 1 and 2"
        // it was verified using Gauss-Legendre 64 quadrature as well
        CHECK_THAT( 3.48840590735717, WithinRel( weight.integrateLogarithmicLinear( 1., 2., 1., 4. ) ) );
        CHECK_THAT( 0., WithinRel( weight.integrateLogarithmicLinear( 1., 1., 1., 4. ) ) );
      } // THEN

      THEN( "integration with log-log interpolation can be performed" ) {

        // this value was calculated using Wolfram Alpha using this command:
        // "integrate x exp( ln(4)/ln(2) ln(x) ) dx between 1 and 2"
        // it was verified using Gauss-Legendre 64 quadrature as well
        CHECK_THAT( 3.75, WithinRel( weight.integrateLogarithmicLogarithmic( 1., 2., 1., 4. ) ) );
        CHECK_THAT( 0., WithinRel( weight.integrateLogarithmicLogarithmic( 1., 1., 1., 4. ) ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
