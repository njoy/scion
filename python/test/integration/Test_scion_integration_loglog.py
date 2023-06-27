# standard imports
import unittest

# third party imports

# local imports
from scion.integration import loglog

class Test_scion_integration_loglog( unittest.TestCase ) :
    """Unit test for the log-log interpolant."""

    def test_integration_function( self ) :

        xLeft = 1.0
        xRight = 2.0
        yLeft = 1.0
        yRight = 4.0

        self.assertAlmostEqual( 2.33333333333333, loglog( xLeft, xRight, yLeft, yRight ) )

if __name__ == '__main__' :

    unittest.main()
