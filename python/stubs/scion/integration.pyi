"""
Common integration capabilities and components
"""
from __future__ import annotations
import typing
__all__ = ['GaussLegendre10', 'GaussLegendre16', 'GaussLegendre2', 'GaussLegendre32', 'GaussLegendre4', 'GaussLegendre6', 'GaussLegendre64', 'GaussLegendre7', 'GaussLegendre8', 'GaussLobatto10', 'GaussLobatto16', 'GaussLobatto2', 'GaussLobatto32', 'GaussLobatto4', 'GaussLobatto6', 'GaussLobatto64', 'GaussLobatto8', 'histogram', 'linlin', 'linlog', 'loglin', 'loglog']
class GaussLegendre10:
    """
    Gauss-Legendre 10-point quadrature rule
    """
    @typing.overload
    def __call__(self, functor: typing.Callable[[float], float]) -> float:
        """
        Calculate the integral over the interval [-1, 1]
        
        Arguments:
            self       the integrator object
            functor    the function to integrate
        """
    @typing.overload
    def __call__(self, functor: typing.Callable[[float], float], a: float, b: float) -> float:
        """
        Calculate the integral over the interval [a,b]
        
        Arguments:
            self       the integrator object
            functor    the function to integrate
            a          the lower bound of the integration interval
            b          the upper bound of the integration interval
        """
    def __init__(self) -> None:
        """
        Initialise the quadrature rule
        """
class GaussLegendre16:
    """
    Gauss-Legendre 16-point quadrature rule
    """
    @typing.overload
    def __call__(self, functor: typing.Callable[[float], float]) -> float:
        """
        Calculate the integral over the interval [-1, 1]
        
        Arguments:
            self       the integrator object
            functor    the function to integrate
        """
    @typing.overload
    def __call__(self, functor: typing.Callable[[float], float], a: float, b: float) -> float:
        """
        Calculate the integral over the interval [a,b]
        
        Arguments:
            self       the integrator object
            functor    the function to integrate
            a          the lower bound of the integration interval
            b          the upper bound of the integration interval
        """
    def __init__(self) -> None:
        """
        Initialise the quadrature rule
        """
class GaussLegendre2:
    """
    Gauss-Legendre 2-point quadrature rule
    """
    @typing.overload
    def __call__(self, functor: typing.Callable[[float], float]) -> float:
        """
        Calculate the integral over the interval [-1, 1]
        
        Arguments:
            self       the integrator object
            functor    the function to integrate
        """
    @typing.overload
    def __call__(self, functor: typing.Callable[[float], float], a: float, b: float) -> float:
        """
        Calculate the integral over the interval [a,b]
        
        Arguments:
            self       the integrator object
            functor    the function to integrate
            a          the lower bound of the integration interval
            b          the upper bound of the integration interval
        """
    def __init__(self) -> None:
        """
        Initialise the quadrature rule
        """
class GaussLegendre32:
    """
    Gauss-Legendre 32-point quadrature rule
    """
    @typing.overload
    def __call__(self, functor: typing.Callable[[float], float]) -> float:
        """
        Calculate the integral over the interval [-1, 1]
        
        Arguments:
            self       the integrator object
            functor    the function to integrate
        """
    @typing.overload
    def __call__(self, functor: typing.Callable[[float], float], a: float, b: float) -> float:
        """
        Calculate the integral over the interval [a,b]
        
        Arguments:
            self       the integrator object
            functor    the function to integrate
            a          the lower bound of the integration interval
            b          the upper bound of the integration interval
        """
    def __init__(self) -> None:
        """
        Initialise the quadrature rule
        """
class GaussLegendre4:
    """
    Gauss-Legendre 4-point quadrature rule
    """
    @typing.overload
    def __call__(self, functor: typing.Callable[[float], float]) -> float:
        """
        Calculate the integral over the interval [-1, 1]
        
        Arguments:
            self       the integrator object
            functor    the function to integrate
        """
    @typing.overload
    def __call__(self, functor: typing.Callable[[float], float], a: float, b: float) -> float:
        """
        Calculate the integral over the interval [a,b]
        
        Arguments:
            self       the integrator object
            functor    the function to integrate
            a          the lower bound of the integration interval
            b          the upper bound of the integration interval
        """
    def __init__(self) -> None:
        """
        Initialise the quadrature rule
        """
class GaussLegendre6:
    """
    Gauss-Legendre 6-point quadrature rule
    """
    @typing.overload
    def __call__(self, functor: typing.Callable[[float], float]) -> float:
        """
        Calculate the integral over the interval [-1, 1]
        
        Arguments:
            self       the integrator object
            functor    the function to integrate
        """
    @typing.overload
    def __call__(self, functor: typing.Callable[[float], float], a: float, b: float) -> float:
        """
        Calculate the integral over the interval [a,b]
        
        Arguments:
            self       the integrator object
            functor    the function to integrate
            a          the lower bound of the integration interval
            b          the upper bound of the integration interval
        """
    def __init__(self) -> None:
        """
        Initialise the quadrature rule
        """
class GaussLegendre64:
    """
    Gauss-Legendre 64-point quadrature rule
    """
    @typing.overload
    def __call__(self, functor: typing.Callable[[float], float]) -> float:
        """
        Calculate the integral over the interval [-1, 1]
        
        Arguments:
            self       the integrator object
            functor    the function to integrate
        """
    @typing.overload
    def __call__(self, functor: typing.Callable[[float], float], a: float, b: float) -> float:
        """
        Calculate the integral over the interval [a,b]
        
        Arguments:
            self       the integrator object
            functor    the function to integrate
            a          the lower bound of the integration interval
            b          the upper bound of the integration interval
        """
    def __init__(self) -> None:
        """
        Initialise the quadrature rule
        """
class GaussLegendre7:
    """
    Gauss-Legendre 7-point quadrature rule
    """
    @typing.overload
    def __call__(self, functor: typing.Callable[[float], float]) -> float:
        """
        Calculate the integral over the interval [-1, 1]
        
        Arguments:
            self       the integrator object
            functor    the function to integrate
        """
    @typing.overload
    def __call__(self, functor: typing.Callable[[float], float], a: float, b: float) -> float:
        """
        Calculate the integral over the interval [a,b]
        
        Arguments:
            self       the integrator object
            functor    the function to integrate
            a          the lower bound of the integration interval
            b          the upper bound of the integration interval
        """
    def __init__(self) -> None:
        """
        Initialise the quadrature rule
        """
class GaussLegendre8:
    """
    Gauss-Legendre 8-point quadrature rule
    """
    @typing.overload
    def __call__(self, functor: typing.Callable[[float], float]) -> float:
        """
        Calculate the integral over the interval [-1, 1]
        
        Arguments:
            self       the integrator object
            functor    the function to integrate
        """
    @typing.overload
    def __call__(self, functor: typing.Callable[[float], float], a: float, b: float) -> float:
        """
        Calculate the integral over the interval [a,b]
        
        Arguments:
            self       the integrator object
            functor    the function to integrate
            a          the lower bound of the integration interval
            b          the upper bound of the integration interval
        """
    def __init__(self) -> None:
        """
        Initialise the quadrature rule
        """
class GaussLobatto10:
    """
    Gauss-Lobatto 10-point quadrature rule
    """
    @typing.overload
    def __call__(self, functor: typing.Callable[[float], float]) -> float:
        """
        Calculate the integral over the interval [-1, 1]
        
        Arguments:
            self       the integrator object
            functor    the function to integrate
        """
    @typing.overload
    def __call__(self, functor: typing.Callable[[float], float], a: float, b: float) -> float:
        """
        Calculate the integral over the interval [a,b]
        
        Arguments:
            self       the integrator object
            functor    the function to integrate
            a          the lower bound of the integration interval
            b          the upper bound of the integration interval
        """
    def __init__(self) -> None:
        """
        Initialise the quadrature rule
        """
class GaussLobatto16:
    """
    Gauss-Lobatto 16-point quadrature rule
    """
    @typing.overload
    def __call__(self, functor: typing.Callable[[float], float]) -> float:
        """
        Calculate the integral over the interval [-1, 1]
        
        Arguments:
            self       the integrator object
            functor    the function to integrate
        """
    @typing.overload
    def __call__(self, functor: typing.Callable[[float], float], a: float, b: float) -> float:
        """
        Calculate the integral over the interval [a,b]
        
        Arguments:
            self       the integrator object
            functor    the function to integrate
            a          the lower bound of the integration interval
            b          the upper bound of the integration interval
        """
    def __init__(self) -> None:
        """
        Initialise the quadrature rule
        """
class GaussLobatto2:
    """
    Gauss-Lobatto 2-point quadrature rule
    """
    @typing.overload
    def __call__(self, functor: typing.Callable[[float], float]) -> float:
        """
        Calculate the integral over the interval [-1, 1]
        
        Arguments:
            self       the integrator object
            functor    the function to integrate
        """
    @typing.overload
    def __call__(self, functor: typing.Callable[[float], float], a: float, b: float) -> float:
        """
        Calculate the integral over the interval [a,b]
        
        Arguments:
            self       the integrator object
            functor    the function to integrate
            a          the lower bound of the integration interval
            b          the upper bound of the integration interval
        """
    def __init__(self) -> None:
        """
        Initialise the quadrature rule
        """
class GaussLobatto32:
    """
    Gauss-Lobatto 32-point quadrature rule
    """
    @typing.overload
    def __call__(self, functor: typing.Callable[[float], float]) -> float:
        """
        Calculate the integral over the interval [-1, 1]
        
        Arguments:
            self       the integrator object
            functor    the function to integrate
        """
    @typing.overload
    def __call__(self, functor: typing.Callable[[float], float], a: float, b: float) -> float:
        """
        Calculate the integral over the interval [a,b]
        
        Arguments:
            self       the integrator object
            functor    the function to integrate
            a          the lower bound of the integration interval
            b          the upper bound of the integration interval
        """
    def __init__(self) -> None:
        """
        Initialise the quadrature rule
        """
class GaussLobatto4:
    """
    Gauss-Lobatto 4-point quadrature rule
    """
    @typing.overload
    def __call__(self, functor: typing.Callable[[float], float]) -> float:
        """
        Calculate the integral over the interval [-1, 1]
        
        Arguments:
            self       the integrator object
            functor    the function to integrate
        """
    @typing.overload
    def __call__(self, functor: typing.Callable[[float], float], a: float, b: float) -> float:
        """
        Calculate the integral over the interval [a,b]
        
        Arguments:
            self       the integrator object
            functor    the function to integrate
            a          the lower bound of the integration interval
            b          the upper bound of the integration interval
        """
    def __init__(self) -> None:
        """
        Initialise the quadrature rule
        """
class GaussLobatto6:
    """
    Gauss-Lobatto 6-point quadrature rule
    """
    @typing.overload
    def __call__(self, functor: typing.Callable[[float], float]) -> float:
        """
        Calculate the integral over the interval [-1, 1]
        
        Arguments:
            self       the integrator object
            functor    the function to integrate
        """
    @typing.overload
    def __call__(self, functor: typing.Callable[[float], float], a: float, b: float) -> float:
        """
        Calculate the integral over the interval [a,b]
        
        Arguments:
            self       the integrator object
            functor    the function to integrate
            a          the lower bound of the integration interval
            b          the upper bound of the integration interval
        """
    def __init__(self) -> None:
        """
        Initialise the quadrature rule
        """
class GaussLobatto64:
    """
    Gauss-Lobatto 64-point quadrature rule
    """
    @typing.overload
    def __call__(self, functor: typing.Callable[[float], float]) -> float:
        """
        Calculate the integral over the interval [-1, 1]
        
        Arguments:
            self       the integrator object
            functor    the function to integrate
        """
    @typing.overload
    def __call__(self, functor: typing.Callable[[float], float], a: float, b: float) -> float:
        """
        Calculate the integral over the interval [a,b]
        
        Arguments:
            self       the integrator object
            functor    the function to integrate
            a          the lower bound of the integration interval
            b          the upper bound of the integration interval
        """
    def __init__(self) -> None:
        """
        Initialise the quadrature rule
        """
class GaussLobatto8:
    """
    Gauss-Lobatto 8-point quadrature rule
    """
    @typing.overload
    def __call__(self, functor: typing.Callable[[float], float]) -> float:
        """
        Calculate the integral over the interval [-1, 1]
        
        Arguments:
            self       the integrator object
            functor    the function to integrate
        """
    @typing.overload
    def __call__(self, functor: typing.Callable[[float], float], a: float, b: float) -> float:
        """
        Calculate the integral over the interval [a,b]
        
        Arguments:
            self       the integrator object
            functor    the function to integrate
            a          the lower bound of the integration interval
            b          the upper bound of the integration interval
        """
    def __init__(self) -> None:
        """
        Initialise the quadrature rule
        """
def histogram(xLeft: float, xRight: float, yLeft: float, yRight: float) -> float:
    """
    Perform histogram integration (y is constant in x)
    
    Arguments:
        xLeft    the left value on the x interval
        xRight   the right value on the x interval
        yLeft    the left value on the y interval
        yRight   the right value on the y interval
    """
def linlin(xLeft: float, xRight: float, yLeft: float, yRight: float) -> float:
    """
    Perform linear-linear integration (y is linear in x)
    
    The integral of a panel is calculated analytically using the trapezoid rule.
    Arguments:
        xLeft    the left value on the x interval
        xRight   the right value on the x interval
        yLeft    the left value on the y interval
        yRight   the right value on the y interval
    """
def linlog(xLeft: float, xRight: float, yLeft: float, yRight: float) -> float:
    """
    Perform linear-logarithmic integration (y is linear in ln(x))
    
    The integral of a panel is calculated analytically using the following
    primitive function:
      int ln(x) =  x ln(x) - x
    
    Since y is linear in ln(x), the panel is interpolated as:
      y = a ln(x/x1) + y1 with a = (y2 - y1) / ln(x2/x1)
    
    The integral over the panel is then given by:
      int[x1,x2] y dx = int[x1,x2] a ln(x/x1) dx + y1 (x2 - x1)
    
    By substituting z = x/x1 in the first term, we obtain:
      int[x1,x2] y dx = int[1,x2/x1] a x1 ln(z) dz + y1 (x2 - x1)
    which simplifies to (using the primitive):
      int[x1,x2] y dx = a x1 (x2/x1 (ln(x2/x1) - 1) + 1) + y1 (x2 - x1)
    
    Arguments:
        xLeft    the left value on the x interval
        xRight   the right value on the x interval
        yLeft    the left value on the y interval
        yRight   the right value on the y interval
    """
def loglin(xLeft: float, xRight: float, yLeft: float, yRight: float) -> float:
    """
    Perform logarithmic-linear integration (ln(y) is linear in x)
    
    The integral of a panel is calculated analytically using the following
    primitive function:
      int exp(ax) =  exp(ax) / a
    
    Since ln(y) is linear in x, the panel is interpolated as:
      y = exp(a (x - x1) + ln(y1)) with a = ln(y2/y1) / (x2 - x1)
        = y1 exp(a (x - x1))
    
    The integral over the panel is then given by:
      int[x1,x2] y dx = y1 int[x1,x2] exp(a (x - x1))
    which simplifies to (using the primitive):
      int[x1,x2] y dx = y1 / a (exp(a (x2 - x1)) - exp(a (x1 - x1)))
                      = y1 / a (exp(a (x2 - x1)) - 1)
                      = y1 / a (y2 / y1 - 1)
    
    Arguments:
        xLeft    the left value on the x interval
        xRight   the right value on the x interval
        yLeft    the left value on the y interval
        yRight   the right value on the y interval
    """
def loglog(xLeft: float, xRight: float, yLeft: float, yRight: float) -> float:
    """
    Perform logarithmic-logarithmic integration (ln(y) is linear in ln(x))
    
    Since ln(y) is linear in ln(x), the panel is interpolated as:
      y = exp(a ln(x/x1) + ln(y1)) with a = ln(y2/y1) / ln(x2/x1)
        = y1 (x/x1)^a
    
    The integral over the panel is then given by:
      int[x1,x2] y dx = y1 int[x1,x2] (x/x1)^a
    which simplifies to:
      int[x1,x2] y dx = x1 y1 / (a + 1) ((x2/x1)^(a+1) - 1)
    
    Arguments:
        xLeft    the left value on the x interval
        xRight   the right value on the x interval
        yLeft    the left value on the y interval
        yRight   the right value on the y interval
    """
