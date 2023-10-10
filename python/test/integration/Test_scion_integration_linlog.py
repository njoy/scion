# standard imports
import unittest

# third party imports

# local imports
from scion.integration import linlog

class Test_scion_integration_linlog( unittest.TestCase ) :
    """Unit test for the lin-log interpolant."""

    def test_integration_function( self ) :

        xLeft = 1.0
        xRight = 2.0
        yLeft = 1.0
        yRight = 4.0

        self.assertAlmostEqual( 2.67191487733311, linlog( xLeft, xRight, yLeft, yRight ) )

if __name__ == '__main__' :

    unittest.main()
