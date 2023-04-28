# standard imports
import unittest

# third party imports

# local imports
from scion.math import clenshaw

class Test_scion_math_clenshaw( unittest.TestCase ) :
    """Unit test for the clenshaw function."""

    def test_clenshaw_polynomials( self ) :

        # polynomial coefficients (from lower order to higher order)
        order0 = [ 1. ]
        order1 = [ 1., 2. ]
        order2 = [ 1., 2., 3. ]
        order3 = [ 1., 2., 3., 4. ]

        def a( k, x ) : return x
        def b( k, x ) : return 0.

        self.assertAlmostEqual(  1., clenshaw( order0, a, b, 1., 0., 0. ) )
        self.assertAlmostEqual(  1., clenshaw( order1, a, b, 1., 0., 0. ) )
        self.assertAlmostEqual(  1., clenshaw( order2, a, b, 1., 0., 0. ) )
        self.assertAlmostEqual(  1., clenshaw( order3, a, b, 1., 0., 0. ) )

        self.assertAlmostEqual(  1., clenshaw( order0, a, b, 1., 1., 1. ) )
        self.assertAlmostEqual(  3., clenshaw( order1, a, b, 1., 1., 1. ) )
        self.assertAlmostEqual(  6., clenshaw( order2, a, b, 1., 1., 1. ) )
        self.assertAlmostEqual( 10., clenshaw( order3, a, b, 1., 1., 1. ) )

        self.assertAlmostEqual(  1., clenshaw( order0, a, b, 1., -1., -1. ) )
        self.assertAlmostEqual( -1., clenshaw( order1, a, b, 1., -1., -1. ) )
        self.assertAlmostEqual(  2., clenshaw( order2, a, b, 1., -1., -1. ) )
        self.assertAlmostEqual( -2., clenshaw( order3, a, b, 1., -1., -1. ) )

    def test_clenshaw_legendre( self ) :

        # Legendre coefficients (from lower order to higher order)
        order0 = [ 1. ]
        order1 = [ 1., 2. ]
        order2 = [ 1., 2., 3. ]
        order3 = [ 1., 2., 3., 4. ]

        def a( k, x ) : return ( 2 * k + 1 ) / ( k + 1 ) * x
        def b( k, x ) : return - k / ( k + 1 )

        self.assertAlmostEqual(  1. , clenshaw( order0, a, b, 1., 0., 0. ) )
        self.assertAlmostEqual(  1. , clenshaw( order1, a, b, 1., 0., 0. ) )
        self.assertAlmostEqual( -0.5, clenshaw( order2, a, b, 1., 0., 0. ) )
        self.assertAlmostEqual( -0.5, clenshaw( order3, a, b, 1., 0., 0. ) )

        self.assertAlmostEqual(  1., clenshaw( order0, a, b, 1., 1., 1. ) )
        self.assertAlmostEqual(  3., clenshaw( order1, a, b, 1., 1., 1. ) )
        self.assertAlmostEqual(  6., clenshaw( order2, a, b, 1., 1., 1. ) )
        self.assertAlmostEqual( 10., clenshaw( order3, a, b, 1., 1., 1. ) )

        self.assertAlmostEqual(  1., clenshaw( order0, a, b, 1., -1., -1. ) )
        self.assertAlmostEqual( -1., clenshaw( order1, a, b, 1., -1., -1. ) )
        self.assertAlmostEqual(  2., clenshaw( order2, a, b, 1., -1., -1. ) )
        self.assertAlmostEqual( -2., clenshaw( order3, a, b, 1., -1., -1. ) )

if __name__ == '__main__' :

    unittest.main()
