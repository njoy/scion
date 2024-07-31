#ifndef NJOY_SCION_MATH_INTERPOLATIONTABLEFUNCTION
#define NJOY_SCION_MATH_INTERPOLATIONTABLEFUNCTION

// system includes
#include <variant>
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "utility/IteratorView.hpp"
#include "scion/interpolation/InterpolationType.hpp"
#include "scion/math/TwoDimensionalFunctionBase.hpp"
#include "scion/math/HistogramTableFunction.hpp"
#include "scion/math/LinearLinearTableFunction.hpp"
#include "scion/math/LinearLogTableFunction.hpp"
#include "scion/math/LogLinearTableFunction.hpp"
#include "scion/math/LogLogTableFunction.hpp"
#include "scion/verification/ranges.hpp"

namespace njoy {
namespace scion {
namespace math {

  /**
   *  @class
   *  @brief Tabulated data with one or more interpolation types
   */
  template < typename X, typename F, typename Y, typename Z >
  class InterpolationTableFunction :
      public TwoDimensionalFunctionBase< InterpolationTableFunction< X, F, Y, Z >, X, Y, Z > {

    /* friend declarations */
    friend class TwoDimensionalFunctionBase< InterpolationTableFunction< X, F, Y, Z >, X, Y, Z >;

    /* type aliases */
    using Parent = TwoDimensionalFunctionBase< InterpolationTableFunction< X, F, Y, Z >, X, Y, Z >;
    using XIterator = typename std::vector< X >::const_iterator;
    using FIterator = typename std::vector< F >::const_iterator;
    using XContainer = njoy::utility::IteratorView< XIterator >;
    using FContainer = njoy::utility::IteratorView< FIterator >;
    using TableVariant = std::variant<
                             LinearLinearTableFunction< X, Y, Z, F, XContainer, FContainer >,
                             HistogramTableFunction< X, Y, Z, F, XContainer, FContainer >,
                             LinearLogTableFunction< X, Y, Z, F, XContainer, FContainer >,
                             LogLinearTableFunction< X, Y, Z, F, XContainer, FContainer >,
                             LogLogTableFunction< X, Y, Z, F, XContainer, FContainer > >;

    /* fields */
    std::vector< X > x_;
    std::vector< F > f_;
    std::vector< std::size_t > boundaries_;
    std::vector< interpolation::InterpolationType > interpolants_;
    std::vector< TableVariant > tables_;

    /* auxiliary function */
    #include "scion/math/InterpolationTableFunction/src/generateTables.hpp"
    #include "scion/math/InterpolationTableFunction/src/processBoundaries.hpp"

    /**
     *  @brief Return the interpolation tables
     */
    const std::vector< TableVariant >& tables() const noexcept {

      return this->tables_;
    }

    /* interface implementation functions */
    #include "scion/math/InterpolationTableFunction/src/evaluate.hpp"

  public:

    /* constructor */
    #include "scion/math/InterpolationTableFunction/src/ctor.hpp"

    /* methods */

    /**
     *  @brief Return the x values of the table
     */
    const std::vector< X >& x() const noexcept {

      return this->x_;
    }

    /**
     *  @brief Return the f(y) functions of the table
     */
    const std::vector< F >& f() const noexcept {

      return this->f_;
    }

    /**
     *  @brief Return the boundaries of the interpolation regions
     */
    const std::vector< std::size_t >& boundaries() const noexcept {

      return this->boundaries_;
    }

    /**
     *  @brief Return the interpolation types of the interpolation regions
     */
    const std::vector< interpolation::InterpolationType >& interpolants() const noexcept {

      return this->interpolants_;
    }

    /**
     *  @brief Return the number of points in the table
     */
    std::size_t numberPoints() const noexcept {

      return this->x().size();
    }

    /**
     *  @brief Return the number of interpolation regions in the table
     */
    std::size_t numberRegions() const noexcept {

      return this->boundaries().size();
    }

    using Parent::operator();
  };

} // math namespace
} // scion namespace
} // njoy namespace

#endif
