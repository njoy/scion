# standard imports
import unittest

# third party imports

# local imports
from scion.interpolation import histogram

class Test_scion_interpolation_histogram( unittest.TestCase ) :
    """Unit test for the horner function."""

    def test_interpolation_function( self ) :

        xLeft = 1.0
        xRight = 2.0
        yLeft = 1.0
        yRight = 4.0

        self.assertAlmostEqual( 1.0, histogram( 1.0, xLeft, xRight, yLeft, yRight ) )
        self.assertAlmostEqual( 1.0, histogram( 1.5, xLeft, xRight, yLeft, yRight ) )
        self.assertAlmostEqual( 1.0, histogram( 2.0, xLeft, xRight, yLeft, yRight ) )

if __name__ == '__main__' :

    unittest.main()
