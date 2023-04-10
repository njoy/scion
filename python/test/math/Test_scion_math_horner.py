# standard imports
import unittest

# third party imports

# local imports
from scion.math import horner

class Test_scion_math_horner( unittest.TestCase ) :
    """Unit test for the horner function."""

    def test_horner( self ) :

        # polynomial coefficients (from lower order to higher order)
        order0 = [ 1. ]
        order1 = [ 1., 2. ]
        order2 = [ 1., 2., 3. ]
        order3 = [ 1., 2., 3., 4. ]

        self.assertAlmostEqual(  1., horner( order0, 0. ) )
        self.assertAlmostEqual(  1., horner( order1, 0. ) )
        self.assertAlmostEqual(  1., horner( order2, 0. ) )
        self.assertAlmostEqual(  1., horner( order3, 0. ) )

        self.assertAlmostEqual(  1., horner( order0, 1. ) )
        self.assertAlmostEqual(  3., horner( order1, 1. ) )
        self.assertAlmostEqual(  6., horner( order2, 1. ) )
        self.assertAlmostEqual( 10., horner( order3, 1. ) )

        self.assertAlmostEqual(  1., horner( order0, -1. ) )
        self.assertAlmostEqual( -1., horner( order1, -1. ) )
        self.assertAlmostEqual(  2., horner( order2, -1. ) )
        self.assertAlmostEqual( -2., horner( order3, -1. ) )

if __name__ == '__main__' :

    unittest.main()
