/**
 *  @brief Constructor
 *
 *  @param x   the x values of the tabulated data
 *  @param y   the y values of the tabulated data
 */
LinearLinearTable( XContainer x, YContainer y ) :
  Parent( std::move( x ), std::move( y ) ) {}