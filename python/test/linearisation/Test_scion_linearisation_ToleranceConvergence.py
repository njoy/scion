# standard imports
import unittest

# third party imports

# local imports
from scion.linearisation import ToleranceConvergence

class Test_scion_linearisation_ToleranceConvergence( unittest.TestCase ) :
    """Unit test for the ToleranceConvergence function."""

    def test_ToleranceConvergence( self ) :

        xLeft = 0.
        xRight = 2.
        yLeft = 1.
        yRight = 3.

        # the default tolerance and threshold are used
        chunk = ToleranceConvergence();

        self.assertEqual( False, chunk( 1.000, 2., xLeft, xRight, yLeft, yRight ) )
        self.assertEqual( False, chunk( 1.900, 2., xLeft, xRight, yLeft, yRight ) )
        self.assertEqual( False, chunk( 1.990, 2., xLeft, xRight, yLeft, yRight ) )
        self.assertEqual( True, chunk( 1.999, 2., xLeft, xRight, yLeft, yRight ) )
        self.assertEqual( True, chunk( 2.000, 2., xLeft, xRight, yLeft, yRight ) )
        self.assertEqual( True, chunk( 2.001, 2., xLeft, xRight, yLeft, yRight ) )
        self.assertEqual( False, chunk( 2.010, 2., xLeft, xRight, yLeft, yRight ) )
        self.assertEqual( False, chunk( 2.100, 2., xLeft, xRight, yLeft, yRight ) )
        self.assertEqual( False, chunk( 3.000, 2., xLeft, xRight, yLeft, yRight ) )

        # a user defined tolerance and default threshold
        chunk = ToleranceConvergence( 0.01 );

        self.assertEqual( False, chunk( 1.000, 2., xLeft, xRight, yLeft, yRight ) )
        self.assertEqual( False, chunk( 1.900, 2., xLeft, xRight, yLeft, yRight ) )
        self.assertEqual( True, chunk( 1.990, 2., xLeft, xRight, yLeft, yRight ) )
        self.assertEqual( True, chunk( 1.999, 2., xLeft, xRight, yLeft, yRight ) )
        self.assertEqual( True, chunk( 2.000, 2., xLeft, xRight, yLeft, yRight ) )
        self.assertEqual( True, chunk( 2.001, 2., xLeft, xRight, yLeft, yRight ) )
        self.assertEqual( True, chunk( 2.010, 2., xLeft, xRight, yLeft, yRight ) )
        self.assertEqual( False, chunk( 2.100, 2., xLeft, xRight, yLeft, yRight ) )
        self.assertEqual( False, chunk( 3.000, 2., xLeft, xRight, yLeft, yRight ) )

if __name__ == '__main__' :

    unittest.main()
