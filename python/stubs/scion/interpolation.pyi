"""
Common interpolation capabilities and components
"""
from __future__ import annotations
import typing
__all__ = ['InterpolationType', 'histogram', 'linlin', 'linlog', 'loglin', 'loglog']
class InterpolationType:
    """
    The interpolation types
    
    Members:
    
      Histogram
    
      LinearLinear
    
      LinearLog
    
      LogLinear
    
      LogLog
    """
    Histogram: typing.ClassVar[InterpolationType]  # value = <InterpolationType.Histogram: 1>
    LinearLinear: typing.ClassVar[InterpolationType]  # value = <InterpolationType.LinearLinear: 2>
    LinearLog: typing.ClassVar[InterpolationType]  # value = <InterpolationType.LinearLog: 3>
    LogLinear: typing.ClassVar[InterpolationType]  # value = <InterpolationType.LogLinear: 4>
    LogLog: typing.ClassVar[InterpolationType]  # value = <InterpolationType.LogLog: 5>
    __members__: typing.ClassVar[dict[str, InterpolationType]]  # value = {'Histogram': <InterpolationType.Histogram: 1>, 'LinearLinear': <InterpolationType.LinearLinear: 2>, 'LinearLog': <InterpolationType.LinearLog: 3>, 'LogLinear': <InterpolationType.LogLinear: 4>, 'LogLog': <InterpolationType.LogLog: 5>}
    def __eq__(self, other: typing.Any) -> bool:
        ...
    def __ge__(self, other: typing.Any) -> bool:
        ...
    def __getstate__(self) -> int:
        ...
    def __gt__(self, other: typing.Any) -> bool:
        ...
    def __hash__(self) -> int:
        ...
    def __index__(self) -> int:
        ...
    def __init__(self, value: int) -> None:
        ...
    def __int__(self) -> int:
        ...
    def __le__(self, other: typing.Any) -> bool:
        ...
    def __lt__(self, other: typing.Any) -> bool:
        ...
    def __ne__(self, other: typing.Any) -> bool:
        ...
    def __repr__(self) -> str:
        ...
    def __setstate__(self, state: int) -> None:
        ...
    def __str__(self) -> str:
        ...
    @property
    def name(self) -> str:
        ...
    @property
    def value(self) -> int:
        ...
def histogram(x: float, xLeft: float, xRight: float, yLeft: float, yRight: float) -> float:
    """
    Perform histogram interpolation (y is constant in x)
    
    Arguments:
        x        the value of x
        xLeft    the left value on the x interval
        xRight   the right value on the x interval
        yLeft    the left value on the y interval
        yRight   the right value on the y interval
    """
def linlin(x: float, xLeft: float, xRight: float, yLeft: float, yRight: float) -> float:
    """
    Perform linear-linear interpolation (y is linear in x)
    
    Arguments:
        x        the value of x
        xLeft    the left value on the x interval
        xRight   the right value on the x interval
        yLeft    the left value on the y interval
        yRight   the right value on the y interval
    """
def linlog(x: float, xLeft: float, xRight: float, yLeft: float, yRight: float) -> float:
    """
    Perform linear-logarithmic interpolation (y is linear in ln(x))
    
    Arguments:
        x        the value of x
        xLeft    the left value on the x interval
        xRight   the right value on the x interval
        yLeft    the left value on the y interval
        yRight   the right value on the y interval
    """
def loglin(x: float, xLeft: float, xRight: float, yLeft: float, yRight: float) -> float:
    """
    Perform logarithmic-linear interpolation (ln(y) is linear in x)
    
    Arguments:
        x        the value of x
        xLeft    the left value on the x interval
        xRight   the right value on the x interval
        yLeft    the left value on the y interval
        yRight   the right value on the y interval
    """
def loglog(x: float, xLeft: float, xRight: float, yLeft: float, yRight: float) -> float:
    """
    Perform logarithmic-logarithmic interpolation (ln(y) is linear in ln(x))
    
    Arguments:
        x        the value of x
        xLeft    the left value on the x interval
        xRight   the right value on the x interval
        yLeft    the left value on the y interval
        yRight   the right value on the y interval
    """
