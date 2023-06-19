# standard imports
import unittest

# third party imports

# local imports
from scion.interpolation import linlog

class Test_scion_interpolation_linlog( unittest.TestCase ) :
    """Unit test for the horner function."""

    def test_interpolation_function( self ) :

        xLeft = 1.0
        xRight = 2.0
        yLeft = 1.0
        yRight = 4.0

        self.assertAlmostEqual( 1.0, linlog( 1.0, xLeft, xRight, yLeft, yRight ) )
        self.assertAlmostEqual( 2.75488750216347, linlog( 1.5, xLeft, xRight, yLeft, yRight ) )
        self.assertAlmostEqual( 4.0, linlog( 2.0, xLeft, xRight, yLeft, yRight ) )

if __name__ == '__main__' :

    unittest.main()
