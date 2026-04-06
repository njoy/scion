# standard imports
import unittest
import sys

# third party imports

# local imports
from scion.math import GroupedTable

class Test_scion_math_GroupedTable( unittest.TestCase ) :
    """Unit test for the GroupedTable class."""

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( 3, chunk.number_groups )
            self.assertEqual( 3, len(chunk.values) )
            self.assertEqual( 4, len( chunk.bounds ) )
            self.assertAlmostEqual( chunk.values[0], 34 )
            self.assertAlmostEqual( chunk.values[1], 35 )
            self.assertAlmostEqual( chunk.values[2], 36 )
            self.assertAlmostEqual( chunk.bounds[0],  0 )
            self.assertAlmostEqual( chunk.bounds[1], 10 )
            self.assertAlmostEqual( chunk.bounds[2], 25 )
            self.assertAlmostEqual( chunk.bounds[3], 32 )

        # the data is given explicitly for data without boundaries
        chunk = GroupedTable( bounds = [ 0., 10., 25., 32. ],
                              values = [ 34., 35., 36. ] )

        verify_chunk( self, chunk )

    def test_failures( self ) :

        print( '\n' )

        # there are not enough values in the x or y grid
        with self.assertRaises( Exception ) :

            chunk = GroupedTable( x = [1.0], y = [] )

        # the x and y sizes don't match
        with self.assertRaises( Exception ) :

            chunk = GroupedTable( x = [ 1., 2., 3. ],
                                        y = [ 4., 3., 2. ] )

        # the x grid is not sorted
        with self.assertRaises( Exception ) :

            chunk = GroupedTable( x = [ 1., 3., 2., 4. ],
                                        y = [ 4., 3., 2. ] )

        # the x grid is not unique
        with self.assertRaises( Exception ) :

            chunk = GroupedTable( x = [ 1., 2., 2., 4. ],
                                        y = [ 4., 3., 2. ]
            )


if __name__ == '__main__' :

    unittest.main()
