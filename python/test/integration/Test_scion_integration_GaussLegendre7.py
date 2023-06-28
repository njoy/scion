# standard imports
import unittest

# third party imports

# local imports
from scion.integration import GaussLegendre7

class Test_scion_integration_GaussLegendre7( unittest.TestCase ) :
    """Unit test for the GaussLegendre7 interpolant."""

    def test_integration( self ) :

        def f( x ) :

            return x + 1

        integrator = GaussLegendre7()

        self.assertAlmostEqual( 2.0, integrator( f ) )

if __name__ == '__main__' :

    unittest.main()
