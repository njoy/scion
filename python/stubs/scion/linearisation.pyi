"""
Common linearisation capabilities and components
"""
from __future__ import annotations
import typing
__all__ = ['Lineariser', 'MidpointSplit', 'ToleranceConvergence']
class Lineariser:
    """
    A generic linearisation object
    """
    def __call__(self, grid: list[float], function: typing.Callable[[float], float], convergence: typing.Callable[[float, float, float, float, float, float], bool], split: typing.Callable[[float, float, float, float], float]) -> None:
        """
        Linearise a function
        
            grid          the initial grid
            functor       the function to linearise
            convergence   the convergence criterion function
            split         the panel splitting function
        """
    def __init__(self) -> None:
        """
        Initialise the lineariser
        """
    @property
    def x(self) -> list[float]:
        """
        The x values of the linearised function
        """
    @property
    def y(self) -> list[float]:
        """
        The y values of the linearised function
        """
class MidpointSplit:
    """
    A split functor using a panel's midpoint
    """
    def __call__(self, xLeft: float, xRight: float, yLeft: float, yRight: float) -> float:
        """
        Split the panel
        
        Arguments:
            self     the split functor
            xLeft    the left value on the x interval
            xRight   the right value on the x interval
            yLeft    the left value on the y interval
            yRight   the right value on the y interval
        """
    def __init__(self) -> None:
        """
        Initialise the panel split functor
        """
class ToleranceConvergence:
    """
    A convergence functor using a single tolerance
    
    This functor class can be used to ensure convergence of the linearisation
    process using a relative tolerance and absolute difference threshold.
    With this functor, a trial value and reference value are considered
    converged if:
      abs( trial - reference ) < ( abs( trial ) + abs( reference ) ) * tolerance
    
    For very small values (when ( abs( trial ) + abs( reference ) ) * tolerance
    is smaller than the threshold value), a trial value and reference value
    are considered converged if:
      abs( trial - reference ) < threshold
    """
    def __call__(self, trial: float, reference: float, xLeft: float, xRight: float, yLeft: float, yRight: float) -> float:
        """
        Test the convergence of the linearisation
        
        Arguments:
            self         the convergence functor
            trial        the trial value to be tested
            reference    the reference value to be tested against
            xLeft        the left value on the x interval
            xRight       the right value on the x interval
            yLeft        the left value on the y interval
            yRight       the right value on the y interval
        """
    def __init__(self, tolerance: float = 0.001, threshold: float = 1e-10) -> None:
        """
        Initialise the convergence functor
        
        Arguments:
            self        the functor
            tolerance   the linearisation tolerance (default 0.1 %)
            threshold   the lowest allowed absolute difference (default 1e-10)
        """
    @property
    def threshold(self) -> float:
        """
        The linearisation threshold
        """
    @property
    def tolerance(self) -> float:
        """
        The linearisation tolerance
        """
