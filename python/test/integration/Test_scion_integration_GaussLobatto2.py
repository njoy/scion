# standard imports
import unittest

# third party imports

# local imports
from scion.integration import GaussLobatto2

class Test_scion_integration_GaussLobatto2( unittest.TestCase ) :
    """Unit test for the GaussLobatto2 integrator."""

    def test_integration( self ) :

        def poly0( x ) : return 1
        def poly1( x ) : return x + 1

        integrator = GaussLobatto2()

        self.assertAlmostEqual( 2.0, integrator( poly0 ) )
        self.assertAlmostEqual( 2.0, integrator( poly0, -1., 1. ) )
        self.assertAlmostEqual( 2.0, integrator( poly0, 3., 5. ) )

        self.assertAlmostEqual(  2.0, integrator( poly1 ) )
        self.assertAlmostEqual(  2.0, integrator( poly1, -1., 1. ) )
        self.assertAlmostEqual( 10.0, integrator( poly1, 3., 5. ) )

if __name__ == '__main__' :

    unittest.main()
