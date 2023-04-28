#ifndef NJOY_SCION_LINEARISATION_GRID
#define NJOY_SCION_LINEARISATION_GRID

// system includes

// other includes

namespace njoy {
namespace scion {
namespace linearisation {

  /**
   *  @brief Determine the minimum grid for linearisation
   *
   *  This template function returns the initial grid for linearisation which
   *  consists of the following unique set of values: boundaries of the domain,
   *  the real roots of the first and second derivative in the domain.
   *
   *  The FirstDerivative and SecondDerivative objects must have a roots()
   *  method that returns the real roots of the function.
   *
   *  @param first        the first derivative (must have a roots() function)
   *  @param second       the second derivative (must have a roots() function)
   *  @param lowerLimit   the lower limit of the function domain
   *  @param upperLimit   the upper limit of the function domain
   */
  template < typename X, typename FirstDerivative, typename SecondDerivative >
  std::vector< X > grid( FirstDerivative&& first, SecondDerivative&& second,
                         const X& lowerLimit, const X& upperLimit ) {

    std::vector< X > grid = { lowerLimit, upperLimit };

    // add roots of the first derivative
    std::vector< X > temp = first.roots();
    grid.insert( grid.end(), temp.begin(), temp.end() );

    // add roots of the second derivative
    temp = second.roots();
    grid.insert( grid.end(), temp.begin(), temp.end() );

    // sort the grid and remove duplicates
    std::sort( grid.begin(), grid.end() );
    grid.erase( std::unique( grid.begin(), grid.end() ), grid.end() );

    // remove everything outside of the domain
    grid.erase( std::lower_bound( grid.begin(), grid.end(), lowerLimit ), grid.begin() );
    grid.erase( std::next( std::lower_bound( grid.begin(), grid.end(), upperLimit ) ), grid.end() );

    //! @todo remove points that are too close to one another?

    return grid;
  }

  /**
   *  @brief Determine the minimum grid for linearisation
   *
   *  This template function returns the initial grid for linearisation which
   *  consists of the following unique set of values: boundaries of the domain,
   *  the real roots of the first and second derivative in the domain.
   *
   *  @param function     the function
   *  @param lowerLimit   the lower limit of the function domain
   *  @param upperLimit   the upper limit of the function domain
   */
  template < typename X, typename Functor >
  std::vector< X > grid( Functor&& function,
                         const X& lowerLimit, const X& upperLimit ) {

    const auto first = function.derivative();
    const auto second = first.derivative();
    return linearisation::grid( std::move( first ), std::move( second ),
                                lowerLimit, upperLimit );
  }

} // linearisation namespace
} // scion namespace
} // njoy namespace

#endif
