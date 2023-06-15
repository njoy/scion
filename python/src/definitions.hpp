#ifndef NJOY_SCION_PYTHON_DEFINITIONS
#define NJOY_SCION_PYTHON_DEFINITIONS

// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/operators.h>

// other includes
#include "scion/linearisation/ToleranceConvergence.hpp"
#include "scion/math/FunctionBase.hpp"

// namespace aliases
namespace python = pybind11;

/**
 *  @brief Add standard domain definitions
 *
 *  This adds the following standard functions:
 *    in_inside, is_contained
 *
 *  @param[in] component   the domain to which the definitions have to be added
 */
template < typename Component, typename PythonClass >
void addStandardDomainDefinitions( PythonClass& component ) {

  component
  .def(

    "is_inside",
    &Component::isInside,
    python::arg( "x" ),
    "Check whether or not a value is inside the domain (including boundaries)\n\n"
    "Arguments:\n"
    "    self   the domain\n"
    "    x      the value to be tested"
  )
  .def(

    "is_contained",
    &Component::isContained,
    python::arg( "x" ),
    "Check whether or not a value is inside the domain (excluding boundaries)\n\n"
    "Arguments:\n"
    "    self   the domain\n"
    "    x      the value to be tested"
  )
  .def(

    "__eq__",
    [] ( const Component& self, const Component& right )
       { return self == right; },
    python::is_operator()
  )
  .def(

    "__ne__",
    [] ( const Component& self, const Component& right )
       { return self != right; },
    python::is_operator()
  );
}

/**
 *  @brief Add standard function definitions
 *
 *  This adds the following standard functions:
 *    is_inside, is_contained, __call__, evaluate, domain
 *
 *  @param[in] component   the function to which the definitions have to be added
 */
template < typename Component, typename X, typename Y, typename PythonClass >
void addStandardFunctionDefinitions( PythonClass& component ) {

  using ToleranceConvergence = njoy::scion::linearisation::ToleranceConvergence< X, Y >;
  using DomainVariant = typename njoy::scion::math::FunctionBase< X, Y >::DomainVariant;

  // note: for is_same_domain to bind properly, all possible variant members
  //       must have a default constructor

  component
  .def_property_readonly(

    "domain",
    [] ( const Component& self ) -> decltype(auto)
       { return self.domain(); },
    "The domain"
  )
  .def(

    "is_inside",
    [] ( const Component& self, const X& x ) -> decltype(auto)
       { return self.isInside( x ); },
    python::arg( "x" ),
    "Check whether or not a value is inside the domain (including boundaries)\n\n"
    "Arguments:\n"
    "    self   the function\n"
    "    x      the value to be tested"
  )
  .def(

    "is_contained",
    [] ( const Component& self, const X& x ) -> decltype(auto)
       { return self.isContained( x ); },
    python::arg( "x" ),
    "Check whether or not a value is inside the domain (including boundaries)\n\n"
    "Arguments:\n"
    "    self   the function\n"
    "    x      the value to be tested"
  )
  .def(

    "__call__",
    [] ( const Component& self, const X& x ) -> decltype(auto)
       { return self( x ); },
    python::arg( "x" ),
    "Evaluate the function for a value of x\n\n"
    "Arguments:\n"
    "    self   the function\n"
    "    x      the value to be evaluated"
  )
  .def(

    "linearise",
    [] ( const Component& self, const ToleranceConvergence& convergence )
       { return self.linearise( convergence ); },
    python::arg( "convergence" ) = ToleranceConvergence(),
    "Linearise the function and return a LinearLinearTable\n\n"
    "Arguments:\n"
    "    self           the function\n"
    "    convergence    the linearisation convergence criterion (default 0.1 %)"
  )
  .def(

    "is_same_domain",
    [] ( const Component& self, const DomainVariant& domain )
       { return self.isSameDomain( domain ); },
    python::arg( "domain" ),
    "Check whether or not a domain is equal to the function's domain\n\n"
    "Arguments:\n"
    "    self     the function\n"
    "    domain   the domain to be tested"
  );
}

/**
 *  @brief Add standard series expansion definitions
 *
 *  This adds the following standard functions:
 *    +=, -= for scalars and Component
 *    +, - for scalars and Component
 *    *=, /= for scalars
 *    *, / for scalars
 *
 *  @param[in] component   the function to which the definitions have to be added
 */
template < typename Component, typename X, typename Y, typename PythonClass >
void addStandardOperatorDefinitions( PythonClass& component ) {

  component
  .def( -python::self )
  .def( python::self + Y() )
  .def( python::self - Y() )
  .def( python::self * Y() )
  .def( python::self / Y() )
  .def( python::self + python::self )
  .def( python::self - python::self )
  .def( python::self += Y() )
  .def( python::self -= Y() )
  .def( python::self *= Y() )
  .def( python::self /= Y() )
  .def( python::self += python::self )
  .def( python::self -= python::self )
  .def( Y() + python::self )
  .def( Y() - python::self )
  .def( Y() * python::self );
}

/**
 *  @brief Add standard series expansion definitions
 *
 *  This adds the following standard functions:
 *    coefficients, order, derivative, primitive, roots
 *    standard operators
 *
 *  @param[in] component   the series to which the definitions have to be added
 */
template < typename Component, typename X, typename Y, typename PythonClass >
void addStandardSeriesDefinitions( PythonClass& component ) {

  component
  .def_property_readonly(

    "coefficients",
    [] ( const Component& self ) -> decltype(auto)
       { return self.coefficients(); },
    "The Legendre coefficients"
  )
  .def_property_readonly(

    "order",
    [] ( const Component& self ) -> decltype(auto)
       { return self.order(); },
    "The Legendre order"
  )
  .def(

    "derivative",
    [] ( const Component& self ) -> decltype(auto)
       { return self.derivative(); },
    "Return the derivative of the series"
  )
  .def(

    "primitive",
    [] ( const Component& self, const X& left ) -> decltype(auto)
       { return self.primitive( left ); },
    python::arg( "left" ) = X( 0. ),
    "Return the primitive or antiderivative of the series\n\n"
    "Arguments:\n"
    "    self   the function\n"
    "    left   the left bound of the integral (default = 0)"
  )
  .def(

    "roots",
    [] ( const Component& self, const X& a ) -> decltype(auto)
       { return self.roots( a ); },
    python::arg( "a" ) = X( 0. ),
    "Calculate the real roots of the series so that f(x) = a\n\n"
    "This function calculates all roots on the real axis of the series.\n\n"
    "The roots of the series are the eigenvalues of the companion matrix whose\n"
    "elements are trivial functions of the coefficients of the series. The\n"
    "resulting roots are in the complex plane so the roots that are not on the\n"
    "real axis are filtered out.\n\n"
    "Arguments:\n"
    "    self   the function\n"
    "    a      the value of a (default is zero)"
  );

  // add standard function and operator definitions
  addStandardFunctionDefinitions< Component, X, Y >( component );
  addStandardOperatorDefinitions< Component, X, Y >( component );
}

/**
 *  @brief Add standard single interpolation zone table definitions
 *
 *  This adds the following standard functions:
 *    number_points, interpolation, x, y
 *
 *  @param[in] component   the domain to which the definitions have to be added
 */
template < typename Component, typename X, typename Y, typename PythonClass >
void addStandardSingleInterpolationTableDefinitions( PythonClass& component ) {

  component
  .def_property_readonly(

    "interpolation",
    [] ( const Component& self ) -> decltype(auto)
       { return self.interpolation(); },
    "The interpolation type"
  )
  .def_property_readonly(

    "x",
    [] ( const Component& self ) -> decltype(auto)
       { return self.x(); },
    "The x values of the table"
  )
  .def_property_readonly(

    "y",
    [] ( const Component& self ) -> decltype(auto)
       { return self.y(); },
    "The y values of the table"
  )
  .def_property_readonly(

    "number_points",
    [] ( const Component& self ) -> decltype(auto)
       { return self.numberPoints(); },
    "The y values of the table"
  );

  // add standard function definitions
  addStandardFunctionDefinitions< Component, X, Y >( component );
}

/**
 *  @brief Add standard split functor definitions
 *
 *  This adds the following standard functions:
 *    __call__, evaluate
 *
 *  @param[in] component   the split functor to which the definitions have to be added
 */
template < typename Component, typename X, typename PythonClass >
void addStandardSplitDefinitions( PythonClass& component ) {

  component
  .def(

    "__call__",
    [] ( const Component& self,
         const X& xLeft, const X& xRight,
         const X& yLeft, const X& yRight ) -> decltype(auto)
       { return self( xLeft, xRight, yLeft, yRight ); },
       python::arg( "xLeft" ), python::arg( "xRight" ),
       python::arg( "yLeft" ), python::arg( "yRight" ),
    "Split the panel\n\n"
    "Arguments:\n"
    "    self     the split functor\n"
    "    xLeft    the left value on the x interval\n"
    "    xRight   the right value on the x interval\n"
    "    yLeft    the left value on the y interval\n"
    "    yRight   the right value on the y interval"
  );
}

/**
 *  @brief Add standard convergence functor definitions
 *
 *  This adds the following standard functions:
 *    __call__, evaluate
 *
 *  @param[in] component   the convergence functor to which the definitions have to be added
 */
template < typename Component, typename X, typename Y, typename PythonClass >
void addStandardConvergenceDefinitions( PythonClass& component ) {

  component
  .def(

    "__call__",
    [] ( const Component& self,
         const Y& trial, const Y& reference,
         const X& xLeft, const X& xRight,
         const Y& yLeft, const Y& yRight ) -> decltype(auto)
       { return self( trial, reference, xLeft, xRight, yLeft, yRight ); },
    python::arg( "trial" ), python::arg( "reference" ),
    python::arg( "xLeft" ), python::arg( "xRight" ),
    python::arg( "yLeft" ), python::arg( "yRight" ),
    "Test the convergence of the linearisation\n\n"
    "Arguments:\n"
    "    self         the convergence functor\n"
    "    trial        the trial value to be tested\n"
    "    reference    the reference value to be tested against\n"
    "    xLeft        the left value on the x interval\n"
    "    xRight       the right value on the x interval\n"
    "    yLeft        the left value on the y interval\n"
    "    yRight       the right value on the y interval"
  );
}

#endif
