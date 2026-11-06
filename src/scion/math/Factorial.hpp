#ifndef NJOY_SCION_MATH_FACTORIAL
#define NJOY_SCION_MATH_FACTORIAL

// system includes
#include <array>

// other includes

namespace njoy {
namespace scion {
namespace math {

  /**
   *  @class
   *  @brief Calculate the factorial of a number
   */
  class Factorial {

    /* fields */

    static constexpr std::array< double, 23 > factorials = {

                           1.,
                           1.,
                           2.,
                           6.,
                          24.,
                         120.,
                         720.,
                        5040.,
                       40320.,
                      362880.,
                     3628800.,
                    39916800.,
                   479001600.,
                  6227020800.,
                 87178291200.,
               1307674368000.,
              20922789888000.,
             355687428096000.,
            6402373705728000.,
          121645100408832000.,
         2432902008176640000.,
        51090942171709440000.,
      1124000727777607680000.
    };

    /* auxiliary function */

  public:

    /* methods */

    /**
     *  @brief Calculate the factorial of a number
     *
     *  @param n   the value to be evaluated
     */
    double operator()( std::size_t n ) const {

      return factorials[n];
    }
  };

  // integration function
  static constexpr Factorial factorial;

} // math namespace
} // scion namespace
} // njoy namespace

#endif
