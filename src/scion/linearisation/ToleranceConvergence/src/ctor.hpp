/**
 *  @brief Constructor
 *
 *  @param tolerance   the linearisation tolerance
 *  @param threshold   the lowest allowed absolute difference
 */
ToleranceConvergence( const Y& tolerance = Y( 0.001 ),
                      const Y& threshold = Y( 1e-10 ) ) :
  tolerance_( tolerance ), threshold_( threshold ) {}
