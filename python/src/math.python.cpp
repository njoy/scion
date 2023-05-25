// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes

// namespace aliases
namespace python = pybind11;

// declarations
namespace math {

  // utility functions
  void wrapComparisonFunctions( python::module& );
  void wrapNewton( python::module& );

  // evaluation schemes
  void wrapClenshaw( python::module& );
  void wrapHorner( python::module& );

  // special functions
  void wrapChebyshev( python::module& );
  void wrapLegendre( python::module& );

  // function interface
  void wrapIntervalDomain( python::module& );
  void wrapOpenDomain( python::module& );

  // functions
  void wrapLinearLinearTable( python::module& );
  void wrapHistogramTable( python::module& );
  void wrapLogLinearTable( python::module& );
  void wrapLinearLogTable( python::module& );
  void wrapLogLogTable( python::module& );
  void wrapInterpolationTable( python::module& );
  void wrapChebyshevSeries( python::module& );
  void wrapChebyshevApproximation( python::module& );
  void wrapLegendreSeries( python::module& );
  void wrapPolynomialSeries( python::module& );
}

void wrapMathModule( python::module& module ) {

  // create the submodule
  python::module submodule = module.def_submodule(

    "math",
    "Common math capabilities and components"
  );

  // wrap scion's math capabilities
  math::wrapComparisonFunctions( submodule );
  math::wrapNewton( submodule );
  math::wrapClenshaw( submodule );
  math::wrapHorner( submodule );
  math::wrapChebyshev( submodule );
  math::wrapLegendre( submodule );
  math::wrapIntervalDomain( submodule );
  math::wrapOpenDomain( submodule );
  math::wrapLinearLinearTable( submodule );
  math::wrapHistogramTable( submodule );
  math::wrapLogLinearTable( submodule );
  math::wrapLinearLogTable( submodule );
  math::wrapLogLogTable( submodule );
  math::wrapInterpolationTable( submodule );
  math::wrapChebyshevSeries( submodule );
  math::wrapChebyshevApproximation( submodule );
  math::wrapLegendreSeries( submodule );
  math::wrapPolynomialSeries( submodule );
}
