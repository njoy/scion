# standard imports
import unittest

# third party imports

# local imports
from scion.integration import GaussLegendre10

class Test_scion_integration_GaussLegendre10( unittest.TestCase ) :
    """Unit test for the GaussLegendre10 interpolant."""

    def test_integration( self ) :

        def poly0( x ) : return 1
        def poly1( x ) : return x + 1
        def poly2( x ) : return x * x + 1
        def poly3( x ) : return x * x * x + 1
        def poly7( x ) : return x**7 + 1
        def poly11( x ) : return x**11 + 1
        def poly13( x ) : return x**13 + 1
        def poly15( x ) : return x**15 + 1
        def polymax( x ) : return x**19 + 1

        integrator = GaussLegendre10()

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

        self.assertAlmostEqual(     2., integrator( poly7 ) )
        self.assertAlmostEqual(     2., integrator( poly7, -1., 1. ) )
        self.assertAlmostEqual( 48010., integrator( poly7, 3., 5. ) )

        self.assertAlmostEqual( 2.                  , integrator( poly11 ) )
        self.assertAlmostEqual( 2.                  , integrator( poly11, -1., 1. ) )
        self.assertAlmostEqual( 2.030076733333333e+7, integrator( poly11, 3., 5. ) )

        self.assertAlmostEqual( 2.                  , integrator( poly13 ) )
        self.assertAlmostEqual( 2.                  , integrator( poly13, -1., 1. ) )
        self.assertAlmostEqual( 4.356237631428576e+8, integrator( poly13, 3., 5. ), 4 )

        self.assertAlmostEqual( 2.                  , integrator( poly15 ) )
        self.assertAlmostEqual( 2.                  , integrator( poly15, -1., 1. ) )
        self.assertAlmostEqual( 9.534052746000000e+9, integrator( poly15, 3., 5. ), 3 )

        self.assertAlmostEqual( 2.                     , integrator( polymax ) )
        self.assertAlmostEqual( 2.                     , integrator( polymax, -1., 1. ) )
        self.assertAlmostEqual( 4.768197242813200e+12, integrator( polymax, 3., 5. ), 0 )

if __name__ == '__main__' :

    unittest.main()
