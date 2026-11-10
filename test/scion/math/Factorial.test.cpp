// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "scion/math/Factorial.hpp"

// other includes

// convenience typedefs
using namespace njoy::scion;

SCENARIO( "Factorial" ) {

  CHECK(                      1  == math::factorial(  0 ) );
  CHECK(                      1  == math::factorial(  1 ) );
  CHECK(                      2  == math::factorial(  2 ) );
  CHECK(                      6  == math::factorial(  3 ) );
  CHECK(                     24  == math::factorial(  4 ) );
  CHECK(                    120  == math::factorial(  5 ) );
  CHECK(                    720  == math::factorial(  6 ) );
  CHECK(                   5040  == math::factorial(  7 ) );
  CHECK(                  40320  == math::factorial(  8 ) );
  CHECK(                 362880  == math::factorial(  9 ) );
  CHECK(                3628800  == math::factorial( 10 ) );
  CHECK(               39916800  == math::factorial( 11 ) );
  CHECK(              479001600  == math::factorial( 12 ) );
  CHECK(             6227020800  == math::factorial( 13 ) );
  CHECK(            87178291200  == math::factorial( 14 ) );
  CHECK(          1307674368000  == math::factorial( 15 ) );
  CHECK(         20922789888000  == math::factorial( 16 ) );
  CHECK(        355687428096000  == math::factorial( 17 ) );
  CHECK(       6402373705728000  == math::factorial( 18 ) );
  CHECK(     121645100408832000  == math::factorial( 19 ) );
  CHECK(    2432902008176640000  == math::factorial( 20 ) );
  CHECK(   51090942171709440000. == math::factorial( 21 ) );
  CHECK( 1124000727777607680000. == math::factorial( 22 ) );
} // SCENARIO
