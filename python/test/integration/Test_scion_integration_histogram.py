# standard imports
import unittest

# third party imports

# local imports
from scion.integration import histogram

class Test_scion_integration_histogram( unittest.TestCase ) :
    """Unit test for the histogram interpolant."""

    def test_integration_function( self ) :

        xLeft = 1.0
        xRight = 2.0
        yLeft = 1.0
        yRight = 4.0

        self.assertAlmostEqual( 1.0, histogram( xLeft, xRight, yLeft, yRight ) )

if __name__ == '__main__' :

    unittest.main()
