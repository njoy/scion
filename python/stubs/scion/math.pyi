"""
Common math capabilities and components
"""
from __future__ import annotations
import scion.interpolation
import scion.linearisation
import typing
__all__ = ['AnalyticalIntegrator', 'ChebyshevApproximation', 'ChebyshevSeries', 'HistogramTable', 'InterpolationTable', 'IntervalDomain', 'LegendreSeries', 'LinearLinearTable', 'LinearLogTable', 'LogLinearTable', 'LogLogTable', 'OpenDomain', 'PolynomialSeries', 'chebyshev', 'clenshaw', 'clenshaw_chebyshev', 'clenshaw_legendre', 'horner', 'is_close', 'is_close_to_zero', 'legendre', 'newton']
class AnalyticalIntegrator:
    """
    Analytical integration of data over a number of successive integration intervals
    """
    def __call__(self, table: InterpolationTable) -> list[float]:
        ...
    @typing.overload
    def __init__(self, boundaries: list[float]) -> None:
        """
        Initialise the integrator
        
        Arguments:
            self         the integrator
            boundaries    the integration interval boundaries
        """
    @typing.overload
    def __init__(self, a: float, b: float) -> None:
        """
        Initialise the integrator
        
        Arguments:
            self   the integrator
            a      the lower limit of the integration interval
            b      the upper limit of the integration interval
        """
    @property
    def boundaries(self) -> list[float]:
        """
        The boundaries
        """
    @property
    def number_intervals(self) -> int:
        """
        The number of integration intervals
        """
class ChebyshevApproximation:
    """
    Approximation of a function f(x) in the [a,b] domain using a Chebyshev series
    
    Users should note that the underlying Chebyshev series is ALWAYS defined in
    [-1, 1] and that the approximated function is defined on [a,b] and that
    a domain transformation is required to go from one to the other. This
    transformation is performed inside this object.
    
    Chebyshev function approximation only works well within the defined
    domain. Outside of the domain, the approximated function can quickly diverge.
    Range checking by the user is advised.
    
    The derivative function of an approximated function is another approximated
    function. The derivative is equal to the derivative of the underlying
    Chebyshev series and is defined over the same domain as the original
    approximated function.
    
    The primitive of an approximated function is another approximated
    function. The primitive is equal to the primitive of the underlying
    Chebyshev series and is defined over the same domain as the original
    approximated function.
    
    The integral function is defined so that the integral function for x = left
    equals 0.
    """
    __hash__: typing.ClassVar[None] = None
    @typing.overload
    def __add__(self, arg0: float) -> ChebyshevApproximation:
        ...
    @typing.overload
    def __add__(self, arg0: ChebyshevApproximation) -> ChebyshevApproximation:
        ...
    def __call__(self, x: float) -> float:
        """
        Evaluate the function for a value of x
        
        Arguments:
            self   the function
            x      the value to be evaluated
        """
    def __eq__(self, arg0: ChebyshevApproximation) -> bool:
        ...
    @typing.overload
    def __iadd__(self, arg0: float) -> ChebyshevApproximation:
        ...
    @typing.overload
    def __iadd__(self, arg0: ChebyshevApproximation) -> ChebyshevApproximation:
        ...
    def __imul__(self, arg0: float) -> ChebyshevApproximation:
        ...
    @typing.overload
    def __init__(self, lower: float, upper: float, function: typing.Callable[[float], float], order: int) -> None:
        """
        Initialise the function
        
        Arguments:
            self        the function
            lower       the lower limit of the domain
            upper       the upper limit of the domain
            function    the function to be approximated
            order       the order of the approximation
        """
    @typing.overload
    def __init__(self, lower: float, upper: float, coefficients: list[float]) -> None:
        """
        Initialise the function
        
        Arguments:
            self            the function
            lower           the lower limit of the domain
            upper           the upper limit of the domain
            coefficients    the coefficients that approximate the function
        """
    @typing.overload
    def __isub__(self, arg0: float) -> ChebyshevApproximation:
        ...
    @typing.overload
    def __isub__(self, arg0: ChebyshevApproximation) -> ChebyshevApproximation:
        ...
    def __itruediv__(self, arg0: float) -> ChebyshevApproximation:
        ...
    def __mul__(self, arg0: float) -> ChebyshevApproximation:
        ...
    def __ne__(self, arg0: ChebyshevApproximation) -> bool:
        ...
    def __neg__(self) -> ChebyshevApproximation:
        ...
    def __radd__(self, arg0: float) -> ChebyshevApproximation:
        ...
    def __rmul__(self, arg0: float) -> ChebyshevApproximation:
        ...
    def __rsub__(self, arg0: float) -> ChebyshevApproximation:
        ...
    @typing.overload
    def __sub__(self, arg0: float) -> ChebyshevApproximation:
        ...
    @typing.overload
    def __sub__(self, arg0: ChebyshevApproximation) -> ChebyshevApproximation:
        ...
    def __truediv__(self, arg0: float) -> ChebyshevApproximation:
        ...
    def derivative(self) -> ChebyshevApproximation:
        """
        Return the derivative of the series
        """
    def is_contained(self, x: float) -> bool:
        """
        Check whether or not a value is inside the domain (including boundaries)
        
        Arguments:
            self   the function
            x      the value to be tested
        """
    def is_inside(self, x: float) -> bool:
        """
        Check whether or not a value is inside the domain (including boundaries)
        
        Arguments:
            self   the function
            x      the value to be tested
        """
    def is_same_domain(self, domain: IntervalDomain | OpenDomain) -> bool:
        """
        Check whether or not a domain is equal to the function's domain
        
        Arguments:
            self     the function
            domain   the domain to be tested
        """
    def linearise(self, convergence: scion.linearisation.ToleranceConvergence = ...) -> InterpolationTable:
        """
        Linearise the function and return a LinearLinearTable
        
        Arguments:
            self           the function
            convergence    the linearisation convergence criterion (default 0.1 %)
        """
    def primitive(self, left: float = 0.0) -> ChebyshevApproximation:
        """
        Return the primitive or antiderivative of the series
        
        Arguments:
            self   the function
            left   the left bound of the integral (default = 0)
        """
    def roots(self, a: float = 0.0) -> list[float]:
        """
        Calculate the real roots of the series so that f(x) = a
        
        This function calculates all roots on the real axis of the series.
        
        The roots of the series are the eigenvalues of the companion matrix whose
        elements are trivial functions of the coefficients of the series. The
        resulting roots are in the complex plane so the roots that are not on the
        real axis are filtered out.
        
        Arguments:
            self   the function
            a      the value of a (default is zero)
        """
    @property
    def coefficients(self) -> list[float]:
        """
        The coefficients of the series expansion
        """
    @property
    def domain(self) -> IntervalDomain | OpenDomain:
        """
        The domain
        """
    @property
    def order(self) -> int:
        """
        The order of the series expansion
        """
class ChebyshevSeries:
    """
    A Chebyshev series function y -> f(x) = sum c_i T_i(x) of order n
    
    This class represents a Chebyshev series function y -> f(x) =
    sum c_i T_i(x) defined over the domain [-1,1].
    
    The Clenshaw recursion scheme is used for the evaluation of the series
    using the following recursion relation for Chebyshev polynomials:
      T_(n+1) = 2 x T_n - T_(n-1)
    
    The derivative function of a Chebyshev series function is another
    Chebyshev series function. The coefficients of the new Chebyshev series
    are calculated using the derivative of a Chebyshev polynomial as a
    function of other Chebyshev polynomials:
      d/dx T_n = 2 n ( T_(n-1) + T_(n-3) + ... + T_1 ) if n is even
      d/dx T_n = 2 n ( T_(n-1) + T_(n-3) + ... + T_2 ) + n T_0 if n is odd
    This relation can be proven by mathematical induction.
    
    The primitive or antiderivative of a Chebyshev series function is another
    Chebyshev series function. The coefficients of the new Chebyshev series
    are calculated using the integral of a Chebyshev polynomial as a
    function of other Chebyshev polynomials:
      2 int T_n = T_(n + 1)/(n + 1) - T_(n - 1)/(n - 1)
    
    The integrated series is defined so that the integral function for x = left
    equals 0.
    
    The derivative  and primitive function is defined over the same domain as
    the original function.
    """
    __hash__: typing.ClassVar[None] = None
    @typing.overload
    def __add__(self, arg0: float) -> ChebyshevSeries:
        ...
    @typing.overload
    def __add__(self, arg0: ChebyshevSeries) -> ChebyshevSeries:
        ...
    def __call__(self, x: float) -> float:
        """
        Evaluate the function for a value of x
        
        Arguments:
            self   the function
            x      the value to be evaluated
        """
    def __eq__(self, arg0: ChebyshevSeries) -> bool:
        ...
    @typing.overload
    def __iadd__(self, arg0: float) -> ChebyshevSeries:
        ...
    @typing.overload
    def __iadd__(self, arg0: ChebyshevSeries) -> ChebyshevSeries:
        ...
    def __imul__(self, arg0: float) -> ChebyshevSeries:
        ...
    def __init__(self, coefficients: list[float]) -> None:
        """
        Initialise the function
        
        Arguments:
            self           the function
            coefficients   the coefficients of the Chebyshev series (from
                           lowest to highest order coefficient)
        """
    @typing.overload
    def __isub__(self, arg0: float) -> ChebyshevSeries:
        ...
    @typing.overload
    def __isub__(self, arg0: ChebyshevSeries) -> ChebyshevSeries:
        ...
    def __itruediv__(self, arg0: float) -> ChebyshevSeries:
        ...
    def __mul__(self, arg0: float) -> ChebyshevSeries:
        ...
    def __ne__(self, arg0: ChebyshevSeries) -> bool:
        ...
    def __neg__(self) -> ChebyshevSeries:
        ...
    def __radd__(self, arg0: float) -> ChebyshevSeries:
        ...
    def __rmul__(self, arg0: float) -> ChebyshevSeries:
        ...
    def __rsub__(self, arg0: float) -> ChebyshevSeries:
        ...
    @typing.overload
    def __sub__(self, arg0: float) -> ChebyshevSeries:
        ...
    @typing.overload
    def __sub__(self, arg0: ChebyshevSeries) -> ChebyshevSeries:
        ...
    def __truediv__(self, arg0: float) -> ChebyshevSeries:
        ...
    def derivative(self) -> ChebyshevSeries:
        """
        Return the derivative of the series
        """
    def is_contained(self, x: float) -> bool:
        """
        Check whether or not a value is inside the domain (including boundaries)
        
        Arguments:
            self   the function
            x      the value to be tested
        """
    def is_inside(self, x: float) -> bool:
        """
        Check whether or not a value is inside the domain (including boundaries)
        
        Arguments:
            self   the function
            x      the value to be tested
        """
    def is_same_domain(self, domain: IntervalDomain | OpenDomain) -> bool:
        """
        Check whether or not a domain is equal to the function's domain
        
        Arguments:
            self     the function
            domain   the domain to be tested
        """
    def linearise(self, convergence: scion.linearisation.ToleranceConvergence = ...) -> InterpolationTable:
        """
        Linearise the function and return a LinearLinearTable
        
        Arguments:
            self           the function
            convergence    the linearisation convergence criterion (default 0.1 %)
        """
    def primitive(self, left: float = 0.0) -> ChebyshevSeries:
        """
        Return the primitive or antiderivative of the series
        
        Arguments:
            self   the function
            left   the left bound of the integral (default = 0)
        """
    def roots(self, a: float = 0.0) -> list[float]:
        """
        Calculate the real roots of the series so that f(x) = a
        
        This function calculates all roots on the real axis of the series.
        
        The roots of the series are the eigenvalues of the companion matrix whose
        elements are trivial functions of the coefficients of the series. The
        resulting roots are in the complex plane so the roots that are not on the
        real axis are filtered out.
        
        Arguments:
            self   the function
            a      the value of a (default is zero)
        """
    @property
    def coefficients(self) -> list[float]:
        """
        The coefficients of the series expansion
        """
    @property
    def domain(self) -> IntervalDomain | OpenDomain:
        """
        The domain
        """
    @property
    def integral(self) -> float:
        """
        The integral (zeroth order moment) of the table over its domain
        """
    @property
    def mean(self) -> float:
        """
        The mean (first order raw moment) of the table over its domain
        """
    @property
    def order(self) -> int:
        """
        The order of the series expansion
        """
class HistogramTable:
    """
    Tabulated data with histogram interpolation (y is constant in x)
    """
    def __call__(self, x: float) -> float:
        """
        Evaluate the function for a value of x
        
        Arguments:
            self   the function
            x      the value to be evaluated
        """
    def __init__(self, x: list[float], y: list[float]) -> None:
        """
        Initialise the function
        
        Arguments:
            self   the function
            x      the x values of the tabulated data
            y      the y values of the tabulated data
        """
    def is_contained(self, x: float) -> bool:
        """
        Check whether or not a value is inside the domain (including boundaries)
        
        Arguments:
            self   the function
            x      the value to be tested
        """
    def is_inside(self, x: float) -> bool:
        """
        Check whether or not a value is inside the domain (including boundaries)
        
        Arguments:
            self   the function
            x      the value to be tested
        """
    def is_same_domain(self, domain: IntervalDomain | OpenDomain) -> bool:
        """
        Check whether or not a domain is equal to the function's domain
        
        Arguments:
            self     the function
            domain   the domain to be tested
        """
    def linearise(self, convergence: scion.linearisation.ToleranceConvergence = ...) -> tuple[list[float], list[float]]:
        """
        Linearise the function and return a LinearLinearTable
        
        Arguments:
            self           the function
            convergence    the linearisation convergence criterion (default 0.1 %)
        """
    @property
    def domain(self) -> IntervalDomain | OpenDomain:
        """
        The domain
        """
    @property
    def integral(self) -> float:
        """
        The integral (zeroth order moment) of the table over its domain
        """
    @property
    def interpolation(self) -> scion.interpolation.InterpolationType:
        """
        The interpolation type
        """
    @property
    def mean(self) -> float:
        """
        The mean (first order raw moment) of the table over its domain
        """
    @property
    def number_points(self) -> int:
        """
        The y values of the table
        """
    @property
    def x(self) -> list[float]:
        """
        The x values of the table
        """
    @property
    def y(self) -> list[float]:
        """
        The y values of the table
        """
class InterpolationTable:
    """
    Tabulated data with one or more interpolation types
    """
    __hash__: typing.ClassVar[None] = None
    @typing.overload
    def __add__(self, arg0: float) -> InterpolationTable:
        ...
    @typing.overload
    def __add__(self, arg0: InterpolationTable) -> InterpolationTable:
        ...
    def __call__(self, x: float) -> float:
        """
        Evaluate the function for a value of x
        
        Arguments:
            self   the function
            x      the value to be evaluated
        """
    def __eq__(self, arg0: InterpolationTable) -> bool:
        ...
    @typing.overload
    def __iadd__(self, arg0: float) -> InterpolationTable:
        ...
    @typing.overload
    def __iadd__(self, arg0: InterpolationTable) -> InterpolationTable:
        ...
    def __imul__(self, arg0: float) -> InterpolationTable:
        ...
    @typing.overload
    def __init__(self, x: list[float], y: list[float], boundaries: list[int], interpolants: list[scion.interpolation.InterpolationType]) -> None:
        """
        Initialise the function
        
        Arguments:
            self           the function
            x              the x values of the tabulated data
            y              the y values of the tabulated data
            boundaries     the boundaries of the interpolation regions
            interpolants   the interpolation types of the interpolation regions
        """
    @typing.overload
    def __init__(self, x: list[float], y: list[float], interpolant: scion.interpolation.InterpolationType = ...) -> None:
        """
        Initialise the function
        
        Arguments:
            self          the function
            x             the x values of the tabulated data
            y             the y values of the tabulated data
            interpolant   the interpolation type (default lin-lin)
        """
    @typing.overload
    def __isub__(self, arg0: float) -> InterpolationTable:
        ...
    @typing.overload
    def __isub__(self, arg0: InterpolationTable) -> InterpolationTable:
        ...
    def __itruediv__(self, arg0: float) -> InterpolationTable:
        ...
    def __mul__(self, arg0: float) -> InterpolationTable:
        ...
    def __ne__(self, arg0: InterpolationTable) -> bool:
        ...
    def __neg__(self) -> InterpolationTable:
        ...
    def __radd__(self, arg0: float) -> InterpolationTable:
        ...
    def __rmul__(self, arg0: float) -> InterpolationTable:
        ...
    def __rsub__(self, arg0: float) -> InterpolationTable:
        ...
    @typing.overload
    def __sub__(self, arg0: float) -> InterpolationTable:
        ...
    @typing.overload
    def __sub__(self, arg0: InterpolationTable) -> InterpolationTable:
        ...
    def __truediv__(self, arg0: float) -> InterpolationTable:
        ...
    def is_contained(self, x: float) -> bool:
        """
        Check whether or not a value is inside the domain (including boundaries)
        
        Arguments:
            self   the function
            x      the value to be tested
        """
    def is_inside(self, x: float) -> bool:
        """
        Check whether or not a value is inside the domain (including boundaries)
        
        Arguments:
            self   the function
            x      the value to be tested
        """
    def is_same_domain(self, domain: IntervalDomain | OpenDomain) -> bool:
        """
        Check whether or not a domain is equal to the function's domain
        
        Arguments:
            self     the function
            domain   the domain to be tested
        """
    def linearise(self, convergence: scion.linearisation.ToleranceConvergence = ...) -> InterpolationTable:
        """
        Linearise the function and return a LinearLinearTable
        
        Arguments:
            self           the function
            convergence    the linearisation convergence criterion (default 0.1 %)
        """
    @property
    def boundaries(self) -> list[int]:
        """
        The boundaries of the interpolation regions
        """
    @property
    def domain(self) -> IntervalDomain | OpenDomain:
        """
        The domain
        """
    @property
    def integral(self) -> float:
        """
        The integral (zeroth order moment) of the table over its domain
        """
    @property
    def interpolants(self) -> list[scion.interpolation.InterpolationType]:
        """
        The interpolation types of the interpolation regions
        """
    @property
    def is_linearised(self) -> bool:
        """
        Flag indicating whether or not the data is linearised
        """
    @property
    def mean(self) -> float:
        """
        The mean (first order raw moment) of the table over its domain
        """
    @property
    def number_points(self) -> int:
        """
        The number of points in the table
        """
    @property
    def number_regions(self) -> int:
        """
        The number of interpolation regions in the table
        """
    @property
    def x(self) -> list[float]:
        """
        The x values of the table
        """
    @property
    def y(self) -> list[float]:
        """
        The y values of the table
        """
class IntervalDomain:
    """
    A domain for a function y -> f(x) for x inside [a,b]
    """
    __hash__: typing.ClassVar[None] = None
    def __eq__(self, arg0: IntervalDomain) -> bool:
        ...
    def __init__(self, lower: float, upper: float) -> None:
        """
        Initialise the domain
        
        Arguments:
            self    the domain
            lower   the lower limit of the domain
            upper   the upper limit of the domain
        """
    def __ne__(self, arg0: IntervalDomain) -> bool:
        ...
    def is_contained(self, x: float) -> bool:
        """
        Check whether or not a value is inside the domain (excluding boundaries)
        
        Arguments:
            self   the domain
            x      the value to be tested
        """
    def is_inside(self, x: float) -> bool:
        """
        Check whether or not a value is inside the domain (including boundaries)
        
        Arguments:
            self   the domain
            x      the value to be tested
        """
    @property
    def lower_limit(self) -> float:
        """
        The lower limit of the domain
        """
    @property
    def upper_limit(self) -> float:
        """
        The upper limit of the domain
        """
class LegendreSeries:
    """
    A Legendre series function y -> f(x) = sum c_i P_i(x) of order n
    
    This class represents a Legendre series function y -> f(x) = sum c_i P_i(x)
    defined over the domain [-1,1].
    
    The Clenshaw recursion scheme is used for the evaluation of the series
    using the following recursion relation for Legendre polynomials:
      P_(n+1) = (2n+1)/(n+1) x P_n - n/(n+1) P_(n-1)
    
    The derivative function of a Legendre series function is another
    Legendre series function. The coefficients of the new Legendre series
    are calculated using the derivative of a Legendre polynomial as a
    function of other Legendre polynomials:
      d/dx P_(n + 1) = (2 * n + 1) * P_n + (2 * (n - 2) + 1) * P_(n - 2) + ...
    knowing that:
      d/dx P_0 = 0.0
      d/dx P_1 = P_0
    
    This formula can be derived using the following property of Legendre
    polynomials:
      ( 2 * n + 1 ) * P_n = d/dx P_(n + 1) - d/dx P_(n - 1)
    
    The primitive or antiderivative of a Legendre series function is another
    Legendre series function. The coefficients of the new Legendre series
    are calculated using the integral of a Legendre polynomial as a
    function of other Legendre polynomials:
      int P_n = (P_(n + 1) - P_(n - 1))/(2 * n + 1)
    
    The integrated series is defined so that the integral function for x = left
    equals 0.
    
    The derivative and primitive function is defined over the same domain as
    the original function.
    """
    __hash__: typing.ClassVar[None] = None
    @typing.overload
    def __add__(self, arg0: float) -> LegendreSeries:
        ...
    @typing.overload
    def __add__(self, arg0: LegendreSeries) -> LegendreSeries:
        ...
    def __call__(self, x: float) -> float:
        """
        Evaluate the function for a value of x
        
        Arguments:
            self   the function
            x      the value to be evaluated
        """
    def __eq__(self, arg0: LegendreSeries) -> bool:
        ...
    @typing.overload
    def __iadd__(self, arg0: float) -> LegendreSeries:
        ...
    @typing.overload
    def __iadd__(self, arg0: LegendreSeries) -> LegendreSeries:
        ...
    def __imul__(self, arg0: float) -> LegendreSeries:
        ...
    def __init__(self, coefficients: list[float]) -> None:
        """
        Initialise the function
        
        Arguments:
            self           the function
            coefficients   the coefficients of the Legendre series (from
                           lowest to highest order coefficient)
        """
    @typing.overload
    def __isub__(self, arg0: float) -> LegendreSeries:
        ...
    @typing.overload
    def __isub__(self, arg0: LegendreSeries) -> LegendreSeries:
        ...
    def __itruediv__(self, arg0: float) -> LegendreSeries:
        ...
    def __mul__(self, arg0: float) -> LegendreSeries:
        ...
    def __ne__(self, arg0: LegendreSeries) -> bool:
        ...
    def __neg__(self) -> LegendreSeries:
        ...
    def __radd__(self, arg0: float) -> LegendreSeries:
        ...
    def __rmul__(self, arg0: float) -> LegendreSeries:
        ...
    def __rsub__(self, arg0: float) -> LegendreSeries:
        ...
    @typing.overload
    def __sub__(self, arg0: float) -> LegendreSeries:
        ...
    @typing.overload
    def __sub__(self, arg0: LegendreSeries) -> LegendreSeries:
        ...
    def __truediv__(self, arg0: float) -> LegendreSeries:
        ...
    def derivative(self) -> LegendreSeries:
        """
        Return the derivative of the series
        """
    def is_contained(self, x: float) -> bool:
        """
        Check whether or not a value is inside the domain (including boundaries)
        
        Arguments:
            self   the function
            x      the value to be tested
        """
    def is_inside(self, x: float) -> bool:
        """
        Check whether or not a value is inside the domain (including boundaries)
        
        Arguments:
            self   the function
            x      the value to be tested
        """
    def is_same_domain(self, domain: IntervalDomain | OpenDomain) -> bool:
        """
        Check whether or not a domain is equal to the function's domain
        
        Arguments:
            self     the function
            domain   the domain to be tested
        """
    def linearise(self, convergence: scion.linearisation.ToleranceConvergence = ...) -> InterpolationTable:
        """
        Linearise the function and return a LinearLinearTable
        
        Arguments:
            self           the function
            convergence    the linearisation convergence criterion (default 0.1 %)
        """
    def primitive(self, left: float = 0.0) -> LegendreSeries:
        """
        Return the primitive or antiderivative of the series
        
        Arguments:
            self   the function
            left   the left bound of the integral (default = 0)
        """
    def roots(self, a: float = 0.0) -> list[float]:
        """
        Calculate the real roots of the series so that f(x) = a
        
        This function calculates all roots on the real axis of the series.
        
        The roots of the series are the eigenvalues of the companion matrix whose
        elements are trivial functions of the coefficients of the series. The
        resulting roots are in the complex plane so the roots that are not on the
        real axis are filtered out.
        
        Arguments:
            self   the function
            a      the value of a (default is zero)
        """
    @property
    def coefficients(self) -> list[float]:
        """
        The coefficients of the series expansion
        """
    @property
    def domain(self) -> IntervalDomain | OpenDomain:
        """
        The domain
        """
    @property
    def integral(self) -> float:
        """
        The integral (zeroth order moment) of the table over its domain
        """
    @property
    def mean(self) -> float:
        """
        The mean (first order raw moment) of the table over its domain
        """
    @property
    def order(self) -> int:
        """
        The order of the series expansion
        """
class LinearLinearTable:
    """
    Tabulated data with linear-linear interpolation (y is linear in x)
    """
    def __call__(self, x: float) -> float:
        """
        Evaluate the function for a value of x
        
        Arguments:
            self   the function
            x      the value to be evaluated
        """
    def __init__(self, x: list[float], y: list[float]) -> None:
        """
        Initialise the function
        
        Arguments:
            self   the function
            x      the x values of the tabulated data
            y      the y values of the tabulated data
        """
    def is_contained(self, x: float) -> bool:
        """
        Check whether or not a value is inside the domain (including boundaries)
        
        Arguments:
            self   the function
            x      the value to be tested
        """
    def is_inside(self, x: float) -> bool:
        """
        Check whether or not a value is inside the domain (including boundaries)
        
        Arguments:
            self   the function
            x      the value to be tested
        """
    def is_same_domain(self, domain: IntervalDomain | OpenDomain) -> bool:
        """
        Check whether or not a domain is equal to the function's domain
        
        Arguments:
            self     the function
            domain   the domain to be tested
        """
    def linearise(self, convergence: scion.linearisation.ToleranceConvergence = ...) -> tuple[list[float], list[float]]:
        """
        Linearise the function and return a LinearLinearTable
        
        Arguments:
            self           the function
            convergence    the linearisation convergence criterion (default 0.1 %)
        """
    @property
    def domain(self) -> IntervalDomain | OpenDomain:
        """
        The domain
        """
    @property
    def integral(self) -> float:
        """
        The integral (zeroth order moment) of the table over its domain
        """
    @property
    def interpolation(self) -> scion.interpolation.InterpolationType:
        """
        The interpolation type
        """
    @property
    def mean(self) -> float:
        """
        The mean (first order raw moment) of the table over its domain
        """
    @property
    def number_points(self) -> int:
        """
        The y values of the table
        """
    @property
    def x(self) -> list[float]:
        """
        The x values of the table
        """
    @property
    def y(self) -> list[float]:
        """
        The y values of the table
        """
class LinearLogTable:
    """
    Tabulated data with log-log interpolation (y is linear in ln(x))
    """
    def __call__(self, x: float) -> float:
        """
        Evaluate the function for a value of x
        
        Arguments:
            self   the function
            x      the value to be evaluated
        """
    def __init__(self, x: list[float], y: list[float]) -> None:
        """
        Initialise the function
        
        Arguments:
            self   the function
            x      the x values of the tabulated data
            y      the y values of the tabulated data
        """
    def is_contained(self, x: float) -> bool:
        """
        Check whether or not a value is inside the domain (including boundaries)
        
        Arguments:
            self   the function
            x      the value to be tested
        """
    def is_inside(self, x: float) -> bool:
        """
        Check whether or not a value is inside the domain (including boundaries)
        
        Arguments:
            self   the function
            x      the value to be tested
        """
    def is_same_domain(self, domain: IntervalDomain | OpenDomain) -> bool:
        """
        Check whether or not a domain is equal to the function's domain
        
        Arguments:
            self     the function
            domain   the domain to be tested
        """
    def linearise(self, convergence: scion.linearisation.ToleranceConvergence = ...) -> tuple[list[float], list[float]]:
        """
        Linearise the function and return a LinearLinearTable
        
        Arguments:
            self           the function
            convergence    the linearisation convergence criterion (default 0.1 %)
        """
    @property
    def domain(self) -> IntervalDomain | OpenDomain:
        """
        The domain
        """
    @property
    def integral(self) -> float:
        """
        The integral (zeroth order moment) of the table over its domain
        """
    @property
    def interpolation(self) -> scion.interpolation.InterpolationType:
        """
        The interpolation type
        """
    @property
    def mean(self) -> float:
        """
        The mean (first order raw moment) of the table over its domain
        """
    @property
    def number_points(self) -> int:
        """
        The y values of the table
        """
    @property
    def x(self) -> list[float]:
        """
        The x values of the table
        """
    @property
    def y(self) -> list[float]:
        """
        The y values of the table
        """
class LogLinearTable:
    """
    Tabulated data with log-log interpolation (ln(y) is linear in x)
    """
    def __call__(self, x: float) -> float:
        """
        Evaluate the function for a value of x
        
        Arguments:
            self   the function
            x      the value to be evaluated
        """
    def __init__(self, x: list[float], y: list[float]) -> None:
        """
        Initialise the function
        
        Arguments:
            self   the function
            x      the x values of the tabulated data
            y      the y values of the tabulated data
        """
    def is_contained(self, x: float) -> bool:
        """
        Check whether or not a value is inside the domain (including boundaries)
        
        Arguments:
            self   the function
            x      the value to be tested
        """
    def is_inside(self, x: float) -> bool:
        """
        Check whether or not a value is inside the domain (including boundaries)
        
        Arguments:
            self   the function
            x      the value to be tested
        """
    def is_same_domain(self, domain: IntervalDomain | OpenDomain) -> bool:
        """
        Check whether or not a domain is equal to the function's domain
        
        Arguments:
            self     the function
            domain   the domain to be tested
        """
    def linearise(self, convergence: scion.linearisation.ToleranceConvergence = ...) -> tuple[list[float], list[float]]:
        """
        Linearise the function and return a LinearLinearTable
        
        Arguments:
            self           the function
            convergence    the linearisation convergence criterion (default 0.1 %)
        """
    @property
    def domain(self) -> IntervalDomain | OpenDomain:
        """
        The domain
        """
    @property
    def integral(self) -> float:
        """
        The integral (zeroth order moment) of the table over its domain
        """
    @property
    def interpolation(self) -> scion.interpolation.InterpolationType:
        """
        The interpolation type
        """
    @property
    def mean(self) -> float:
        """
        The mean (first order raw moment) of the table over its domain
        """
    @property
    def number_points(self) -> int:
        """
        The y values of the table
        """
    @property
    def x(self) -> list[float]:
        """
        The x values of the table
        """
    @property
    def y(self) -> list[float]:
        """
        The y values of the table
        """
class LogLogTable:
    """
    Tabulated data with log-log interpolation (ln(y) is linear in ln(x))
    """
    def __call__(self, x: float) -> float:
        """
        Evaluate the function for a value of x
        
        Arguments:
            self   the function
            x      the value to be evaluated
        """
    def __init__(self, x: list[float], y: list[float]) -> None:
        """
        Initialise the function
        
        Arguments:
            self   the function
            x      the x values of the tabulated data
            y      the y values of the tabulated data
        """
    def is_contained(self, x: float) -> bool:
        """
        Check whether or not a value is inside the domain (including boundaries)
        
        Arguments:
            self   the function
            x      the value to be tested
        """
    def is_inside(self, x: float) -> bool:
        """
        Check whether or not a value is inside the domain (including boundaries)
        
        Arguments:
            self   the function
            x      the value to be tested
        """
    def is_same_domain(self, domain: IntervalDomain | OpenDomain) -> bool:
        """
        Check whether or not a domain is equal to the function's domain
        
        Arguments:
            self     the function
            domain   the domain to be tested
        """
    def linearise(self, convergence: scion.linearisation.ToleranceConvergence = ...) -> tuple[list[float], list[float]]:
        """
        Linearise the function and return a LinearLinearTable
        
        Arguments:
            self           the function
            convergence    the linearisation convergence criterion (default 0.1 %)
        """
    @property
    def domain(self) -> IntervalDomain | OpenDomain:
        """
        The domain
        """
    @property
    def integral(self) -> float:
        """
        The integral (zeroth order moment) of the table over its domain
        """
    @property
    def interpolation(self) -> scion.interpolation.InterpolationType:
        """
        The interpolation type
        """
    @property
    def mean(self) -> float:
        """
        The mean (first order raw moment) of the table over its domain
        """
    @property
    def number_points(self) -> int:
        """
        The y values of the table
        """
    @property
    def x(self) -> list[float]:
        """
        The x values of the table
        """
    @property
    def y(self) -> list[float]:
        """
        The y values of the table
        """
class OpenDomain:
    """
    A domain for a function y -> f(x) including any value of x
    """
    __hash__: typing.ClassVar[None] = None
    def __eq__(self, arg0: OpenDomain) -> bool:
        ...
    def __init__(self) -> None:
        """
        Initialise the domain
        """
    def __ne__(self, arg0: OpenDomain) -> bool:
        ...
    def is_contained(self, x: float) -> bool:
        """
        Check whether or not a value is inside the domain (excluding boundaries)
        
        Arguments:
            self   the domain
            x      the value to be tested
        """
    def is_inside(self, x: float) -> bool:
        """
        Check whether or not a value is inside the domain (including boundaries)
        
        Arguments:
            self   the domain
            x      the value to be tested
        """
class PolynomialSeries:
    """
    A polynomial function y -> f(x) = sum c_i x^i of order n
    
    This class represents a polynomial function y -> f(x) = sum c_i x^i of
    order n defined over a domain. Currently, the domain can either be the
    open domain where every value of x is allowed or the interval domain that
    restricts x to an interval [a,b].
    
    The horner scheme is used for the evaluation of the series.
    
    The first order derivative of a polynomial series is another polynomial
    series: y -> d/dx f(x) = sum i c_i x^(i-1) for i = 1 to n
    
    The primitive or antiderivative of a polynomial series is another polynomial
    series: y -> int[left,x] f(x) dx = c_0 + sum c_i/(i+1) x^(i+1)
    The integrated series is defined so that the integral function for x = left
    equals 0.
    
    The derivative and primitive function is defined over the same domain as
    the original series.
    """
    __hash__: typing.ClassVar[None] = None
    @typing.overload
    def __add__(self, arg0: float) -> PolynomialSeries:
        ...
    @typing.overload
    def __add__(self, arg0: PolynomialSeries) -> PolynomialSeries:
        ...
    def __call__(self, x: float) -> float:
        """
        Evaluate the function for a value of x
        
        Arguments:
            self   the function
            x      the value to be evaluated
        """
    def __eq__(self, arg0: PolynomialSeries) -> bool:
        ...
    @typing.overload
    def __iadd__(self, arg0: float) -> PolynomialSeries:
        ...
    @typing.overload
    def __iadd__(self, arg0: PolynomialSeries) -> PolynomialSeries:
        ...
    def __imul__(self, arg0: float) -> PolynomialSeries:
        ...
    @typing.overload
    def __init__(self, coefficients: list[float]) -> None:
        """
        Initialise the function with an open domain
        
        Arguments:
            self           the function
            coefficients   the coefficients of the polynomial series (from
                           lowest to highest order coefficient)
        """
    @typing.overload
    def __init__(self, lower: float, upper: float, coefficients: list[float]) -> None:
        """
        Initialise the function with an open domain
        
        Arguments:
            self           the function
            lower          the lower limit of the domain
            upper          the upper limit of the domain
            coefficients   the coefficients of the polynomial series (from
                           lowest to highest order coefficient)
        """
    @typing.overload
    def __isub__(self, arg0: float) -> PolynomialSeries:
        ...
    @typing.overload
    def __isub__(self, arg0: PolynomialSeries) -> PolynomialSeries:
        ...
    def __itruediv__(self, arg0: float) -> PolynomialSeries:
        ...
    def __mul__(self, arg0: float) -> PolynomialSeries:
        ...
    def __ne__(self, arg0: PolynomialSeries) -> bool:
        ...
    def __neg__(self) -> PolynomialSeries:
        ...
    def __radd__(self, arg0: float) -> PolynomialSeries:
        ...
    def __rmul__(self, arg0: float) -> PolynomialSeries:
        ...
    def __rsub__(self, arg0: float) -> PolynomialSeries:
        ...
    @typing.overload
    def __sub__(self, arg0: float) -> PolynomialSeries:
        ...
    @typing.overload
    def __sub__(self, arg0: PolynomialSeries) -> PolynomialSeries:
        ...
    def __truediv__(self, arg0: float) -> PolynomialSeries:
        ...
    def derivative(self) -> PolynomialSeries:
        """
        Return the derivative of the series
        """
    def is_contained(self, x: float) -> bool:
        """
        Check whether or not a value is inside the domain (including boundaries)
        
        Arguments:
            self   the function
            x      the value to be tested
        """
    def is_inside(self, x: float) -> bool:
        """
        Check whether or not a value is inside the domain (including boundaries)
        
        Arguments:
            self   the function
            x      the value to be tested
        """
    def is_same_domain(self, domain: IntervalDomain | OpenDomain) -> bool:
        """
        Check whether or not a domain is equal to the function's domain
        
        Arguments:
            self     the function
            domain   the domain to be tested
        """
    def linearise(self, convergence: scion.linearisation.ToleranceConvergence = ...) -> InterpolationTable:
        """
        Linearise the function and return a LinearLinearTable
        
        Arguments:
            self           the function
            convergence    the linearisation convergence criterion (default 0.1 %)
        """
    def primitive(self, left: float = 0.0) -> PolynomialSeries:
        """
        Return the primitive or antiderivative of the series
        
        Arguments:
            self   the function
            left   the left bound of the integral (default = 0)
        """
    def roots(self, a: float = 0.0) -> list[float]:
        """
        Calculate the real roots of the series so that f(x) = a
        
        This function calculates all roots on the real axis of the series.
        
        The roots of the series are the eigenvalues of the companion matrix whose
        elements are trivial functions of the coefficients of the series. The
        resulting roots are in the complex plane so the roots that are not on the
        real axis are filtered out.
        
        Arguments:
            self   the function
            a      the value of a (default is zero)
        """
    @property
    def coefficients(self) -> list[float]:
        """
        The coefficients of the series expansion
        """
    @property
    def domain(self) -> IntervalDomain | OpenDomain:
        """
        The domain
        """
    @property
    def integral(self) -> float:
        """
        The integral (zeroth order moment) of the table over its domain
        """
    @property
    def mean(self) -> float:
        """
        The mean (first order raw moment) of the table over its domain
        """
    @property
    def order(self) -> int:
        """
        The order of the series expansion
        """
def chebyshev(order: int, x: float) -> float:
    """
    Evaluate a Chebyshev polynomial of order n
    
    Arguments:
        order    the degree of the Chebyshev polynomial
        x        the value at which the polynomial must be evaluated
    """
def clenshaw(coefficients: list[float], a: typing.Callable[[int, float], float], b: typing.Callable[[int, float], float], f0: float, f1: float, x: float) -> float:
    """
    Clenshaw recursion scheme using a range
    
    The Clenshaw recursion scheme is an elegant and efficient way to
    evaluate a sum of coefficients times functions that obey a recursion
    formula (such as Legendre polynomials).
    
    Consider a function defined as follows:
    
      y = c_n * F_n(x) + c_(n - 1) * F_(n - 1)(x) + ... + c_0 * F_0(x)
    
    with F_(k + 1)(x) = a(k, x) * F_k(x) + b(k, x) * F_(k - 1)(x)
    
    We now define the values y_k:
    
      y_(n + 1) = y_(n + 2) = 0.0
      y_k = a(k, x) * y_(k+1) + b(k + 1, x) * y_(k + 2) + c_k  for k = n .. 1
    
    Once we know y_2 and y_1, it can be shown that the value of y will be equal to:
    
      y = b(1, x) * F_0(x) * y_2 + F_1(x) * y_1 + c_0 * F_0(x)
    
    Source: Numerical recipes - Third edition, p222-223
    
    The main reason for using the Clenshaw recursion scheme is computational
    efficiency.
    
    Arguments:
        coefficients   a range of coefficient values (from lowest to
                       highest order coefficient)
        a              the function a(k, x)
        b              the function b(k, x)
        f0             the value of F_0(x)
        f1             the value of F_1(x)
        x              the value of X
    """
def clenshaw_chebyshev(coefficients: list[float], x: float) -> float:
    """
    Clenshaw evaluation of a Chebyshev series using a range
    
    Arguments:
        coefficients   a range of coefficient values (from lowest to
                       highest order coefficient)
        x              the value of X
    """
def clenshaw_legendre(coefficients: list[float], x: float) -> float:
    """
    Clenshaw evaluation of a Legendre series using a range
    
    Arguments:
        coefficients   a range of coefficient values (from lowest to
                       highest order coefficient)
        x              the value of X
    """
def horner(coefficients: list[float], x: float) -> float:
    """
    Horner evaluation of a polynomial function for different x and y types using a range
    
    A polynomial is defined as a sequence of coefficients c_i so that the
    polynomial of order n is given by:
    
      y = c_n * x^n + c_(n - 1) * x^(n - 1) + c_(n - 2) * x^(n - 2) + ...
    
    With the Horner scheme, a polynomial is evaluated as follows:
    
      y = c_n * (x + c_(n-1) * (x + c_(n - 2) * (x + ...
    
    The main reason for using the Horner scheme is computational efficiency.
    
    Source: Numerical recipes - Third edition, p201-202
    
    Arguments:
        coefficients   a list of coefficient values (from lowest to highest
                       order coefficient)
        x              the value at which the polynomial must be evaluated
    """
def is_close(a: float, b: float, epsilon: float = 2.220446049250313e-14, threshold: float = 2.220446049250313e-14) -> bool:
    """
    Compare two floating point numbers
    
    Arguments:
        a           the first floating point number to compare
        b           the second floating point number to compare
        epsilon     the relative comparison tolerance
        threshold   the absolute comparison tolerance
    """
def is_close_to_zero(a: float, threshold: float = 2.220446049250313e-14) -> bool:
    """
    Compare a floating point number to zero
    
    Arguments:
        a           the floating point number to compare to zero
        threshold   the absolute comparison tolerance
    """
def legendre(order: int, x: float) -> float:
    """
    Evaluate a Legendre polynomial of order n
    
    Arguments:
        order    the order of the Legendre polynomial
        x        the value at which the polynomial must be evaluated
    """
def newton(estimate: float, functor: typing.Callable[[float], float], derivative: typing.Callable[[float], float], iterations: int = 5) -> float:
    """
    Apply the Newton-Raphson method for root estimation
    
    The Newton-Raphson method is used to calculate the root of a function f(x)
    provided that an estinate of the root is given. The method works by
    iteratively calculating new estimates to the root until it converges. The
    estimate of the root in iteration n+1 is given as:
      root(n+1) = root(n) - f(root(n)) / df/dx(root(n))
    
    By default, this method will perform at the leat the number of requested
    iterations (by default 5 iterations) if the root does not converge (as
    determined by the isClose function).
    
    Caveat: this method can break down when df/dx(root(n)) is close to zero.
    
    Arguments:
        estimate      the estimate of the root
        functor       the function f(x)
        derivative    the derivative of the function f(x)
        iterations    the number of iterations if the root does not converge
                      (by default 5 iterations)
    """
