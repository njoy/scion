# standard imports
import unittest

# third party imports

# local imports
from scion.math import newton

class Test_scion_math_newton( unittest.TestCase ) :
    """Unit test for the newton function."""

    def test_newton( self ) :

        def functor( x ) : return x * x - 1.
        def derivative( x ) : return 2. * x

        self.assertEqual( 1., newton( 0.5, functor, derivative ) )
        self.assertEqual( 1., newton( 0.7, functor, derivative ) )
        self.assertEqual( 1., newton( 1.2, functor, derivative ) )
        self.assertEqual( 1., newton( 1.5, functor, derivative ) )
        self.assertEqual( 1., newton( 2.0, functor, derivative ) )

if __name__ == '__main__' :

    unittest.main()
