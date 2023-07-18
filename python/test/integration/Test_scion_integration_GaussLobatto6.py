# standard imports
import unittest

# third party imports

# local imports
from scion.integration import GaussLobatto6

class Test_scion_integration_GaussLobatto6( unittest.TestCase ) :
    """Unit test for the GaussLobatto6 integrator."""

    def test_integration( self ) :

        def poly0( x ) : return 1
        def poly1( x ) : return x + 1
        def poly1( x ) : return x + 1
        def poly2( x ) : return x * x + 1
        def poly3( x ) : return x * x * x + 1
        def poly5( x ) : return x**5 + 1
        def polymax( x ) : return x**9 + 1

        integrator = GaussLobatto6()

        self.assertAlmostEqual( 2.0, integrator( poly0 ) )
        self.assertAlmostEqual( 2.0, integrator( poly0, -1., 1. ) )
        self.assertAlmostEqual( 2.0, integrator( poly0, 3., 5. ) )

        self.assertAlmostEqual(  2.0, integrator( poly1 ) )
        self.assertAlmostEqual(  2.0, integrator( poly1, -1., 1. ) )
        self.assertAlmostEqual( 10.0, integrator( poly1, 3., 5. ) )

        self.assertAlmostEqual(  2.66666666666666, integrator( poly2 ) )
        self.assertAlmostEqual(  2.66666666666666, integrator( poly2, -1., 1. ) )
        self.assertAlmostEqual( 34.66666666666666, integrator( poly2, 3., 5. ) )

        self.assertAlmostEqual(   2., integrator( poly3 ) )
        self.assertAlmostEqual(   2., integrator( poly3, -1., 1. ) )
        self.assertAlmostEqual( 138., integrator( poly3, 3., 5. ) )

        self.assertAlmostEqual(                    2., integrator( poly5 ) )
        self.assertAlmostEqual(                    2., integrator( poly5, -1., 1. ) )
        self.assertAlmostEqual( 2.484666666666666e+03, integrator( poly5, 3., 5. ) )

        self.assertAlmostEqual(                    2., integrator( polymax ) )
        self.assertAlmostEqual(                    2., integrator( polymax, -1., 1. ) )
        self.assertAlmostEqual( 9.706596000000000e+05, integrator( polymax, 3., 5. ) )

if __name__ == '__main__' :

    unittest.main()