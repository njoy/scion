#ifndef NJOY_SCION_PYTHON_DEFINITIONS
#define NJOY_SCION_PYTHON_DEFINITIONS

// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// other includes

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
  );
}

/**
 *  @brief Add standard function definitions
 *
 *  This adds the following standard functions:
 *    in_inside, is_contained, __call__, evaluate, domain
 *
 *  @param[in] component   the domain to which the definitions have to be added
 */
template < typename Component, typename X, typename Y, typename PythonClass >
void addStandardFunctionDefinitions( PythonClass& component ) {

  component
  .def_property_readonly(

    "domain",
    [] ( const Component& self ) -> decltype(auto)
       { return self.domain(); },
    "The domain"
  )
  .def(

    "evaluate",
    &Component::evaluate,
    python::arg( "x" ),
    "Evaluate the function for a value of x\n\n"
    "Arguments:\n"
    "    self   the function\n"
    "    x      the value to be evaluated"
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
  );
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

    "evaluate",
    &Component::evaluate,
    python::arg( "xLeft" ), python::arg( "xRight" ),
    "Split the panel\n\n"
    "Arguments:\n"
    "    self     the split functor\n"
    "    xLeft    the left value on the x interval\n"
    "    xRight   the right value on the x interval"
  )
  .def(

    "__call__",
    [] ( const Component& self, const X& xLeft, const X& xRight ) -> decltype(auto)
       { return self( xLeft, xRight ); },
    python::arg( "xLeft" ), python::arg( "xRight" ),
    "Split the panel\n\n"
    "Arguments:\n"
    "    self     the split functor\n"
    "    xLeft    the left value on the x interval\n"
    "    xRight   the right value on the x interval"
  );
}

#endif
