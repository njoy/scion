#ifndef NJOY_SCION_MATH_MATRIX
#define NJOY_SCION_MATH_MATRIX

// system includes

// other includes
#include <Eigen/Core>
#include <Eigen/Eigenvalues>

namespace njoy {
namespace scion {
namespace math {

  /* type aliases */
  template < typename T > using Matrix = Eigen::Matrix< T, Eigen::Dynamic, Eigen::Dynamic >;

} // math namespace
} // scion namespace
} // njoy namespace

#endif
