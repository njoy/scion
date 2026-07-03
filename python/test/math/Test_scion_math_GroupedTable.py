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
            self.assertEqual( 4, len( chunk.boundaries ) )
            self.assertAlmostEqual( chunk.values[0], 34 )
            self.assertAlmostEqual( chunk.values[1], 35 )
            self.assertAlmostEqual( chunk.values[2], 36 )
            self.assertAlmostEqual( chunk.boundaries[0],  0 )
            self.assertAlmostEqual( chunk.boundaries[1], 10 )
            self.assertAlmostEqual( chunk.boundaries[2], 25 )
            self.assertAlmostEqual( chunk.boundaries[3], 32 )

        # the data is given explicitly for data without boundaries
        chunk = GroupedTable( boundaries = [ 0., 10., 25., 32. ],
                              values = [ 34., 35., 36. ] )

        verify_chunk( self, chunk )

        changed = 2 * chunk
        changed_back = changed / 2

        verify_chunk(self, changed_back)

    def test_failures( self ) :

        print( '\n' )

        # there are not enough values in the boundaries or values grid
        with self.assertRaises( Exception ) :

            chunk = GroupedTable( boundaries = [1.0], values = [] )

        # the boundaries and values sizes don't match
        with self.assertRaises( Exception ) :

            chunk = GroupedTable( boundaries = [ 1., 2., 3. ],
                                  values = [ 4., 3., 2. ] )

        # the boundaries grid is not sorted
        with self.assertRaises( Exception ) :

            chunk = GroupedTable( boundaries = [ 1., 3., 2., 4. ],
                                  values = [ 4., 3., 2. ] )

        # the boundaries grid is not unique
        with self.assertRaises( Exception ) :

            chunk = GroupedTable( boundaries = [ 1., 2., 2., 4. ],
                                  values = [ 4., 3., 2. ] )

if __name__ == '__main__' :

    unittest.main()
