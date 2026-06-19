// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "scion/math/ConstantWeightFunction.hpp"

// convenience typedefs
using namespace njoy::scion;
using ConstantWeightFunction = math::ConstantWeightFunction< double, double >;

SCENARIO( "ConstantWeightFunction" ) {

  GIVEN( "a constant weight function" ) {

    WHEN( "the data is given explicitly" ) {

      double constant = 2.;

      ConstantWeightFunction weight( constant );

      THEN( "a ConstantWeightFunction can be constructed and members can be tested" ) {

        CHECK_THAT( 2., WithinRel( weight.constant() ) );
      } // THEN

      THEN( "the weight function can be evaluated" ) {

        CHECK_THAT( 2., WithinRel( weight( 1. ) ) );
        CHECK_THAT( 2., WithinRel( weight( 3. ) ) );
        CHECK_THAT( 2., WithinRel( weight( 5. ) ) );
      } // THEN

      THEN( "the integral of the weight function over a panel can be calculated" ) {

        CHECK_THAT( 4., WithinRel( weight.integral( 2., 4. ) ) );
        CHECK_THAT( 8., WithinRel( weight.integral( 1., 5. ) ) );
      } // THEN

      THEN( "the mean of the weight function over a panel can be calculated" ) {

        CHECK_THAT( 12., WithinRel( weight.mean( 2., 4. ) ) );
        CHECK_THAT( 24., WithinRel( weight.mean( 1., 5. ) ) );
      } // THEN

      // test results taken from the integration tests (times 2)

      THEN( "integration with histogram interpolation can be performed" ) {

        CHECK_THAT( 2., WithinRel( weight.integrateHistogram( 1., 2., 1., 4. ) ) );
        CHECK_THAT( 0., WithinRel( weight.integrateHistogram( 1., 1., 1., 4. ) ) );
      } // THEN

      THEN( "integration with lin-lin interpolation can be performed" ) {

        CHECK_THAT( 5., WithinRel( weight.integrateLinearLinear( 1., 2., 1., 4. ) ) );
        CHECK_THAT( 0., WithinRel( weight.integrateLinearLinear( 1., 1., 1., 4. ) ) );
      } // THEN

      THEN( "integration with lin-log interpolation can be performed" ) {

        CHECK_THAT( 2. * 2.67191487733311, WithinRel( weight.integrateLinearLogarithmic( 1., 2., 1., 4. ) ) );
        CHECK_THAT( 0., WithinRel( weight.integrateLinearLogarithmic( 1., 1., 1., 4. ) ) );
      } // THEN

      THEN( "integration with log-lin interpolation can be performed" ) {

        CHECK_THAT( 2. * 2.16404256133345, WithinRel( weight.integrateLogarithmicLinear( 1., 2., 1., 4. ) ) );
        CHECK_THAT( 0., WithinRel( weight.integrateLogarithmicLinear( 1., 1., 1., 4. ) ) );
      } // THEN

      THEN( "integration with log-log interpolation can be performed" ) {

        CHECK_THAT( 2. * 2.33333333333333, WithinRel( weight.integrateLogarithmicLogarithmic( 1., 2., 1., 4. ) ) );
        CHECK_THAT( 0., WithinRel( weight.integrateLogarithmicLogarithmic( 1., 1., 1., 4. ) ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
