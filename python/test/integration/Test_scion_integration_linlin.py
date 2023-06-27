# standard imports
import unittest

# third party imports

# local imports
from scion.integration import linlin

class Test_scion_integration_linlin( unittest.TestCase ) :
    """Unit test for the lin-lin interpolant."""

    def test_integration_function( self ) :

        xLeft = 1.0
        xRight = 2.0
        yLeft = 1.0
        yRight = 4.0

        self.assertAlmostEqual( 2.5, linlin( xLeft, xRight, yLeft, yRight ) )

if __name__ == '__main__' :

    unittest.main()
