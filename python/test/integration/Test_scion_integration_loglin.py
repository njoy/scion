# standard imports
import unittest

# third party imports

# local imports
from scion.integration import loglin

class Test_scion_integration_loglin( unittest.TestCase ) :
    """Unit test for the log-lin interpolant."""

    def test_integration_function( self ) :

        xLeft = 1.0
        xRight = 2.0
        yLeft = 1.0
        yRight = 4.0

        self.assertAlmostEqual( 2.16404256133345, loglin( xLeft, xRight, yLeft, yRight ) )

if __name__ == '__main__' :

    unittest.main()
